// Classic ESP32: connect TX2 / GPIO17 to RX2 / GPIO16 with power off.
// Serial Monitor: 115200 baud, New Line. UART2: 9600 baud, 8N1.
#include <cstring>

constexpr int RX_PIN = 16;
constexpr int TX_PIN = 17;
constexpr unsigned long UART_BAUD = 9600;
constexpr unsigned long TIMEOUT_MS = 2000;
constexpr size_t BUFFER_SIZE = 80;
char inputLine[BUFFER_SIZE] = {};
char receivedLine[BUFFER_SIZE] = {};
char expectedLine[BUFFER_SIZE] = {};
size_t inputLength = 0;
size_t receivedLength = 0;
bool waitingForEcho = false;
unsigned long sentAt = 0;

void transmitLine() {
  if (inputLength == 0) return;
  inputLine[inputLength] = '\0';
  if (waitingForEcho) {
    Serial.println("BUSY: wait for the previous result");
    inputLength = 0;
    return;
  }
  while (Serial2.available()) Serial2.read();
  receivedLength = 0;
  strcpy(expectedLine, inputLine);
  waitingForEcho = true;
  sentAt = millis();
  Serial.print("TX UART2@9600: ");
  Serial.println(expectedLine);
  Serial2.println(expectedLine);
  inputLength = 0;
}

void setup() {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  Serial.begin(115200);
  Serial2.begin(UART_BAUD, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("BOOT: Module 2 Task 1 - UART2 loopback");
  Serial.println("Wire GPIO17 (TX2) -> GPIO16 (RX2), 3.3 V logic");
  Serial.println("READY: send one short ASCII line; monitor=115200, UART2=9600 8N1");
}

void loop() {
  while (Serial.available()) {
    const char c = char(Serial.read());
    if (c == '\r') continue;
    if (c == '\n') {
      transmitLine();
    } else if (inputLength < BUFFER_SIZE - 1) {
      inputLine[inputLength++] = c;
    } else {
      inputLength = 0;
      Serial.println("INPUT TOO LONG: use fewer than 80 ASCII characters");
    }
  }

  while (Serial2.available()) {
    const char c = char(Serial2.read());
    if (c == '\r') continue;
    if (c == '\n') {
      receivedLine[receivedLength] = '\0';
      Serial.print("RX UART2@9600: ");
      Serial.println(receivedLine);
      if (waitingForEcho) {
        Serial.println(strcmp(receivedLine, expectedLine) == 0
                         ? "PASS: received line matches transmitted line"
                         : "FAIL: received line differs from transmitted line");
        waitingForEcho = false;
      } else {
        Serial.println("UNEXPECTED RX: no line awaiting confirmation");
      }
      receivedLength = 0;
    } else if (receivedLength < BUFFER_SIZE - 1) {
      receivedLine[receivedLength++] = c;
    } else {
      receivedLength = 0;
      waitingForEcho = false;
      Serial.println("FAIL: received line exceeds buffer");
    }
  }

  if (waitingForEcho && millis() - sentAt >= TIMEOUT_MS) {
    waitingForEcho = false;
    receivedLength = 0;
    Serial.println("TIMEOUT: no complete echo within 2000 ms; check the TX2-to-RX2 jumper");
  }
}
