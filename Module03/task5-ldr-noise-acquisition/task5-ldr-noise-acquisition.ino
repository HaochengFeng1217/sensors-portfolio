#include <Arduino.h>
#include <math.h>

constexpr int ADC_PIN = 34;
constexpr int N = 500;
constexpr uint32_t INTERVAL_US = 10000; // 100 Hz target
uint16_t samples[N];
uint32_t timestamps[N];
bool captured = false;

void printCapture() {
  if (!captured) return;
  Serial.println("BEGIN_TASK5_2_LDR_RAW");
  Serial.println("sample,elapsed_us,raw_adc");
  double sum = 0, ss = 0;
  int lo = 4095, hi = 0;
  for (int i = 0; i < N; i++) {
    Serial.printf("%d,%lu,%u\n", i + 1, (unsigned long)timestamps[i], samples[i]);
    sum += samples[i];
    if (samples[i] < lo) lo = samples[i];
    if (samples[i] > hi) hi = samples[i];
  }
  double mean = sum / N;
  for (int i = 0; i < N; i++) ss += (samples[i] - mean) * (samples[i] - mean);
  Serial.printf("SUMMARY N=%d,mean_raw=%.6f,sample_SD_raw=%.6f,min_raw=%d,max_raw=%d,range_raw=%d\n",
                N, mean, sqrt(ss / (N - 1)), lo, hi, hi - lo);
  Serial.printf("TIMING first_us=%lu,last_us=%lu,mean_interval_us=%.3f\n",
                (unsigned long)timestamps[0], (unsigned long)timestamps[N - 1],
                double(timestamps[N - 1] - timestamps[0]) / (N - 1));
  Serial.println("END_TASK5_2_LDR_RAW");
  Serial.println("DONE. Send P to reprint the same stored data; no new acquisition.");
}

void capture() {
  Serial.println("START: keep illumination and sensor position fixed for 5 seconds.");
  Serial.flush();
  for (int i = 0; i < 32; i++) { analogRead(ADC_PIN); delay(10); }
  uint32_t start = micros();
  for (int i = 0; i < N; i++) {
    uint32_t target = start + uint32_t(i) * INTERVAL_US;
    while (int32_t(micros() - target) < 0) delayMicroseconds(50);
    timestamps[i] = micros() - start;
    samples[i] = analogRead(ADC_PIN);
    delay(1);
  }
  captured = true;
  printCapture(); // Print after sampling to avoid serial timing interference.
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  delay(2000);
  Serial.println("READY_TASK5_2: LDR GPIO34, 12 bit, 11 dB, 500 raw samples at 100 Hz.");
  Serial.println("Send S to capture; P reprints stored data. Keep illumination fixed.");
}
void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == 'S' || c == 's') capture();
    if (c == 'P' || c == 'p') printCapture();
  }
  delay(10);
}
