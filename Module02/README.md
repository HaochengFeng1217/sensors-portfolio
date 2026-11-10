# Module 2: Buses and I2C

Student: Haocheng Feng. Started: 28 October 2026.

## Learning Goals

Goal numbers follow the [Module 2 workbook](https://github.com/iotempire/iotempire-teaching/blob/129d3f0ab4d9acd43e1659769cf4777e4e2aa41e/full-classes/hsbi-sensors-actuators-10d/modules/02-i2c-and-sensor-addressing.md#-learning-goals). Status describes the recorded evidence and identifies work carried out by Zhenning Yu.

| Workbook goal | Experiment or study | Evidence | Status |
| --- | --- | --- | --- |
| **LG1 · Interfaces.** Compare digital, analog and PWM pins with RS-232/UART, RS-485, Modbus RTU, CAN, I²C/I³C, SPI and OneWire by wiring, voltage, signaling, drive, speed, length, topology, uses and origin. Explain why PWM is not a bus. | Haocheng · Tasks 1–2, pin comparison, UART loopback and SPI survey | [Pin classification and PWM notes](pins-and-dividers.md), [UART log](uart-loopback/evidence/observed-loopback.txt) and [SPI profile](bus-spi.md). | Partial. The full bus comparison and pitch are not recorded in Haocheng's portfolio. |
| **LG2 · I²C principles.** Explain SDA/SCL, open-drain signaling, pull-ups, addressing, ACK/NACK, repeated start and clock stretching. | Haocheng · I²C study notes. Zhenning · Tasks 5 and 9 | [Pull-up notes](#task-2-bus-survey-and-pitch--in-progress), [address scan][yu-task-5] and [decoded NACK][yu-task-9]. | Partial. The notes and teammate capture cover pull-ups, addressing and acknowledgments. Repeated start and clock stretching lack specific evidence here. |
| **LG3 · Scanning.** Wire an I²C bus, scan it and identify the connected devices by address. | Zhenning · Tasks 5 and 7 | [Single-device scan][yu-task-5] and [two-device scan][yu-task-7] identify the LCD1602 and SE95. | Demonstrated by Zhenning. Haocheng's hands-on scan is unverified. |
| **LG4 · Registers.** Read a sensor through a library and directly from its raw registers. | Zhenning · Task 6 | [SE95 comparison][yu-task-6] shows agreement between direct conversion and the library. | Demonstrated by Zhenning. Haocheng's hands-on register read is unverified. |
| **LG5 · Shared bus.** Operate two devices on one bus and resolve an address conflict. | Zhenning · Task 7 | [LCD1602 and SE95 on shared SDA/SCL][yu-task-7] respond at different addresses. | Partial teammate evidence. Address-conflict resolution is not documented. |
| **LG6 · Instrumentation.** Build and evaluate a low-cost ESP32 scope or logic analyzer and agree on one or two class tools for bus debugging. | Zhenning · Task 9 | [ESP32 and PulseView test][yu-task-9] covers a square wave and I²C decoding. | Partial teammate evidence. Class-wide tool selection is unverified. |

## Task 1: Simple pins, PWM, UART and a divider

[Classification table, calculations and UART notes](pins-and-dividers.md) · [UART loopback firmware](uart-loopback/uart-loopback.ino)

The conceptual notes and proposed divider calculation are prepared. UART loopback firmware compiled and uploaded for the classic ESP32. One hardware string test passed with matching TX and RX output; the [screenshot](uart-loopback/evidence/loopback-01.png) and [text](uart-loopback/evidence/observed-loopback.txt) are saved. The student has obtained a multimeter and recorded a 3.316 V divider-input reading. Divider output and the 5 V-input scenario have not yet been measured. Task 1 is not yet complete.

## Task 2: Bus survey and pitch — in progress

The instructor directed the class to begin Task 2 before the divider output was measured. The student identified SPI as the assigned bus. A sourced [SPI profile](bus-spi.md) and [research questions with source checks](bus-spi-research.md) have been prepared. The physical kit example, device-specific settings, pod discussion and presentation remain to be verified or recorded. [Notes from other pods' pitches](other-pods-notes.md) are awaiting the presentations.

All pods should be ready to explain I2C open-drain signaling and pull-ups: devices pull a shared line low or release it, while a pull-up supplies its high state. The pull-up voltage and current must be compatible with the connected devices. This is a study note, not a claim that an I2C circuit or a pod discussion has been completed.

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
