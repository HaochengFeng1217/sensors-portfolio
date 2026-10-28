# Module 2: Buses and I2C

Student: Haocheng Feng. Started: 28 October 2026.

## Task 1: Simple pins, PWM, UART and a divider

[Classification table, calculations and UART notes](pins-and-dividers.md) · [UART loopback firmware](uart-loopback/uart-loopback.ino)

The conceptual notes and proposed divider calculation are prepared. UART loopback firmware compiled and uploaded for the classic ESP32. One hardware string test passed with matching TX and RX output; the [screenshot](uart-loopback/evidence/loopback-01.png) and [text](uart-loopback/evidence/observed-loopback.txt) are saved. The student has obtained a multimeter and recorded a 3.316 V divider-input reading. Divider output and the 5 V-input scenario have not yet been measured. Task 1 is not yet complete.

## Task 2: Bus survey and pitch — in progress

The instructor directed the class to begin Task 2 before the divider output was measured. The student identified SPI as the assigned bus. A sourced [SPI profile](bus-spi.md) and [research questions with source checks](bus-spi-research.md) have been prepared. The physical kit example, device-specific settings, pod discussion and presentation remain to be verified or recorded.

All pods should be ready to explain I2C open-drain signaling and pull-ups: devices pull a shared line low or release it, while a pull-up supplies its high state. The pull-up voltage and current must be compatible with the connected devices. This is a study note, not a claim that an I2C circuit or a pod discussion has been completed.

Later Module 2 tasks have not been started in this record.
