# Module 5: LEDs and Light as Output

[Portfolio](../README.md) · [Evidence](#experiment-records) · [Reflection 5](../Reflections/ref05.md) · [Review](../PORTFOLIO-REVIEW.md)

Student: Haocheng Feng. Course: HSBI Sensorik und Aktorik, WS 2026/27. Experiment date: 18 November 2026.

Three projects trace the path from PWM dimming to RGB channel control and addressable pixels. The student supplied physical observations and meter readings; Codex assisted with setup, uploads, serial checks and documentation.

## At a glance

| Item | Recorded scope |
| --- | --- |
| Projects | Single-LED fade, serial RGB control and an eight-pixel strip. |
| RGB currents | 7.53 / 4.40 / 3.87 mA, derived from resistor-voltage readings. |
| Strip current | 0.09 A at white, luminance 80/255; ESP32 excluded. |
| Remaining evidence | Working-strip media, actual pod exchange and course sharing. |

## Learning Goals

Goal numbering follows the [Module 5 workbook](https://github.com/iotempire/iotempire-teaching/blob/43ee9338bdec8c83d568d07a27174865cb453552/full-classes/hsbi-sensors-actuators-10d/modules/05-leds-and-light-output.md#-learning-goals). The workbook identifies its task text as provisional. Status below describes the available evidence, not a claim that every learning goal has been fully assessed.

| Goal | Experiment | Evidence | Status and limits |
| --- | --- | --- | --- |
| **LG1 · LED current limiting.** Relate forward voltage, resistance and current. | Tasks 1–2 | [RGB resistor identification and current calculations](task2-rgb/README.md#verification-and-current-measurements) | Three onboard 150-ohm resistors identified; currents calculated from measured resistor voltages. An [illustrative target-current design](study-notes.md#current-limiting-and-forward-voltage) is documented; Task 1 current was not measured and personal understanding has not been independently assessed. |
| **LG2 · PWM.** Control brightness and explain duty cycle, frequency and gamma. | Task 1 | [Fade report](task1-led/README.md#pwm-behaviour-and-observed-result), [source](task1-led/task1-led.ino), [video](task1-led/evidence/pwm-fade.mp4) | Fade demonstrated and duty cycle documented. [Frequency and gamma study notes](study-notes.md#duty-cycle-frequency-and-gamma) are now available; frequency and gamma were not experimentally compared. |
| **LG3 · RGB mixing.** Control channels and explain additive colour. | Task 2; Task 3 white output | [RGB photographs and measurements](task2-rgb/README.md), [eight-pixel observations](task3-strip/README.md#verification-and-evidence) | Separate red, green and blue outputs confirmed; eight-pixel white confirmed. A mixed-colour series on the discrete RGB module was not recorded. |
| **LG4 · Reproducible workflow.** Use PlatformIO and AI assistance, then verify hardware. | Tasks 2–3 | Each project's platformio.ini, AGENTS.md, source and serial evidence | Both projects built, uploaded and checked on the original ESP32 Dev Module. Task 1 used Arduino IDE. Code, instructions and evidence are packaged in this repository; course sharing remains unrecorded. |
| **LG5 · Addressable pixels.** Select pixels and choose hardware-driven data output. | Task 3 | [Code and driver](task3-strip/README.md#driver-and-brightness), [first/last-pixel evidence](task3-strip/README.md#verification-and-evidence) | Pixel 0 and pixel 7 verified, with clear and all-eight white. RMT channel 0 selected and the [data path explained](study-notes.md#additive-colour-and-addressable-data); coexistence with active Wi-Fi/BLE was not tested. |
| **LG6 · Power budget.** Compare calculated and measured demand with supply capacity. | Task 3 | [Power budget and measurements](task3-strip/power-budget.md) | Eight-pixel white measured at 0.09 A with luminance 80/255; off indication 0.00 A. Larger lengths calculated only. ESP32 consumption and USB-source capacity were not measured. |

## Experiment records

| Task | Report and code | Result |
| --- | --- | --- |
| Task 1 · Single LED | [Report](task1-led/README.md) · [Arduino sketch](task1-led/task1-led.ino) | GPIO16 PWM fade restored and confirmed; original video retained. |
| Task 2 · RGB LED | [Report](task2-rgb/README.md) · [Firmware](task2-rgb/src/main.cpp) · [PlatformIO settings](task2-rgb/platformio.ini) | Serial RGB control and invalid-input checks passed. Derived currents: red 7.53 mA, green 4.40 mA, blue 3.87 mA. |
| Task 3 · Eight-pixel strip | [Report](task3-strip/README.md) · [Firmware](task3-strip/src/main.cpp) · [Power budget](task3-strip/power-budget.md) | Single-pixel RGB, first/last indexing, eight-pixel white and clear confirmed; strip current measured at reduced luminance. |
| Task 4 · Repository preparation | This index, the three project folders and the linked evidence | Code, documentation and evidence are organized together in this repository. Course sharing is not yet recorded. |
| Task 5 · Exchange and evidence | [Remaining work](#remaining-work) | Pod discussion, agreed learning and Discord artifact sharing have not been recorded. |

## Study log

**Task 1.** A red LED faded up and down using GPIO16 PWM. Duty cycle is the fraction of each PWM period for which the output is on. The sketch's nominal up/down duration is 4.096 seconds plus overhead; the video is evidence of fading, not a timing measurement. The workbook labels Task 1 as an exercise without AI; in this session the student explicitly delegated IDE operation and troubleshooting to Codex, so it is recorded as assisted work.

**Task 2.** The RGB module responded to serial commands for red, green and blue. Its three resistors were marked 151, corresponding to nominal 150 ohms. Across them, the student measured 1.13 V, 0.66 V and 0.58 V, giving 7.53 mA, 4.40 mA and 3.87 mA. The module operated with its common minus pin at GND and COMMON_ANODE=false, consistent with common cathode. Equal nominal resistances did not produce equal currents.

**Task 3.** The eight-pixel strip accepted index R G B and clear. GPIO16 sends the data through a 220-ohm resistor, with 5 V supply and common GND. The library uses RMT channel 0 and SetLuminance(80). White output across all eight pixels produced a reported 0.09 A in the strip supply branch; after clear the 10 A meter range indicated 0.00 A. The ESP32 was excluded from this current path. Only eight pixels were available, so longer strips appear solely as calculated budgets.

**AI claim checked and corrected.** The initial RGB instructions assumed the workbook's three 220-ohm resistors. The close-up photograph showed three onboard 150-ohm resistors, and the record and calculations were corrected. A serial acknowledgment confirms program handling; it does not itself prove that the LED lit. Physical observations were recorded separately. Calculation results are distinguished from meter readings throughout.

**Display rationale.** Static single-pixel red, green and blue distinguish the channels and endpoints; eight-pixel white provides a repeatable load pattern; clear provides the off comparison. No animation or optional extension was performed. Additive mixing means combining channel light; equal commanded RGB values need not produce equal currents or a colour-balanced white.

## Remaining work

- Add a photograph or video of the working eight-pixel output. Existing strip photographs show labels and controller wiring, not illuminated output.
- Add a meter-display/setup photograph if available; current values are student-reported, with the supply-branch location explicitly confirmed.
- Complete or discuss PWM frequency/gamma, target-current resistor selection, and mixed colours on the RGB module where required for assessment.
- Measure total USB supply current if a controller-plus-strip comparison is needed. Do not describe the 90 mA strip measurement as total system demand.
- Record the pod's actual discussion and agreed learning; no discussion or feedback is invented here.
- Share the repository link and selected artifact in the course channel when requested.

[Workbook](https://github.com/iotempire/iotempire-teaching/blob/43ee9338bdec8c83d568d07a27174865cb453552/full-classes/hsbi-sensors-actuators-10d/modules/05-leds-and-light-output.md) · [Portfolio home](../README.md)

## Later study and reflection

[LED theory and supply-decision notes](study-notes.md) · [Reflection 5 — draft for review](../Reflections/ref05.md). These are documentation additions, not new bench evidence.
