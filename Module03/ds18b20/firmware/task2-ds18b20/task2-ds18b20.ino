#include <OneWire.h>
#include <DallasTemperature.h>
OneWire bus(4);
DallasTemperature sensors(&bus);
DeviceAddress probe;
bool ready = false;
unsigned long sampleNo = 0;
float sumC = 0, lowC = 0, highC = 0, firstC = 0;

void setup() {
  Serial.begin(115200);
  delay(1500);
  sensors.begin();
  if (!sensors.getAddress(probe, 0)) {
    Serial.println("ERROR: no sensor"); return;
  }
  sensors.setResolution(probe, 12);
  sensors.setWaitForConversion(false);
  ready = true;
  Serial.println("CONTINUOUS 12-bit. Send M to mark transfer.");
  Serial.println("sample,elapsed_ms,temperature_C");
}

void loop() {
  if (!ready) return;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == 'm' || c == 'M') {
      Serial.print("TRANSFER_MARKER_ms="); Serial.println(millis());
    }
  }
  sensors.requestTemperatures();
  delay(760);
  float t = sensors.getTempC(probe);
  unsigned long sampleMs = millis();
  if (t == DEVICE_DISCONNECTED_C) {
    Serial.println("READ_ERROR"); delay(240); return;
  }
  if (sampleNo % 10 == 0) { sumC = 0; lowC = highC = firstC = t; }
  sumC += t;
  if (t < lowC) lowC = t;
  if (t > highC) highC = t;
  sampleNo++;
  Serial.print(sampleNo); Serial.print(',');
  Serial.print(sampleMs); Serial.print(','); Serial.println(t, 4);
  if (sampleNo % 10 == 0) {
    Serial.print("LAST10 mean="); Serial.print(sumC / 10, 4);
    Serial.print(" min="); Serial.print(lowC, 4);
    Serial.print(" max="); Serial.print(highC, 4);
    Serial.print(" change="); Serial.println(t - firstC, 4);
  }
  delay(240);
}
