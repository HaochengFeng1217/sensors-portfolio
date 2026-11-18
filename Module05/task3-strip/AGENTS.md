# Addressable LED lab

- Actual board: original classic ESP32 Dev Module, PlatformIO esp32dev.
- Eight WS2812B-compatible RGB pixels, GRB order; verify physical count and colour order.
- DIN on GPIO16 through the operator's 220-ohm data resistor. Disconnect Task 2 RGB wiring.
- Strip power from USB 5 V / VIN, common GND. Never use GPIO or 3.3 V for strip power.
- Use makuna/NeoPixelBus and an ESP32 hardware method, never default to FastLED.
- Keep SetLuminance at 80 or lower; start with pixels cleared.
- Serial 115200: index R G B or clear, strict bounds and acknowledgments.
- Run pio run -t compiledb after dependency changes, then pio run.
- Records in English. Distinguish compilation, upload, acknowledgments and physical observations.
- Do not commit .pio or compile_commands.json.
