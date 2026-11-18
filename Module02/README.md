# Module 2: Buses and I2C

**Haocheng Feng** · HSBI Sensorik und Aktorik · Started 28 October 2026

[Portfolio](../README.md) · [Evidence](#task-1-simple-pins-pwm-uart-and-a-divider) · [Reflection](../Reflections/ref02.md) · [Review](../PORTFOLIO-REVIEW.md)

Interface study, UART loopback and divider records, alongside explicitly credited I²C experiments by Zhenning Yu.

## At a glance

| Focus | Recorded evidence |
| --- | --- |
| **Own bench result** | The UART2 loopback returned the transmitted string exactly. Divider input measured 3.316 V; output remains unmeasured. |
| **Study material** | SPI research, pin classification and a consolidated interface comparison, with notes supplied from other pods. |
| **Contribution boundary** | Zhenning performed the linked I²C scan, register-read, shared-bus and logic-analyzer experiments. Haocheng's hands-on role in those tests is unverified. |

## Learning Goals

Goal numbers follow the [Module 2 workbook](https://github.com/iotempire/iotempire-teaching/blob/129d3f0ab4d9acd43e1659769cf4777e4e2aa41e/full-classes/hsbi-sensors-actuators-10d/modules/02-i2c-and-sensor-addressing.md#-learning-goals). Status describes the recorded evidence and identifies work carried out by Zhenning Yu.

| Workbook goal | Experiment or study | Evidence | Status |
| --- | --- | --- | --- |
| **LG1 · Interfaces.** Compare digital, analog and PWM pins with RS-232/UART, RS-485, Modbus RTU, CAN, I²C/I³C, SPI and OneWire by wiring, voltage, signaling, drive, speed, length, topology, uses and origin. Explain why PWM is not a bus. | Haocheng · Tasks 1–2, pin comparison, UART loopback and SPI survey | [Pin classification and PWM notes](pins-and-dividers.md), [UART log](uart-loopback/evidence/observed-loopback.txt) and [SPI profile](bus-spi.md). | A [consolidated comparison](bus-comparison.md) is now documented; Haocheng's own SPI kit demonstration and pitch remain unverified. |
| **LG2 · I²C principles.** Explain SDA/SCL, open-drain signaling, pull-ups, addressing, ACK/NACK, repeated start and clock stretching. | Haocheng · I²C study notes. Zhenning · Tasks 5 and 9 | [Pull-up notes](#task-2-bus-survey-and-pitch--in-progress), [address scan][yu-task-5] and [decoded NACK][yu-task-9]. | Partial. The notes and teammate capture cover pull-ups, addressing and acknowledgments. Repeated START and clock stretching are covered by [later sourced theory notes](bus-comparison.md#i²c-transaction-concepts-added-during-review); no new capture or hands-on test is claimed. |
| **LG3 · Scanning.** Wire an I²C bus, scan it and identify the connected devices by address. | Zhenning · Tasks 5 and 7 | [Single-device scan][yu-task-5] and [two-device scan][yu-task-7] identify the LCD1602 and SE95. | Demonstrated by Zhenning. Haocheng's hands-on scan is unverified. |
| **LG4 · Registers.** Read a sensor through a library and directly from its raw registers. | Zhenning · Task 6 | [SE95 comparison][yu-task-6] shows agreement between direct conversion and the library. | Demonstrated by Zhenning. Haocheng's hands-on register read is unverified. |
| **LG5 · Shared bus.** Operate two devices on one bus and resolve an address conflict. | Zhenning · Task 7 | [LCD1602 and SE95 on shared SDA/SCL][yu-task-7] respond at different addresses. | Partial teammate evidence. Address-conflict resolution is not documented; the corresponding Task 8 experiment is optional. |
| **LG6 · Instrumentation.** Build and evaluate a low-cost ESP32 scope or logic analyzer and agree on one or two class tools for bus debugging. | Zhenning · Task 9 | [ESP32 and PulseView test][yu-task-9] covers a square wave and I²C decoding. | Partial teammate evidence. Class-wide tool selection is unverified. |

## Task 1: Simple pins, PWM, UART and a divider

[Classification table, calculations and UART notes](pins-and-dividers.md) · [UART loopback firmware](uart-loopback/uart-loopback.ino)

One UART hardware string test passed on the classic ESP32, with matching TX and RX output preserved in the [screenshot](uart-loopback/evidence/loopback-01.png) and [text record](uart-loopback/evidence/observed-loopback.txt). The divider-input reading was 3.316 V. Its output and the 5 V-input scenario remain unmeasured, so Task 1 is incomplete.

## Task 2: Bus survey and pitch — in progress

The instructor directed the class to begin Task 2 before the divider output was measured. The student identified SPI as the assigned bus. A sourced [SPI profile](bus-spi.md) and [research questions with source checks](bus-spi-research.md) have been prepared. The physical kit example, device-specific settings, pod discussion and presentation remain to be verified or recorded. [Notes from other pods' pitches](other-pods-notes.md) already cover RS-485, RS-232, Modbus RTU, CAN and I²C/I³C. They are consolidated with SPI, the pin notes and later OneWire study in the [comparison table](bus-comparison.md).

**I²C study note.** Devices pull a shared line low or release it; pull-ups restore the high level. Pull-up voltage and sink current must suit the connected devices. This explanation is conceptual, not evidence of a completed circuit or pod discussion.

Haocheng's documented work here covers Tasks 1–2. The later experiments linked below are Zhenning's contributions.

## Teammate contributions

Zhenning Yu carried out and documented the experiments below in his own portfolio. The summaries describe his results and serve as references for Haocheng's study of I²C.

| Task in Zhenning's portfolio | Recorded result |
| --- | --- |
| [Task 5 · I²C bus scan][yu-task-5] | The LCD1602 acknowledged address `0x27` in a single-device scan. |
| [Task 6 · Library and register reads][yu-task-6] | Direct decoding of the SE95 temperature register and the library both reported `26.938 °C`. |
| [Task 7 · Two devices on one bus][yu-task-7] | The LCD1602 (`0x27`) and SE95 (`0x4F`) shared SDA and SCL and were addressed separately. The display showed the sensor's reading. |
| [Task 9 · ESP32 logic analyzer][yu-task-9] | PulseView captured a square wave and decoded a separate I²C write to `0x29`. The target address was unoccupied and the transaction returned a NACK. |

[Reflection 2 — draft for review](../Reflections/ref02.md) · [Portfolio home](../README.md)

[yu-task-5]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/main/Module02/README.md#task-5-i2c-bus-scan
[yu-task-6]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/main/Module02/README.md#task-6-library-and-register-reading
[yu-task-7]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/main/Module02/README.md#task-7-two-devices-on-one-bus
[yu-task-9]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/main/Module02/README.md#task-9-build-and-test-an-esp32-logic-analyzer

## Documentation review — 18 November 2026

[Interface comparison and I²C transaction notes](bus-comparison.md) consolidate existing evidence and distinguish optional experiments from missing core work. The comparison is a written study addition, not a new presentation.
