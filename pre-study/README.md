# Module 0: Pre-study

Course: HSBI Sensorik und Aktorik, WS 2026/27  
GitHub account: HaochengFeng1217  
Full name: Haocheng Feng  
Entry started: 2026-10-20  
Status: **In progress - Wokwi experiment completed; other pre-study answers pending.**

## Preparation log

- Personal portfolio created from the course template.
- ESP32 potentiometer-to-LED simulation run on 2026-10-21.
- Compared 12-bit and 10-bit readings and tested a four-level brightness mapping.
- Saved the project, source files, serial output, and three screenshots.
- Datasheet reading, the remaining guiding questions, and the project abstract are still pending.

## Completion checklist

- [x] Personal public GitHub repository created with "Use this template".
- [x] Initial pre-study entry structure prepared.
- [x] Full name added to the portfolio homepage.
- [ ] Guiding Questions 1-8 answered and understood.
- [ ] VL53L0X and MPR121 datasheet notes completed, with sources and conditions.
- [x] Wokwi ESP32 potentiometer-to-LED simulation run.
- [x] ADC resolution changed and actual observations recorded.
- [x] Coarse threshold/step behaviour tested and described.
- [x] Real circuit and serial-output screenshots, or a saved simulation link, added.
- [ ] 5-10 line project abstract added, identifying two sensors and one actuator.
- [ ] Remaining pre-study answers completed and final links checked.
- [ ] Instructor access arranged through the course's confirmed process.
- [ ] Arduino IDE v2 or PlatformIO readiness checked on the Mac.

## 1. Sensor-to-system chain

Choose a device I actually own. Identify the physical quantity, transducer, conditioning,
ADC, MCU, and system. Check what is known about the device instead of inventing its internals.

- Device and reason for choosing it: TODO
- Chain diagram and explanation: TODO
- Source or uncertainty about internal components: TODO

## 2. Wokwi observations: ADC resolution

Run date: 2026-10-21. [Open the saved Wokwi project](https://wokwi.com/projects/478439382770685953).

The ESP32 reads a potentiometer on GPIO34 and drives a red LED through a
330 ohm resistor on GPIO2. The serial monitor records the raw ADC reading and
the PWM brightness value.

| ADC setting | Configured brightness levels | Observed ADC endpoints | Example observed PWM values |
|---|---|---|---|
| 12 bits | 256 | 0-4095 | 0, 64, 128, 192, 255 |
| 10 bits | 256 | 0-1023 | 0, 64, 128, 192, 255 |
| 10 bits, coarse output | 4 | 0-1023 | 0, 85, 170, 255 |

A 12-bit ADC has 4096 representable codes; a 10-bit ADC has 1024. Reducing the
resolution therefore makes the nominal ADC step four times coarser for the same
input span. The endpoint ranges above were observed; the code counts are theoretical,
and do not imply that every possible code was sampled.

For a control change from 512 to 513, the raw reading changed from 2050 to 2054
at 12 bits and from 512 to 513 at 10 bits. The LED brightness value stayed at 128
in both cases because the output mapping uses 256 PWM levels. Resolution changed;
this experiment does not demonstrate a change in measurement accuracy.

With four brightness levels, the PWM output jumped from 0 to 85 at raw 256,
from 85 to 170 at raw 512, and from 170 to 255 at raw 768. Many input values map
to the same output, so the LED changes abruptly at these thresholds.

- [Wiring, complete sample tables, and reproduction steps](wokwi/README.md)
- [Program](wokwi/sketch.ino) and [circuit configuration](wokwi/diagram.json)
- [Captured serial readings](wokwi/serial-output.md)
- Screenshots: [12-bit](images/wokwi-adc12.png), [10-bit](images/wokwi-adc10.png),
  [four-level output](images/wokwi-coarse4.png)

## 3. Datasheet question

Use [the notes for both required sensors](datasheets.md).
For one sensor, identify its interface, I²C address if relevant, and stated accuracy with conditions.

- Chosen sensor: TODO
- Interface / address and address convention: TODO
- Accuracy and conditions, or explanation if no single accuracy specification applies: TODO
- Manufacturer document, revision, and page/section: TODO

## 4. Accuracy versus precision

Give two everyday examples and explain the difference in my own words.

- Precise but inaccurate: TODO
- Accurate but imprecise: TODO
- Explanation: TODO

## 5. I²C anticipation

Explain how multiple sensors share clock and data wires, what could go wrong,
and why an address is needed.

- Initial explanation: TODO
- Question to revisit in Module 2: TODO

## 6. Actuator choice: small door latch

Choose an actuator for moving a small door latch once every few minutes.
Compare torque, control, and power; identify an unsuitable alternative.

- Choice and assumptions about the latch: TODO
- Torque / control / power justification: TODO
- Rejected alternative and reason: TODO

## 7. LED power calculation

Use the guide's assumption of 30 WS2812 LEDs, each up to approximately 60 mA at full white.
This is a calculation, not a current measurement.

- Calculation with units: TODO
- Required supply capability and practical margin: TODO
- Why the microcontroller's 5 V pin is unsuitable for this load: TODO

## 8. Project abstract

Status: **Idea not yet selected.**

Write 5-10 lines about a concrete user, scenario, problem, sensor inputs,
and actuator response. This is a tentative direction.

TODO: personal project abstract.

- Sensor 1 and purpose: TODO
- Sensor 2 and purpose: TODO
- Actuator and response: TODO
- Main uncertainty / question to investigate: TODO

## Additional study notes

### Measurement and uncertainty

- True value, error, and uncertainty: TODO
- Resolution versus accuracy: TODO
- Systematic versus random error; calibration versus averaging: TODO
- Sampling, Nyquist condition, and quantization: TODO

### Actuators

- PWM duty cycle, LED dimming, and servo control: TODO
- Plain LED current limiting: TODO
- WS2812 versus plain RGB LEDs and power requirements: TODO
- Servo, DC motor, and stepper comparison: TODO
- Driver electronics for motors and relays: TODO

## Reflection and open questions

- Completed: portfolio structure and the Wokwi ADC/LED experiment with saved evidence.
- Remaining: datasheet notes, the other guiding questions, and a personal project abstract.
- Open question: how real ESP32 ADC noise, offset, and non-linearity differ from this simulation.
- Verification: checked the circuit against the component pin references, compared the serial
  ranges with the ADC API, and tested the output threshold boundaries in the running simulation.

## Sources and version note

- Uploaded Pre-Study Guide and Syllabus: generated 2026-09-25, source revision 31aa6ca.
- [Live pre-study guide](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/pre-study.md)
- [Live syllabus](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/syllabus.md)
- [Portfolio template](https://github.com/iotempire/iot-portfolio-template)

The PDF names this file `pre-study/README.md` (or `00-pre-study.md`).
The uploaded PDFs and live workbook differ on preparation time and checkpoint timing;
confirm the arrangement for this cohort in the LMS or with the instructor.
