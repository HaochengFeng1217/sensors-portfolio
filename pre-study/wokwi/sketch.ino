#include <Arduino.h>

const int ADC_BITS = 12;
const int LED_LEVELS = 256;
const int POT_PIN = 34;
const int LED_PIN = 2;
int lastRaw = -1;

void setup() {
  Serial.begin(115200);
  analogReadResolution(ADC_BITS);
  pinMode(LED_PIN, OUTPUT);
  Serial.printf("ADC bits=%d, LED levels=%d\n", ADC_BITS, LED_LEVELS);
}

void loop() {
  int raw = analogRead(POT_PIN);
  int adcMax = (1 << ADC_BITS) - 1;
  int level = raw * LED_LEVELS / (adcMax + 1);
  int brightness = level * 255 / (LED_LEVELS - 1);
  analogWrite(LED_PIN, brightness);
  if (raw != lastRaw) {
    Serial.printf("raw=%d, brightness=%d\n", raw, brightness);
    lastRaw = raw;
  }
  delay(50);
}
