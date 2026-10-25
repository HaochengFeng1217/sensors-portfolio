// Potentiometer: outer terminals -> 3V3 and GND; wiper -> GPIO34.
// Verify the actual component terminals before connecting power.
// Serial Monitor: 115200 baud. Send H=12 bits, L=10 bits, R=reset statistics.
constexpr int POT_PIN = 34;
constexpr unsigned long SAMPLE_MS = 50;
constexpr float ASSUMED_FULL_SCALE_V = 3.3f;

uint8_t adcBits = 12;
uint8_t seenCodes[512] = {};
uint16_t minimumRaw = 4095;
uint16_t maximumRaw = 0;
uint16_t uniqueCodes = 0;
unsigned long lastSample = 0;

void resetStatistics() {
  for (unsigned int i = 0; i < sizeof(seenCodes); ++i) {
    seenCodes[i] = 0;
  }
  minimumRaw = (1U << adcBits) - 1;
  maximumRaw = 0;
  uniqueCodes = 0;
}

void setResolution(uint8_t bits) {
  adcBits = bits;
  analogReadResolution(adcBits);
  resetStatistics();
}

void setup() {
  // Existing LED and button wiring may remain connected.
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(19, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
  setResolution(12);
  Serial.begin(115200);
}

void loop() {
  while (Serial.available() > 0) {
    const char command = Serial.read();
    if (command == 'H' || command == 'h') {
      setResolution(12);
    } else if (command == 'L' || command == 'l') {
      setResolution(10);
    } else if (command == 'R' || command == 'r') {
      resetStatistics();
    }
  }

  const unsigned long now = millis();
  if (now - lastSample < SAMPLE_MS) {
    return;
  }
  lastSample = now;

  const uint16_t raw = analogRead(POT_PIN);
  if (raw < minimumRaw) minimumRaw = raw;
  if (raw > maximumRaw) maximumRaw = raw;
  const uint16_t byteIndex = raw >> 3;
  const uint8_t mask = 1U << (raw & 7);
  if ((seenCodes[byteIndex] & mask) == 0) {
    seenCodes[byteIndex] |= mask;
    ++uniqueCodes;
  }

  // Nominal scaling assumption, not a calibrated voltage measurement.
  const float nominalVoltage = raw * ASSUMED_FULL_SCALE_V / (1U << adcBits);
  Serial.print("Bits:");
  Serial.print(adcBits);
  Serial.print(",Raw:");
  Serial.print(raw);
  Serial.print(",NominalV:");
  Serial.print(nominalVoltage, 4);
  Serial.print(",Min:");
  Serial.print(minimumRaw);
  Serial.print(",Max:");
  Serial.print(maximumRaw);
  Serial.print(",Unique:");
  Serial.println(uniqueCodes);
}
