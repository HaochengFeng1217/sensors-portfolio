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

## Modbus RTU

- **Background:** The group reported that Modicon created Modbus in 1979 for industrial PLC communication. This date refers to Modbus generally, not a confirmed first release of RTU.
- **Protocol and electrical interface:** Modbus RTU is an asynchronous serial protocol, not an electrical standard. It commonly runs over RS-485 and can also use RS-232. For an RS-485 connection, an ESP32 needs a suitable transceiver; RTU itself specifies no fixed voltage.
- **Topology and addressing:** Typically one client/master communicates with multiple servers/slaves. Addresses 1–247 identify devices; address 0 is a broadcast and receives no reply. The number of devices on a physical link can be lower than the address range.
- **Frames and timing:** A frame contains an address, function, data and CRC-16. The group noted a gap of at least 3.5 character times between frames, with special timing rules above 19,200 bit/s.
- **Speed and distance:** The group cited 9,600 and 19,200 bit/s, and up to 1,000 m at 9,600 bit/s under the serial-line specification's stated conditions. Wiring, speed and loading affect achievable distance.
- **Compared with SPI and RS-485:** RS-485 defines electrical signaling; Modbus RTU adds addressing, functions and framing. SPI is typically used for short local connections and normally selects a peripheral with a CS line.
- **Examples:** Industrial PLCs, meters, motor drives and sensors. Two ESP32s could implement RTU in software with RS-485 transceivers; the group did not confirm a specific kit demonstration.
- **Debugging:** For no reply, check the device address, baud rate, parity, data wiring, common reference, termination and biasing. Inspect frames and CRC and measure line signals where possible.
- **Sources named by the group:** Modbus Organization introduction and Modbus Serial Line Specification V1.02; Texas Instruments material on RS-485 termination. Consult the original documents for details.

## CAN (Controller Area Network)

- **Background:** The group reported that Bosch developed CAN for communication between automotive controllers, with substantial protocol development in 1984 and a public presentation in 1986.
- **Wiring and signaling:** High-speed CAN commonly uses a twisted CANH/CANL pair and an appropriate common reference. A transceiver converts controller logic to differential bus signals. Dominant 0 overrides recessive 1; connector pinouts depend on the application.
- **Topology and arbitration:** CAN is a multi-master broadcast bus, usually a linear trunk with short stubs. Message identifiers indicate content and priority rather than inherently naming a destination. Within the same frame format, a lower identifier wins arbitration. A node that loses stops transmitting without damaging the winning frame.
- **Speed and distance:** Classical CAN supports up to 1 Mbit/s. The group cited 40 m at 1 Mbit/s as a theoretical example, not a guaranteed limit; propagation, transceivers, cable, stubs and bit timing affect the network.
- **Classical CAN and CAN FD:** Classical CAN carries up to 8 data bytes; CAN FD supports up to 64 and can use a faster data phase with compatible hardware. The group noted that the classic ESP32 TWAI controller supports Classical CAN, not CAN FD.
- **Compared with SPI and RS-485:** CAN includes arbitration, framing and error handling. SPI normally uses a shared clock and separate chip-select lines; RS-485 specifies differential electrical signaling and needs a protocol for message rules.
- **Examples:** Automotive controllers, industrial drives, robotics and distributed sensors. The group's proposed classic ESP32 plus SN65HVD230 transceiver example was marked untested.
- **Debugging:** Check power and mode, CANH/CANL, the common reference, matching bit timing and termination at both ends. A single node or listen-only peer cannot supply the external acknowledgement needed for a normal transmission. Inspect error flags or use a CAN analyzer.
- **Remarkable feature:** A CAN acknowledgement means a node received the frame correctly; it does not prove that an application processed the message.
- **Sources named by the group:** CAN in Automation history, CAN CC and physical-layer materials; TI SN65HVD230 datasheet; Bosch CAN FD information.
