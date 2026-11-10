#include <Arduino.h>
constexpr int ADC_PIN = 34;
constexpr int N = 2000;
constexpr uint32_t INTERVAL_US = 10000;
uint16_t samples[N];
uint32_t timestamps[N];
bool captured = false;

void printCapture() {
  if (!captured) { Serial.println("NO_CAPTURE. Send S to start."); return; }
  Serial.println("BEGIN_TASK5_4_POT_STEP");
  Serial.println("sample,elapsed_us,raw_adc,ma5,median5,ema_0p2");
  double ema = samples[0];
  for (int i = 0; i < N; ++i) {
    if (i > 0) ema = 0.2 * samples[i] + 0.8 * ema;
    Serial.printf("%d,%lu,%u,", i + 1, (unsigned long)timestamps[i], samples[i]);
    if (i < 4) Serial.print("nan,nan,");
    else {
      uint16_t window[5]; unsigned long sum = 0;
      for (int j = 0; j < 5; ++j) { window[j] = samples[i-4+j]; sum += window[j]; }
      for (int j = 1; j < 5; ++j) {
        uint16_t v = window[j]; int k = j-1;
        while (k >= 0 && window[k] > v) { window[k+1] = window[k]; --k; }
        window[k+1] = v;
      }
      Serial.printf("%.6f,%u,", sum / 5.0, window[2]);
    }
    Serial.printf("%.6f\n", ema);
  }
  Serial.printf("TIMING N=%d,first_us=%lu,last_us=%lu,mean_interval_us=%.3f\n", N,
    (unsigned long)timestamps[0], (unsigned long)timestamps[N-1],
    double(timestamps[N-1]-timestamps[0])/(N-1));
  Serial.println("END_TASK5_4_POT_STEP");
  Serial.println("DONE. P reprints stored data; S starts a new capture.");
}
void captureStep() {
  Serial.println("START: hold the knob still. At TURN NOW, turn quickly once, then hold.");
  Serial.flush();
  for (int i = 0; i < 32; ++i) { analogRead(ADC_PIN); delay(10); }
  uint32_t start = micros();
  for (int i = 0; i < N; ++i) {
    uint32_t target = start + uint32_t(i)*INTERVAL_US;
    while (int32_t(micros()-target) < 0) delayMicroseconds(50);
    timestamps[i] = micros()-start;
    samples[i] = analogRead(ADC_PIN);
    // One short cue after sample 501; actual sample timing is retained.
    if (i == 500) Serial.println("TURN NOW: turn quickly once, then keep still until DONE.");
    delay(1);
  }
  captured = true;
  printCapture();
}
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  delay(2000);
  Serial.println("READY_TASK5_4: GPIO34, 12 bit, 11 dB, 2000 samples at 100 Hz (20 s).");
  Serial.println("Waiting for S. No acquisition starts automatically. Keep both levels away from ADC rails.");
}
void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'S' || c == 's') captureStep();
    else if (c == 'P' || c == 'p') printCapture();
  }
  delay(10);
}
