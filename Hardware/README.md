# Hardware observed in the lab records

[Portfolio](../README.md) · [Module records](../README.md#modules) · [Completeness review](../PORTFOLIO-REVIEW.md)

Updated: 18 November 2026. This inventory describes documented use or photographs; it does not establish ownership, kit checkout, or that every item is currently available.

| Part / instrument | Observed quantity | Evidence and limits |
| --- | --- | --- |
| Classic ESP32 Dev Module | At least one | Used in Modules 1–3 and 5; [controller photograph](../Module05/task3-strip/evidence/controller-wiring.jpg). Later experiments reused GPIO16. |
| Breadboard and jumper wires | At least one setup | Visible in the [Module 5 wiring](../Module05/task3-strip/evidence/controller-wiring.jpg). |
| Red LED | One in Task 1 setup | [Fade video](../Module05/task1-led/evidence/pwm-fade.mp4); reported series resistance 220 ohms, not independently measured. |
| RGB LED breakout | One | [Three 151-marked resistors](../Module05/task2-rgb/evidence/onboard-resistors.jpg), nominally 150 ohms each. |
| Addressable RGB strip | One, eight pixels | [Input/output labels](../Module05/task3-strip/evidence/strip-labels.jpg), operator-confirmed eight pixels; DIN series resistor reported as 220 ohms. |
| DS18B20 waterproof-style probe | One tested | [ROM ID and thermal measurements](../Module03/ds18b20/README.md); multiple probes were not tested. |
| LDR and fixed divider resistor | One sensor setup | [Module 3 characterization](../Module03/ldr-characterization/README.md); resistor nominally 10 kohms. |
| Rotary potentiometer | One test setup | [ADC experiment](../Module01/potentiometer-adc/README.md); total resistance not independently verified here. |
| Pushbutton | One test setup | [Debounce record](../Module01/button-debounce/README.md). |
| UNI-T UT131C | One reported instrument | [Eight-pixel current measurements](../Module05/task3-strip/power-budget.md); no instrument serial number or calibration certificate recorded. |
| MH-ET LIVE ESP32 MiniKit V2.0 | One photographed, not used for Module 5 tests | Considered during the session; the student explicitly retained the original ESP32 Dev Module. |

HC-SR04, HD-38 and BMI270 Module 4 experiments are documented by Zhenning Yu in the [credited teammate record](../Module04/README.md). They are not claimed as Haocheng's equipment or hands-on tests.

## Connectivity notes

The ESP32 examples use 3.3 V GPIO logic. Strip power uses the USB 5 V/VIN path, not a GPIO or 3.3 V output. Grounds must be common for signal interpretation. Confirm board and peripheral voltage/current limits before changing wiring. The exact divider orientation and measurement position are recorded in each experiment rather than assumed from wire colour.

[Portfolio home](../README.md)
