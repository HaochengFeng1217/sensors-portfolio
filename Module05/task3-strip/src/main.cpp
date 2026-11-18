#include <Arduino.h>
#include <NeoPixelBusLg.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

constexpr uint16_t PIXEL_COUNT = 8;
constexpr uint8_t DATA_PIN = 16;
constexpr uint8_t LUMINANCE = 80;
NeoPixelBusLg<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod, NeoGammaNullMethod> strip(PIXEL_COUNT, DATA_PIN);
char line[96];
size_t used = 0;
bool overflow = false;

void handleLine(char* input) {
  while (isspace(static_cast<unsigned char>(*input))) ++input;
  char* end = input + strlen(input);
  while (end > input && isspace(static_cast<unsigned char>(end[-1]))) --end;
  *end = '\0';
  if (!strcmp(input, "clear")) {
    strip.ClearTo(RgbColor(0, 0, 0));
    strip.Show();
    Serial.println("CLEARED");
    return;
  }
  long values[4];
  char* cursor = input;
  for (int i = 0; i < 4; ++i) {
    while (isspace(static_cast<unsigned char>(*cursor))) ++cursor;
    errno = 0;
    char* next;
    values[i] = strtol(cursor, &next, 10);
    if (next == cursor || errno == ERANGE ||
        (*next && !isspace(static_cast<unsigned char>(*next)))) {
      Serial.println("ERROR: use index R G B or clear");
      return;
    }
    cursor = next;
  }
  while (isspace(static_cast<unsigned char>(*cursor))) ++cursor;
  if (*cursor || values[0] < 0 || values[0] >= PIXEL_COUNT ||
      values[1] < 0 || values[1] > 255 || values[2] < 0 || values[2] > 255 ||
      values[3] < 0 || values[3] > 255) {
    Serial.println("ERROR: index 0..7 and RGB 0..255 required");
    return;
  }
  strip.SetPixelColor(values[0], RgbColor(values[1], values[2], values[3]));
  strip.Show();
  Serial.printf("APPLIED index=%ld R=%ld G=%ld B=%ld luminance=%u\n",
                values[0], values[1], values[2], values[3], LUMINANCE);
}

void setup() {
  Serial.begin(115200);
  strip.Begin();
  strip.SetLuminance(LUMINANCE);
  strip.ClearTo(RgbColor(0, 0, 0));
  strip.Show();
  Serial.println("TASK3_STRIP_READY: 8 pixels, DIN=16, luminance=80; index R G B or clear");
}

void loop() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());
    if (c == '\r') continue;
    if (c == '\n') {
      if (overflow) Serial.println("ERROR: line too long");
      else { line[used] = '\0'; handleLine(line); }
      used = 0;
      overflow = false;
    } else if (c == '\0' || used >= sizeof(line) - 1) {
      overflow = true;
    } else if (!overflow) {
      line[used++] = c;
    }
  }
}
