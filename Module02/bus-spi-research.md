# SPI Research Questions and Verification

These are assistant-guided research questions and source checks prepared for Module 2 Task 2. They are not a record of a physical SPI experiment, a pod discussion or a student presentation.

1. **How does SPI choose one device when several share the bus?** Conventional SPI commonly shares SCLK, MOSI and MISO and uses a separate CS for each peripheral. The selected device participates and a deselected device releases its output. Verified against [Espressif's SPI driver description](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html).
2. **Can SPI transmit and receive simultaneously, and does it acknowledge success?** Standard four-wire SPI can exchange bits in both directions on the same clocks; SPI itself has no universal ACK. A device may have its own status or error-check mechanism. Checked against [Microchip's introduction](https://developerhelp.microchip.com/xwiki/bin/view/applications/SPI/).
3. **Why might correctly wired devices still read incorrect values?** Clock polarity and phase must match the device; other possible causes include the wrong select signal or bit order. Checked against [Analog Devices' SPI mode explanation](https://www.analog.com/en/resources/design-notes/interfacing-spi-realtime-clocks-rtcs-with-a-microcontroller.html). Exact settings and failures remain device-specific and have not been tested on this kit.

The exact introduction year, the specific SPI module in the kit, its voltage and timing, and any measurement remain open verification items.
