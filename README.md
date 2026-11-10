# Sensorik und Aktorik Portfolio

Personal portfolio for HSBI, Campus Gütersloh, WS 2026/27.

- GitHub account: [HaochengFeng1217](https://github.com/HaochengFeng1217)
- Full name: Haocheng Feng
- Partner: [Zhenning Yu](https://github.com/LudwigMo/sensorik-aktorik-portfolio)
- Template: [iotempire/iot-portfolio-template](https://github.com/iotempire/iot-portfolio-template)

## Checkpoint 1 — Modules 1–3

| Module | Learning goals | Key evidence | Reflection draft |
| --- | --- | --- | --- |
| [1 · Foundations and measurement](Module01/README.md) | [LG1–LG6](Module01/README.md#learning-goals) | [Potentiometer ADC](Module01/potentiometer-adc/README.md) reached codes 0–4095 at 12 bits and 0–1023 at 10 bits. The [LDR divider](Module01/ldr-divider/README.md) records 120 readings over 12 trials under four qualitative lighting conditions. | [Module 1 draft](Reflections/ref01.md) |
| [2 · Buses and I²C](Module02/README.md) | [LG1–LG6](Module02/README.md#learning-goals) | Haocheng Feng's [UART loopback](Module02/uart-loopback/evidence/observed-loopback.txt) returned the transmitted string. The [SPI profile](Module02/bus-spi.md) is research evidence. Zhenning Yu's [I²C and logic-analyzer experiments](Module02/README.md#teammate-contributions) are credited separately. | [Module 2 draft](Reflections/ref02.md) |
| [3 · Characterization and calibration](Module03/README.md) | [LG1–LG5](Module03/README.md#learning-goals) | The [ADC calibration](Module03/adc-calibration/README.md) reduced the residual from +21.72 mV to +3.05 mV at one fresh validation point. The [DS18B20 thermal traces](Module03/ds18b20/README.md) show a faster response in water than in air for the recorded setup. [Decision hysteresis](Module03/noise-and-filtering/ldr-hysteresis/README.md) reduced five switches to one on the same LDR trace. The reset was outside the capture. | [Module 3 draft](Reflections/ref03.md) |

Haocheng Feng maintains this portfolio. Zhenning Yu carried out and documented the linked Module 2 Tasks 5, 6, 7 and 9. The [Module 2 contribution notes](Module02/README.md#teammate-contributions) identify his evidence by task. The [Module 3 study log](Module03/README.md#scope-and-assistance) records the assistance used in that module.

## Current status

Module 0 contains the documented Wokwi potentiometer/LED experiment, questions 1–8 and sensor datasheet notes, including the proposed touch-confirmed proximity storage box. Personal review, supplementary study notes and remaining preparation checks are still pending.

Module 1 contains the hardware experiment records through Task 4, including programs, photographs, screenshots, readings and measurement limitations. Module 1 Task 5 filtering remains unperformed. In Module 2, the divider output measurement and SPI presentation remain pending. The three reflection drafts include prompts for Haocheng to confirm personal participation and feedback.

Module 3 now includes English lab records for LDR characterization, DS18B20 thermal response, ADC calibration, and Task 5.1–5.5 noise/filtering evidence. Raw logs, unsuccessful attempts, plots and firmware are retained. The module checklist identifies remaining experiments and limitations, including the unmeasured hysteresis return/reset cycle.

## Contents

- [Module 0: Pre-study](pre-study/README.md)
- [Module 1: experiment records — Tasks 1–4](Module01/README.md)
- [Module 2: UART, divider and SPI research in progress](Module02/README.md)
- [Module 3: sensor characterization and calibration](Module03/README.md)
- [New module template](ModuleNN.md)
- [Working-day reflections](Reflections/README.md)
- [Hardware inventory](Hardware/README.md)

## Course references

- [HSBI Sensors and Actuators workbook](https://github.com/iotempire/iotempire-teaching/tree/main/full-classes/hsbi-sensors-actuators-10d)
- [Pre-study guide](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/pre-study.md)
- [Syllabus](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/syllabus.md)

The uploaded LMS PDFs are dated 2026-09-25, revision 31aa6ca.
The live workbook can change; local scheduling and announcements come from the course LMS.

## Documentation

Write notes in English, German, or a mixture. Record code, diagrams, evidence, sources,
and reflections as the work is performed. Link peer contributions with an explanation.
Keep Markdown and images in the portfolio; link external documents and videos.

