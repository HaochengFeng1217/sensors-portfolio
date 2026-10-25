// LED: GPIO18 -> 220-330 ohm resistor -> LED anode; cathode -> GND.
// Button: GPIO19 -> button -> GND.
// INPUT_PULLUP defines the released state without an external resistor.
// Optional external pull-up: 3V3 -> 10 kilohm resistor -> GPIO19.
constexpr int LED_PIN = 18;
constexpr int BUTTON_PIN = 19;
constexpr unsigned long DEBOUNCE_MS = 30;
constexpr unsigned long REPORT_MS = 200;

int lastRaw;
int stableState;
bool ledOn = false;
unsigned long lastRawChange;
unsigned long lastReport = 0;
unsigned long rawPresses = 0;
unsigned long debouncedPresses = 0;
bool reportPending = true;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastRaw = digitalRead(BUTTON_PIN);
  stableState = lastRaw;
  lastRawChange = millis();
  Serial.begin(115200);
  Serial.println("Button test: released=HIGH, pressed=LOW, debounce=30 ms");
  Serial.println("raw_state,stable_state,raw_presses,debounced_presses,led");
}

void loop() {
  const unsigned long now = millis();
  const int raw = digitalRead(BUTTON_PIN);

  if (raw != lastRaw) {
    if (lastRaw == HIGH && raw == LOW) {
      ++rawPresses;
    }
    lastRaw = raw;
    lastRawChange = now;
    reportPending = true;
  }

  // Accept a state only after the raw input stays unchanged for 30 ms.
  if (raw != stableState && now - lastRawChange >= DEBOUNCE_MS) {
    stableState = raw;
    if (stableState == LOW) {
      ++debouncedPresses;
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }
    reportPending = true;
  }

  // Rate-limit serial output while continuing to sample the button.
  if (reportPending && now - lastReport >= REPORT_MS) {
    Serial.print(raw == HIGH ? "HIGH" : "LOW");
    Serial.print(',');
    Serial.print(stableState == HIGH ? "HIGH" : "LOW");
    Serial.print(',');
    Serial.print(rawPresses);
    Serial.print(',');
    Serial.print(debouncedPresses);
    Serial.print(',');
    Serial.println(ledOn ? "ON" : "OFF");
    lastReport = now;
    reportPending = false;
  }
}
