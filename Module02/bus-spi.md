## Bus profile: SPI

- **History and background:** Motorola developed SPI to connect controllers and peripherals; the introduction year has not been verified. [1]
- **Wires and connectors:** Four signals are shown below, plus common ground and suitable power. Connectors vary. [2]

| Signal | Purpose |
| --- | --- |
| SCLK / SCK | Clock from controller |
| MOSI / COPI | Data from controller to peripheral |
| MISO / CIPO | Data from peripheral to controller |
| CS / SS | Selects a peripheral, often active low |

- **Voltage, signaling, and drive style:** Synchronous serial, usually push-pull; separate data lines allow full duplex. SPI does not prescribe one voltage: the ESP32 uses 3.3 V logic, so check the peripheral and use level shifting if needed. [2][3]
- **Topology and addressing:** One controller normally shares clock and data lines with peripherals, with a separate CS for each; SPI has no I2C-style bus address. Inactive devices must release MISO. [2][3]
- **Speed and maximum length:** Often MHz over short board-level connections. There is no universal speed or cable-length limit; the devices and wiring determine it. [2]
- **Relation to other buses:** I2C/I3C use shared, addressed lines; I2C uses pull-ups. RS-232 and RS-485 define electrical interfaces; Modbus RTU is a protocol often carried over RS-485. CAN uses arbitration; OneWire uses a shared data line and device IDs.
- **Typical use and kit example:** Displays, SD cards and flash memory. A specific SPI device in this kit has not yet been identified or tested. [2]
- **Curiosities / remarkable features:**
  - Data can move in both directions during the same clock cycles.
  - More peripherals normally require more CS pins.
  - There is no universal acknowledgement; check a device-specific ID or status if available. [2]
- **What can go wrong / how to debug:** Check power, ground, signal wiring, CS, clock polarity and phase, and bit order against the device datasheet. A logic analyzer can show CS, clock and data. [3][4]
- **Sources and verification:** [1] [NXP: SPI background](https://www.nxp.com/docs/en/supporting-information/design_con_2003_tecforum_i2c_bus_overview.pdf); [2] [Microchip: SPI overview](https://developerhelp.microchip.com/xwiki/bin/view/applications/SPI/); [3] [Espressif: ESP32 SPI](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html); [4] [Analog Devices: clock modes](https://www.analog.com/en/resources/design-notes/interfacing-spi-realtime-clocks-rtcs-with-a-microcontroller.html). Verify settings and limits in the specific device datasheet.
