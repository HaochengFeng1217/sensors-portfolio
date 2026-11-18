# Task 3 — Addressable LED strip

[Module 5](../README.md) · [Portfolio](../../README.md) · [Study notes](../study-notes.md)

Date: 2026-11-18. Status: compiled and uploaded; serial validation, first/last pixel tests, RGB colours, eight-pixel white output and clear confirmed. Eight-pixel supply-current readings recorded.

## Hardware

The operator is retaining the original classic ESP32 Dev Module (`esp32dev`). The photographed strip input is labelled GND, DIN, 4–7VDC, GND; the other end is labelled DOUT. The operator confirmed eight pixels. Red, green and blue observations are consistent with the configured GRB colour order. The operator reported adding a 220-ohm resistor in series with DIN.

| Strip input | Connection |
| --- | --- |
| GND | ESP32 GND |
| DIN | GPIO16 / RX2 through 220 ohms |
| 4–7VDC | USB 5 V / board VIN |
| Second GND | May remain unconnected |

Disconnect Task 2 RGB wiring. Leave DOUT unconnected. Never power the strip from a GPIO or the 3.3 V pin. The available wiring photo shows only the controller side. Before deployment, the operator explicitly confirmed VIN to 4–7VDC, common GND, and DIN through 220 ohms to GPIO16 / RX2.

## Driver and brightness

NeoPixelBus 2.8.4, Espressif32 8.0.0, Arduino-ESP32 3.3.12. The method is `NeoEsp32Rmt0Ws2812xMethod`, using RMT hardware channel 0 on GPIO16. This hardware waveform method follows the course requirement and avoids software bit-banging. Compilation reports a legacy RMT driver deprecation warning; compilation succeeds. Actual operation with Wi-Fi/BLE has not been tested.

`NeoPixelBusLg` provides `SetLuminance(80)`. `NeoGammaNullMethod` explicitly disables gamma correction for this baseline. Startup clears all eight pixels. The luminance cap reduces output but is not a measured or closed-loop current limit.

[NeoPixelBus ESP32 methods](https://github.com/Makuna/NeoPixelBus/wiki/ESP32-NeoMethods)

## Build and use

```sh
pio run -t compiledb
pio run
pio run -t upload --upload-port /dev/cu.usbserial-0001
pio device monitor --port /dev/cu.usbserial-0001
```

Serial speed: 115200 baud. Send one command per line:

```text
0 255 0 0
7 0 0 255
clear
```

Pixel indices are 0–7. RGB values must be integers in 0–255. Missing, extra, fractional, out-of-range and overlong input is rejected without applying a new colour. Successful pixel commands echo `APPLIED index=... R=... G=... B=... luminance=80`; clearing echoes `CLEARED`.

## Power budget and measurements

[Full power table and measurement conditions](power-budget.md)

Eight pixels at white, luminance 80/255: 0.09 A reported on the UT131C in the 10 A DC range. After clear: 0.00 A indicated, limited by the meter range. The student confirmed the meter was in series in the VIN-to-strip positive supply path, excluding ESP32 current. Only eight pixels were available; 30, 60 and 144 pixels are budget calculations only.

## Verification and evidence

Upload succeeded with flash hash verification and an RTS reset. Eight serial cases passed: clear, index out of range, RGB out of range, fractional input, missing value, extra value, overlong line and first-pixel red. [Serial verification](evidence/serial-first-check.txt)

The operator confirmed:

- Pixel 0, nearest DIN, lit red while all other pixels were off.
- Pixel 7, farthest from DIN, lit blue, then green, while all others were off.
- All eight pixels lit white at luminance 80/255.
- All pixels went off after clear.
- White-load strip current was 0.09 A and the off-state indication was 0.00 A.

[Last-pixel commands](evidence/serial-last-pixel.txt), [green command](evidence/serial-green-pixel.txt), [white commands](evidence/serial-eight-white.txt), [clear for idle comparison](evidence/serial-idle-comparison.txt).

The startup capture contained garbled bytes and a partial ESP32 boot message; a clean TASK3_STRIP_READY banner was not captured. Subsequent commands returned clean expected responses. Wi-Fi/BLE coexistence has not been tested.

## Troubleshooting and limitations

During current-measurement setup the operator reported no light and later reported an accidental short circuit. The strip supply measured 5.17 V during troubleshooting. Data and GND connections were reseated, and intermittent serial-opening errors required USB reconnection. Following restoration of direct power and acknowledged commands, the operator confirmed that first-pixel red and eight-pixel white operation returned. The exact fault was not diagnosed; restored light output does not establish the absence of latent damage.

Subsequently the operator reported the loaded-current and off-state indications and confirmed the series measurement location. Earlier zero readings during failed lighting attempts are not accepted as white-load current measurements.

Remaining portfolio work: add a photograph or video of the working eight-pixel strip, optionally corroborate the meter setup and readings with photographs, complete any chosen optional extension and actual sharing tasks. The static-display rationale and study log are already documented in the [module index](../README.md). Larger-strip physical current measurements were not performed because only eight pixels were available.

## Project files

[Firmware](src/main.cpp) · [PlatformIO settings](platformio.ini) · [Project instructions](AGENTS.md) · [Strip labels](evidence/strip-labels.jpg) · [Controller wiring](evidence/controller-wiring.jpg) · [Module index](../README.md)
