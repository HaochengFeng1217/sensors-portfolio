# RGB LED lab

- Hardware is the classic ESP32 Dev Module used for Task 1. PlatformIO board is esp32dev.
- Actual hardware: RGB breakout with three onboard resistors marked 151 (nominal 150 ohms). R1/red connects to GPIO16 (RX2), R2/green to GPIO17 (TX2), R3/blue to GPIO18. The workbook uses 220 ohms per discrete LED channel; document this difference.
- Common cathode connects to GND. COMMON_ANODE defaults to false. Confirm the physical component before changing this flag and wiring.
- Serial runs at 115200 baud. Accept three decimal RGB integers, clamp each to 0–255, echo applied values and reject malformed or overlong lines.
- Run pio run -t compiledb after dependency changes, then pio run.
- Keep .pio and compile_commands.json out of commits.
- Record physical observations and channel-current measurements in English.
