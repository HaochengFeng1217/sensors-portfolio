#include <Arduino.h>

constexpr int sensorPin = 34;
constexpr int sampleCount = 100;
constexpr uint32_t sampleIntervalMs = 20;
uint16_t raw[sampleCount];
uint16_t millivolts[sampleCount];
uint32_t elapsedMs[sampleCount];

void captureLevel(char level) {
  const uint32_t start = millis();
  for (int i = 0; i < sampleCount; ++i) {
    while (millis() - start < static_cast<uint32_t>(i) * sampleIntervalMs) {
      delay(1);
    }
    elapsedMs[i] = millis() - start;
    raw[i] = analogRead(sensorPin);
    millivolts[i] = analogReadMilliVolts(sensorPin);
  }
  Serial.printf("BEGIN_TASK4_LEVEL level=%c,start_ms=%lu\n", level, (unsigned long)start);
  Serial.println("sample,elapsed_ms,raw_adc,adc_mV_separate_conversion");
  for (int i = 0; i < sampleCount; ++i) {
    Serial.printf("%d,%lu,%u,%u\n", i + 1, (unsigned long)elapsedMs[i], raw[i], millivolts[i]);
  }
  Serial.println("END_TASK4_LEVEL");
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(sensorPin, ADC_11db);
  Serial.println("READY_TASK4_LEVEL: send 1-5 at a marked card position for a 2-second capture.");
}

void loop() {
  if (Serial.available() == 0) {
    delay(1);
    return;
  }
  const char command = Serial.read();
  if (command >= '1' && command <= '5') {
    captureLevel(command);
  }
}
