// External LED: GPIO18 -> 220-330 ohm resistor -> LED anode.
// Connect the LED cathode to GND.
constexpr int LED_PIN = 18;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED=ON");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED=OFF");
  delay(500);
}
