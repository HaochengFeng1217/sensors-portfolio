// Task 4: 3V3 -> LDR -> GPIO34 measurement node -> 10 kOhm -> GND.
// Serial commands label a condition confirmed by the student; they do not detect it.
constexpr int LDR_PIN = 34;
constexpr unsigned long SAMPLE_MS = 300;
constexpr uint8_t SAMPLES_PER_TRIAL = 10;
const char *CONDITIONS[] = {"Dark", "Shade", "Room", "Flashlight"};
uint16_t trials[4] = {};
int condition = -1;
uint8_t sampleCount = 0;
unsigned long lastSample = 0;
uint16_t rawMin = 4095, rawMax = 0;
uint32_t mvMin = 0, mvMax = 0, rawSum = 0, mvSum = 0;

void startTrial(int selected) {
  condition = selected;
  ++trials[condition];
  sampleCount = 0;
  rawMin = 4095;
  rawMax = 0;
  rawSum = mvSum = 0;
  mvMin = UINT32_MAX;
  mvMax = 0;
  lastSample = millis();
  Serial.printf("BEGIN,%s,%u\n", CONDITIONS[condition], trials[condition]);
  Serial.println("Type,Condition,Trial,Sample,Elapsed_ms,Raw,ADC_mV");
}

void setup() {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(LDR_PIN, INPUT);
  analogReadResolution(12);
  analogSetPinAttenuation(LDR_PIN, ADC_11db);
  Serial.begin(115200);
  Serial.println("BOOT,Task4_LDR,12bit,GPIO34");
  Serial.println("READY: D=dark S=shade R=room F=flashlight; X=cancel");
}

void loop() {
  while (Serial.available() > 0) {
    char command = Serial.read();
    if (command >= 'a' && command <= 'z') command -= ('a' - 'A');
    if (command == 'X') {
      condition = -1;
      Serial.println("CANCELLED");
    }
    int selected = -1;
    if (command == 'D') selected = 0;
    if (command == 'S') selected = 1;
    if (command == 'R') selected = 2;
    if (command == 'F') selected = 3;
    if (selected >= 0) {
      if (condition < 0) startTrial(selected);
      else Serial.println("BUSY: finish this trial first");
    }
  }
  if (condition < 0 || millis() - lastSample < SAMPLE_MS) return;
  lastSample = millis();

  // These APIs make separate successive conversions, not one shared sample.
  const uint16_t raw = analogRead(LDR_PIN);
  const uint32_t mv = analogReadMilliVolts(LDR_PIN);
  ++sampleCount;
  if (raw < rawMin) rawMin = raw;
  if (raw > rawMax) rawMax = raw;
  if (mv < mvMin) mvMin = mv;
  if (mv > mvMax) mvMax = mv;
  rawSum += raw;
  mvSum += mv;
  Serial.printf("DATA,%s,%u,%u,%lu,%u,%lu\n", CONDITIONS[condition],
                trials[condition], sampleCount, millis(), raw, mv);

  if (sampleCount == SAMPLES_PER_TRIAL) {
    Serial.printf("END,%s,%u,RawMin:%u,RawMax:%u,RawMean:%.1f,mVMin:%lu,mVMax:%lu,mVMean:%.1f\n",
                  CONDITIONS[condition], trials[condition], rawMin, rawMax,
                  rawSum / float(sampleCount), mvMin, mvMax,
                  mvSum / float(sampleCount));
    condition = -1;
    Serial.println("READY");
  }
}
