# Reflection 5 — LEDs and light output

[Reflection index](README.md) · [Module evidence](../Module05/README.md) · [Portfolio](../README.md)

> **Draft for review** · Based on the 18 November 2026 record. Physical actions and observations are student-reported; Codex assisted with software, verification and documentation. [Prompts](TEMPLATE.md)

## Take-away

My main takeaway from these results is to verify the actual hardware before relying on a circuit description. The RGB module already had three resistors marked 151, so the current calculations needed 150 ohms rather than the workbook's 220-ohm discrete-LED circuit. I would check component markings and the measurement location before comparing results. [RGB report](../Module05/task2-rgb/README.md)

## What was good?

The single LED faded, the RGB module showed red, green and blue, and the strip responded at both ends and in eight-pixel white. The record separates these physical observations from command acknowledgments. The three RGB currents, derived from resistor voltage, were 7.53, 4.40 and 3.87 mA. The strip's reported white-load current was 0.09 A at luminance 80/255, excluding the ESP32. [Fade video](../Module05/task1-led/evidence/pwm-fade.mp4) · [Strip measurements](../Module05/task3-strip/power-budget.md)

## What was difficult?

The current-measurement attempt interrupted lighting, and I reported an accidental short circuit. After restoring direct supply and reconnecting USB, the strip lit again. A later series measurement gave 0.09 A. The original fault was not isolated, so restored operation does not identify a specific repair or rule out damage. I would disconnect power before inserting the meter and secure the series connections before reapplying power. [Troubleshooting](../Module05/task3-strip/README.md#troubleshooting-and-limitations)

## Exploration and show stoppers

The off-state indication was 0.00 A on the 10 A range. That indicates the range's limited resolution rather than proof of no idle current. Only eight pixels were available, so the longer-strip budgets are theoretical. An illuminated-strip photograph, total-system current measurement and optional animation/gamma comparison remain unavailable or unperformed. [Power budget](../Module05/task3-strip/power-budget.md)

## Interaction with peers and instructors

The session record says the professor suggested a different board, but I confirmed continuing with the original ESP32 Dev Module. No pod discussion, agreed-learning note or Discord share has been recorded. Specific peer feedback remains to be added after an actual exchange.

## How did you verify AI suggestions?

The component close-up corrected the initial 220-ohm assumption to 150 ohms. I supplied the resistor-voltage readings and observed colours; Codex calculated the currents and checked command acknowledgments. For the strip, firmware replies alone did not establish light output, so my physical confirmations remained necessary. The 90 mA measurement must be compared with the reduced-luminance configuration, not presented as a full-brightness result. [Resistor photograph](../Module05/task2-rgb/evidence/onboard-resistors.jpg)

## Help and extra work

Codex assisted with project setup, uploads, serial validation, troubleshooting and English documentation. Task 1 was labelled an exercise without AI in the workbook, but I explicitly delegated IDE operation; the record therefore identifies it as assisted work. Human help or contributions beyond the recorded board suggestion are not specified. This draft does not claim an unrecorded presentation or shared artifact.

## Learning-goal self-assessment

The recorded hardware results support PWM dimming, channel control, indexed strip output and a limited power comparison. [Later study notes](../Module05/study-notes.md) explain resistor sizing, frequency versus duty, gamma and the data path. They do not replace personal explanation, a measured PWM frequency, gamma comparison, total-system current or testing with Wi-Fi/BLE active.
