# Notes from other pods' pitches

## RS-485

- **Background:** The group described RS-485 as an EIA standard from 1983, intended for longer distances, multiple devices and better noise resistance than RS-232.
- **Signals:** A differential pair, commonly twisted, carries the signal. The voltage difference between the two wires determines the state. The group cited a minimum 1.5 V transmitter differential and receiver thresholds around ±0.2 V. Check the transceiver datasheet for exact limits and A/B labeling.
- **Topology:** Devices share a linear bus. Termination is typically 120 Ω at each physical end to reduce reflections. Simultaneous transmitters can cause contention.
- **Addressing:** RS-485 defines electrical signaling; a separate protocol such as Modbus RTU provides device addressing and message rules.
- **Speed and distance:** The group gave approximate examples of 100 kbit/s over 1,200 m or 10 Mbit/s over 12 m. These are illustrative trade-offs, not guaranteed limits; cable and transceivers matter.
- **Compared with SPI:** RS-485 is suited to longer, noise-prone links and multi-device wiring. SPI is usually used for short board-level connections with a separate chip-select line per peripheral. Unlike CAN, RS-485 itself does not provide arbitration or error handling.
- **Examples:** Industrial sensors, PLCs and energy meters. The group suggested two Arduino boards with MAX485 modules as an example; this is not a test recorded here.

These notes summarize the material supplied by the groups. Additional pitches can be added when available.

## RS-232

- **Background:** The group described RS-232 as introduced in 1960 for communication between computers and modems, later also used with peripherals such as printers and mice.
- **Connections:** Traditionally point-to-point serial wiring with connectors such as DB-25; separate transmit and receive lines and a common signal ground are commonly used. Connector and pinout depend on the equipment.
- **Signaling and voltage:** RS-232 uses positive and negative signal voltages. For data, a negative voltage represents mark (1), and a positive voltage represents space (0). These are RS-232 signal levels, not 3.3 V ESP32 GPIO levels. Check the relevant equipment specifications.
- **Topology:** A point-to-point link can carry data in both directions using separate transmit and receive wires. Each individual wire carries data in one direction.
- **Speed and distance:** The group cited 20 kbit/s and approximately 15 m as typical reference figures; actual achievable performance depends on equipment, cable and conditions.
- **Compared with RS-485 and SPI:** RS-232 commonly serves a short point-to-point link; RS-485 supports longer differential multi-device links. SPI is synchronous and typically uses chip select; RS-232 defines electrical signaling for serial links.
- **Examples:** CNC equipment, networking equipment and scientific instruments. ESP32-to-ESP32 UART at 3.3 V illustrates serial communication but is not itself an RS-232 electrical connection. A suitable RS-232 transceiver is needed between an ESP32 and an RS-232 port.
- **Debugging:** Check baud rate and serial format, TX/RX routing, common ground and voltage levels. Do not connect RS-232 voltage levels directly to ESP32 GPIO.
- **Group sources:** [RS-232](https://en.wikipedia.org/wiki/RS-232); [serial cable](https://en.wikipedia.org/wiki/Serial_cable).
