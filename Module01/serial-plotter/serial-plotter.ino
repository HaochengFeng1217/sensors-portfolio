// LED: GPIO18 -> 220 ohm resistor -> LED anode; cathode -> GND.
// Button: GPIO19 -> normally open button -> GND; internal pull-up enabled.
// Serial Plotter: 115200 baud, three numerical traces.
constexpr int LED_PIN = 18;
constexpr int BUTTON_PIN = 19;
constexpr unsigned long DEBOUNCE_MS = 30;
constexpr unsigned long SAMPLE_MS = 100;

int lastRaw;
int stableState;
bool ledOn = false;
unsigned long lastRawChange;
unsigned long lastSample = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastRaw = digitalRead(BUTTON_PIN);
  stableState = lastRaw;
  lastRawChange = millis();
  Serial.begin(115200);
}

void loop() {
  const unsigned long now = millis();
  const int raw = digitalRead(BUTTON_PIN);

  if (raw != lastRaw) {
    lastRaw = raw;
    lastRawChange = now;
  }

  if (raw != stableState && now - lastRawChange >= DEBOUNCE_MS) {
    stableState = raw;
    if (stableState == LOW) {
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }
  }

  // Schedule approximately 10 samples per second without blocking the loop.
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;
    Serial.print("Raw:");
    Serial.print(raw == HIGH ? 1 : 0);
    Serial.print(",Debounced:");
    Serial.print(stableState == HIGH ? 1 : 0);
    Serial.print(",LED:");
    Serial.println(ledOn ? 1 : 0);
  }
}
