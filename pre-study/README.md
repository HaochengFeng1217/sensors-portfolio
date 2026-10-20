# Module 0: Pre-study

Course: HSBI Sensorik und Aktorik, WS 2026/27  
GitHub account: HaochengFeng1217  
Full name: Haocheng Feng  
Entry started: 2026-10-20  
Status: **Draft - structure prepared; exercises and personal answers pending.**

## Preparation log

- The course template and the uploaded Pre-Study Guide and Syllabus have been identified.
- The eight guiding-question sections and evidence folders below have been prepared.
- This entry was structured with AI assistance and checked against the course documents.
- No Wokwi experiment or physical measurement is documented as completed.
- Personal examples, datasheet findings, experimental observations, and the project idea must be added.

## Completion checklist

- [x] Personal public GitHub repository created with "Use this template".
- [x] Initial pre-study entry structure prepared.
- [ ] Full name added to the portfolio homepage.
- [ ] Guiding Questions 1-8 answered and understood.
- [ ] VL53L0X and MPR121 datasheet notes completed, with sources and conditions.
- [ ] Wokwi ESP32 potentiometer-to-LED simulation run.
- [ ] ADC resolution changed and actual observations recorded.
- [ ] Coarse threshold/step behaviour tested and described.
- [ ] Real circuit and serial-output screenshots, or a saved simulation link, added.
- [ ] 5-10 line project abstract added, identifying two sensors and one actuator.
- [ ] Changes committed to GitHub and links checked.
- [ ] Instructor access arranged through the course's confirmed process.
- [ ] Arduino IDE v2 or PlatformIO readiness checked on the Mac.

## 1. Sensor-to-system chain

Choose a device I actually own. Identify the physical quantity, transducer, conditioning,
ADC, MCU, and system. Check what is known about the device instead of inventing its internals.

- Device and reason for choosing it: TODO
- Chain diagram and explanation: TODO
- Source or uncertainty about internal components: TODO

## 2. Wokwi observations: ADC resolution

Status: **Not yet performed.**

Start an ESP32 Arduino/C++ project, connect a potentiometer to an analog input,
print readings to the serial monitor, and use the reading to change an LED output.
Change the ADC resolution and test deliberately coarse thresholds or steps.

[Simulation files and evidence plan](wokwi/README.md)

| Setting used | Theoretical code range (label as theory) | Observed minimum / maximum | Observed LED behaviour |
|---|---|---|---|
| First ADC resolution: TODO bits | TODO | Not measured | Not observed |
| Changed ADC resolution: TODO bits | TODO | Not measured | Not observed |
| Coarse step / threshold: TODO | TODO | Not measured | Not observed |

- Number of representable levels before and after: TODO
- Explanation of resolution versus accuracy: TODO
- What actually changed in the simulation: TODO
- Coarse-output "jumps" and their cause: TODO
- Simulation URL: not yet created
- Circuit screenshot: not yet captured
- Serial-output screenshot: not yet captured

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

- What has actually been completed: entry structure only; update after doing the work.
- What is still unclear: TODO
- Questions / confusing instructions to raise in class: TODO
- How AI suggestions were verified: structure compared with the uploaded guide and syllabus;
  technical answers and experiments are still pending verification.

## Sources and version note

- Uploaded Pre-Study Guide and Syllabus: generated 2026-09-25, source revision 31aa6ca.
- [Live pre-study guide](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/pre-study.md)
- [Live syllabus](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/syllabus.md)
- [Portfolio template](https://github.com/iotempire/iot-portfolio-template)

The PDF names this file `pre-study/README.md` (or `00-pre-study.md`).
The uploaded PDFs and live workbook differ on preparation time and checkpoint timing;
confirm the arrangement for this cohort in the LMS or with the instructor.
