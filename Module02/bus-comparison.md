# Interface and bus comparison

Consolidated on 18 November 2026 from the [existing pin notes](pins-and-dividers.md), [SPI profile](bus-spi.md), and [notes supplied from other pods](other-pods-notes.md). This is a retrospective documentation summary, not evidence that Haocheng gave a pitch or tested every interface. Detailed voltage/speed limits must come from the actual devices and cabling; numerical maxima are not universal installation guarantees.

| Interface | Connection and signaling | Device selection / topology | Use and main limitation |
| --- | --- | --- | --- |
| Digital I/O | One logic signal with a common reference | Application-defined input/output | Button or LED; verify logic levels and current limits. |
| Analog | Continuous voltage relative to ground | One ADC input per measurement path | Resistive divider; limited by ADC range, noise, source impedance and calibration. |
| PWM | Logic pulses described by duty cycle, frequency or width | No inherent address or bus arbitration | LED brightness or servo command; not a communications bus by itself. |
| Logic-level UART | Separate TX/RX, common ground; asynchronous framing | Normally point-to-point | Debugging and modules; baud/framing mismatch causes errors. An ESP32 GPIO UART is not electrically RS-232. |
| RS-232 | Transceiver and bipolar signal levels | Typically point-to-point | Legacy instruments; never connect its voltages directly to ESP32 GPIO. |
| RS-485 | Differential pair with suitable reference, termination and bus control | Commonly a multidrop trunk; protocol provides addresses | Longer industrial links; electrical signaling alone supplies no application message rules. |
| Modbus RTU | Serial framing and CRC, often over RS-485 | Addressed request/reply | PLCs/meters; depends on the transport's wiring, timing and transceivers. |
| CAN | Differential bus through a transceiver | Multi-controller messages with identifier arbitration | Distributed control; bit timing, termination and acknowledgment matter. |
| I²C | SDA/SCL with open-drain signaling and pull-ups | Shared addressed bus | Local sensors; rise time, capacitance and address conflicts limit operation. |
| I³C | SDA/SCL; push-pull and open-drain phases | Supports dynamic addressing for compatible devices | Local sensors; host and device capabilities must be checked rather than assuming all I²C boards can use I³C modes. |
| SPI | Clock, data in/out and chip-select signals; compatible logic levels | Shared clock/data with selection usually per peripheral | Board-level peripherals; mode and CS timing are device-specific, with no single universal SPI packet format. |
| 1-Wire | Shared DQ and ground; pull-up, with supply/power mode as required | Device identification by ROM code | DS18B20; see the separately recorded [single-probe experiment](../Module03/ds18b20/README.md). This row was added from later Module 3 study, not from an unrecorded class pitch. |

For the supplied groups' history, example data rates, distance tradeoffs and sources, use [the detailed notes](other-pods-notes.md). SPI's signal and device-specific checks are in the [sourced SPI profile](bus-spi.md). OneWire properties here are supported by the [DS18B20 manufacturer datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ds18b20.pdf), especially its introduction and bus-operation sections.

## I²C transaction concepts added during review

A repeated START begins another address phase without an intervening STOP, retaining the transaction's bus-busy state. A typical register read first writes the register pointer, then uses repeated START to address the same device for reading; the final received byte is followed by controller NACK and STOP. The exact pointer format is device-specific.

Clock stretching holds SCL low until the device releases it. Support is optional; software timeouts and controller support must be checked. An ACK indicates byte reception, not that an application-level action succeeded. These are conceptual notes, not a newly captured trace. Source: [NXP UM10204, Rev. 7.0](https://www.nxp.com/docs/en/user-guide/UM10204.pdf), Sections 3.1.4, 3.1.6, 3.1.9 and 3.1.10.

## What remains unverified

Haocheng's specific SPI kit-device demonstration, exact mode/settings, pitch contribution, hands-on I²C role and class-wide analyzer choice remain unrecorded. The workbook labels the address-conflict Task 8 and wire-level Task 10 as optional; neither is a missing mandatory bench task here. Goal coverage and performed tasks are separate questions.

[Module 2](README.md)
