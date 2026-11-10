#include <Arduino.h>
#include <math.h>

constexpr int ADC_PIN = 34;
constexpr int N = 64;
double meanRaw, sdRaw, meanFactoryV;
double referenceV[2], calibrationRaw[2];
bool havePoint[2] = {false, false};
String inputLine;
unsigned long lastLive = 0;

void measure() {
  double sum = 0, sumSquares = 0, sumMV = 0;
  for (int i = 0; i < N; i++) {
    int raw = analogRead(ADC_PIN);
    sum += raw;
    sumSquares += double(raw) * raw;
    // Separate conversion at the same fixed potentiometer position.
    sumMV += analogReadMilliVolts(ADC_PIN);
    delay(2);
  }
  meanRaw = sum / N;
  sdRaw = sqrt(fmax(0.0, (sumSquares - sum * sum / N) / (N - 1)));
  meanFactoryV = sumMV / N / 1000.0;
}

void printMeasurement(const char* label) {
  Serial.printf("%s,ms=%lu,raw_mean=%.3f,raw_SD=%.3f,factory_V=%.5f,N=%d\n",
                label, millis(), meanRaw, sdRaw, meanFactoryV, N);
}

void handleCommand() {
  char command;
  float voltage;
  if (sscanf(inputLine.c_str(), " %c %f", &command, &voltage) != 2 ||
      !isfinite(voltage) || voltage < 0 || voltage > 3.3) {
    Serial.println("Use A 0.500, B 2.000 or V 1.200; enter the actual meter voltage.");
    return;
  }
  if (command != 'A' && command != 'B' && command != 'V') {
    Serial.println("Unknown command. Use A, B or V."); return;
  }
  measure();
  if (meanRaw < 2 || meanRaw > 4093) {
    Serial.println("Near ADC clipping: choose a voltage inside the measurement range.");
    return;
  }
  printMeasurement("CAPTURE");
  Serial.printf("POINT=%c,reference_V=%.5f\n", command, double(voltage));
  if (command == 'A' || command == 'B') {
    int i = command == 'A' ? 0 : 1;
    referenceV[i] = voltage;
    calibrationRaw[i] = meanRaw;
    havePoint[i] = true;
  }
  if (!havePoint[0] || !havePoint[1]) {
    Serial.println("Waiting for the other calibration point."); return;
  }
  double delta = calibrationRaw[1] - calibrationRaw[0];
  if (fabs(delta) < 100 || fabs(referenceV[1] - referenceV[0]) < 0.1) {
    Serial.println("Calibration points too close. Recapture A and B farther apart."); return;
  }
  double a = (referenceV[1] - referenceV[0]) / delta;
  double b = referenceV[0] - a * calibrationRaw[0];
  Serial.printf("FIT: V = %.9f * raw + %.6f\n", a, b);
  if (command == 'V') {
    double corrected = a * meanRaw + b;
    Serial.printf("VALIDATION corrected_V=%.5f,before_error_V=%.5f,after_error_V=%.5f\n",
                  corrected, meanFactoryV - voltage, corrected - voltage);
    Serial.println("Before = factory-calibrated ADC voltage; after = this two-point fit.");
  }
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);
  delay(1200);
  Serial.println("TASK 3a: GPIO34, 12 bit, 11 dB attenuation.");
  Serial.println("Pot ends: 3V3 and GND. Wiper: GPIO34 and meter red. Meter black: GND.");
  Serial.println("Commands: A <meter volts>, B <meter volts>, V <fresh validation volts>.");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputLine.trim();
      if (inputLine.length()) handleCommand();
      inputLine = "";
    } else if (c != '\r') {
      if (inputLine.length() < 48) inputLine += c;
      else inputLine = "";
    }
  }
  if (millis() - lastLive >= 1000) {
    measure();
    printMeasurement("LIVE");
    lastLive = millis();
  }
}
