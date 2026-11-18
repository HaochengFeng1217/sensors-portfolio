#include <Arduino.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

constexpr int RED_PIN = 16;
constexpr int GREEN_PIN = 17;
constexpr int BLUE_PIN = 18;
constexpr bool COMMON_ANODE = false;
constexpr size_t LINE_CAPACITY = 96;
char lineBuffer[LINE_CAPACITY];
size_t lineLength = 0;
bool lineOverflow = false;

int pwmValue(int value) {
  return COMMON_ANODE ? 255 - value : value;
}

void applyColor(int red, int green, int blue) {
  analogWrite(RED_PIN, pwmValue(red));
  analogWrite(GREEN_PIN, pwmValue(green));
  analogWrite(BLUE_PIN, pwmValue(blue));
  Serial.printf("APPLIED R=%d G=%d B=%d\n", red, green, blue);
}

void processLine(char* line) {
  int values[3];
  char* cursor = line;
  for (int index = 0; index < 3; ++index) {
    while (isspace(static_cast<unsigned char>(*cursor))) {
      ++cursor;
    }
    errno = 0;
    char* end;
    const long value = strtol(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        (*end != '\0' && !isspace(static_cast<unsigned char>(*end)))) {
      Serial.println("ERROR: enter exactly three decimal integers: R G B");
      return;
    }
    values[index] = static_cast<int>(constrain(value, 0L, 255L));
    cursor = end;
  }
  while (isspace(static_cast<unsigned char>(*cursor))) {
    ++cursor;
  }
  if (*cursor != '\0') {
    Serial.println("ERROR: enter exactly three decimal integers: R G B");
    return;
  }
  applyColor(values[0], values[1], values[2]);
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  applyColor(0, 0, 0);
  Serial.println("TASK2_RGB_READY: enter R G B (0-255). Pins 16,17,18; common cathode.");
}

void loop() {
  while (Serial.available() > 0) {
    const char incoming = static_cast<char>(Serial.read());
    if (incoming == '\r') {
      continue;
    }
    if (incoming == '\n') {
      lineBuffer[lineLength] = '\0';
      if (lineOverflow) {
        Serial.println("ERROR: command too long; use R G B");
      } else if (lineLength > 0) {
        processLine(lineBuffer);
      }
      lineLength = 0;
      lineOverflow = false;
    } else if (lineLength < LINE_CAPACITY - 1) {
      lineBuffer[lineLength++] = incoming;
    } else {
      lineOverflow = true;
    }
  }
  delay(1);
}
