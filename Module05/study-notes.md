# LED and addressable-strip study notes

Added 18 November 2026 during portfolio review. These explanations complement the recorded experiments; they are not extra measurements or a test of personal understanding.

## Current limiting and forward voltage

An LED has a nonlinear current/voltage relationship. For a chosen operating current, a series resistor takes the approximate remaining voltage: R = (Vs − Vf) / I. In an illustrative design with Vs = 3.3 V, red Vf = 1.9 V and I = 6 mA, R = 233 ohms; choosing the next higher E24 value, 240 ohms, gives about 5.83 mA under those assumptions. The forward voltage and GPIO output drop are not constants across all devices or currents.

The actual RGB module has nominal 150-ohm resistors, and its currents were inferred from measured resistor drops, without assuming a forward voltage. Those measurements do not establish a different lamp's resistance requirement. [RGB evidence](task2-rgb/README.md#verification-and-current-measurements)

## Duty cycle, frequency and gamma

Duty cycle is on-time divided by period. Frequency is periods per second; changing duty does not inherently change frequency. The 8 ms delay between duty updates in Task 1 controls fade speed, not the underlying hardware PWM frequency. Frequency was not measured or explicitly configured in the tested sketch.

Perceived brightness is nonlinear, so equal duty increments need not look equally spaced. Gamma mapping changes the relationship between requested and output values; its convention and exponent must be stated. The strip baseline explicitly uses NeoGammaNullMethod, so it does not demonstrate gamma correction. A comparison remains unperformed.

## Additive colour and addressable data

Red and green light can combine to appear yellow; red, green and blue can combine to appear white. Perceived balance depends on spectra, relative intensity and viewing conditions. Equal serial RGB numbers do not guarantee equal channel currents or a colour-balanced white.

The Task 2 module exposes three separately driven channels. Each pixel on the Task 3 strip instead includes a controller. The firmware serial command is interpreted by the ESP32; NeoPixelBus translates its pixel buffer into the strip's timed single-wire data stream. In the configured GRB format, each pixel uses three eight-bit colour channels, 24 bits. DIN receives data and DOUT passes subsequent data to the next pixel. GPIO16 carries data, not the strip's load power. [Driver and limitations](task3-strip/README.md#driver-and-brightness)

## Supply decision

The measured 0.09 A covers only the eight-pixel strip at luminance 80/255. The off indication 0.00 A is limited by the UT131C 10 A range. Neither number measures the total USB load. The conservative 0.48 A estimate for eight pixels at full white would leave only 0.02 A of a nominal 0.50 A USB 2.0 budget for everything else; therefore that estimate cannot justify full-brightness operation of the ESP32 plus strip from such a source.

Keep the configured brightness limit, check the actual USB source and board power path, and measure total consumption before claiming a verified system budget. A larger strip needs a separately sized power path with common ground. The 30/60/144-pixel rows are calculations, because only eight pixels were available. [Power table](task3-strip/power-budget.md)

Source for the course design examples, data-path description and conservative current model: [Module 5 workbook](https://github.com/iotempire/iotempire-teaching/blob/43ee9338bdec8c83d568d07a27174865cb453552/full-classes/hsbi-sensors-actuators-10d/modules/05-leds-and-light-output.md). [Module 5 index](README.md)
