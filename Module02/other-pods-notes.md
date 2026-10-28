# Notes from other pods' pitches

## RS-485

- **Background:** The group described RS-485 as an EIA standard from 1983, intended for longer distances, multiple devices and better noise resistance than RS-232.
- **Signals:** A differential pair, commonly twisted, carries the signal. The voltage difference between the two wires determines the state. The group cited a minimum 1.5 V transmitter differential and receiver thresholds around ±0.2 V. Check the transceiver datasheet for exact limits and A/B labeling.
- **Topology:** Devices share a linear bus. Termination is typically 120 Ω at each physical end to reduce reflections. Simultaneous transmitters can cause contention.
- **Addressing:** RS-485 defines electrical signaling; a separate protocol such as Modbus RTU provides device addressing and message rules.
- **Speed and distance:** The group gave approximate examples of 100 kbit/s over 1,200 m or 10 Mbit/s over 12 m. These are illustrative trade-offs, not guaranteed limits; cable and transceivers matter.
- **Compared with SPI:** RS-485 is suited to longer, noise-prone links and multi-device wiring. SPI is usually used for short board-level connections with a separate chip-select line per peripheral. Unlike CAN, RS-485 itself does not provide arbitration or error handling.
- **Examples:** Industrial sensors, PLCs and energy meters. The group suggested two Arduino boards with MAX485 modules as an example; this is not a test recorded here.

These notes summarize the material supplied by the RS-485 group. Additional groups' pitches can be added when available.
