constexpr int LED_PIN = 16;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("GPIO16 HIGH: LED should be on for 2 seconds");
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("GPIO16 LOW: LED should be off for 2 seconds");
  delay(2000);
}
