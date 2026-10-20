# Module 0: Pre-study

Course: HSBI Sensorik und Aktorik, WS 2026/27  
GitHub account: HaochengFeng1217  
Full name: Haocheng Feng  
Entry started: 2026-10-20  
Status: **In progress - Questions 1-8 documented; personal review and preparation checks pending.**

## Preparation log

- Personal portfolio created from the course template.
- ESP32 potentiometer-to-LED simulation run on 2026-10-21.
- Compared 12-bit and 10-bit readings and tested a four-level brightness mapping.
- Saved the project, source files, serial output, and three screenshots.
- Documented the sensor-to-system chain for screen auto-rotation on my iPhone 15 Pro Max.
- Added manufacturer datasheet notes for VL53L0X and MPR121, including address conventions and specification conditions.
- Added two hypothetical scale examples to explain accuracy and precision.
- Added an I²C shared-bus explanation, signal diagram, and likely communication problems.
- Added an actuator choice for a small lever-operated latch, with assumptions and a torque-sizing example.
- Added the full-white LED current/power calculation and a supply-sizing example.
- Selected a touch-confirmed proximity storage box and added a project abstract.
- Personal review, supplementary study notes, and the remaining preparation checks are still pending.

## Completion checklist

- [x] Personal public GitHub repository created with "Use this template".
- [x] Initial pre-study entry structure prepared.
- [x] Full name added to the portfolio homepage.
- [ ] Guiding Questions 1-8 answered and understood.
- [x] VL53L0X and MPR121 datasheet notes completed, with sources and conditions.
- [x] Wokwi ESP32 potentiometer-to-LED simulation run.
- [x] ADC resolution changed and actual observations recorded.
- [x] Coarse threshold/step behaviour tested and described.
- [x] Real circuit and serial-output screenshots, or a saved simulation link, added.
- [x] 5-10 line project abstract added, identifying two sensors and one actuator.
- [ ] Remaining pre-study answers completed and final links checked.
- [ ] Instructor access arranged through the course's confirmed process.
- [ ] Arduino IDE v2 or PlatformIO readiness checked on the Mac.

## 1. Sensor-to-system chain

**Device:** My iPhone 15 Pro Max. Screen auto-rotation is a visible example of a
system responding to a change in the device's physical orientation.

**Simplified chain:** Acceleration along the phone's axes → sensing element →
signal conditioning → ADC → sensor processing and host processor → screen orientation.

Apple lists a high-g accelerometer, a high dynamic range gyroscope, and the A17 Pro
chip for this model. Its Core Motion documentation describes a gravity vector in
the device's reference frame. When the phone is held still in a different orientation,
the gravity components along its axes change; this provides information for estimating
tilt. [iPhone specifications](https://support.apple.com/en-us/111828),
[Core Motion: gravity](https://developer.apple.com/documentation/coremotion/cmdevicemotion/gravity).

The sensing, conditioning, and conversion stages below use a representative
capacitive MEMS accelerometer model.

| Stage | Role in the chain |
|---|---|
| Physical quantity | Acceleration along three axes. At rest, the gravity components provide a reference for tilt. |
| Transducer | In a capacitive MEMS design, acceleration moves a tiny suspended mass and changes a differential capacitance. |
| Signal conditioning | Sensing electronics convert the small capacitance change into an electrical signal suitable for conversion. |
| ADC | Converts the analog sensor signal into digital acceleration readings. The representative sensor integrates this conversion before its digital interface. |
| MCU / processor role | Sensor processing and the phone's processor/operating system use motion data to estimate orientation. The phone has an A17 Pro application processor; the exact sensor-hub hardware and division of processing are unconfirmed. |
| System | In an app that supports rotation, with orientation lock off, the interface can switch between portrait and landscape. |

The [ADXL345 datasheet, Rev. G](https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf)
illustrates the integrated sensing electronics, ADC, digital filter, and digital
interface in Figure 1 (p. 1), and explains capacitive sensing on p. 12. It is an
example for the model above; the actual sensor part number, ADC resolution, interface,
and rotation algorithm in my iPhone remain unconfirmed.
[Apple's rotation guide](https://support.apple.com/guide/iphone/rotate-your-iphone-screen-iph3badf94ec/27/ios/27)
describes the user-visible rotation behavior and orientation lock.

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

**Chosen sensor: VL53L0X.** The [notes for both required sensors](datasheets.md)
cover their supply, interface, range, resolution, and limitations.

The VL53L0X uses **I²C, up to 400 kHz**. Its default **7-bit address is 0x29**.
The datasheet writes **0x52** for the address byte used for writing and **0x53** for
reading; these include the R/W bit (Table 2, p. 3; Section 4, Figure 14, p. 15).

The datasheet characterizes ranging accuracy using **standard deviation**, including
measurement-to-measurement and part-to-part dispersion. One Table 13 example is
**4% at 120 cm with a 33 ms timing budget**, for a white target of **88% reflectance**,
indoors with **no infrared background**. Conditions include **2.8 V**, **23°C**, offset
correction at **10 cm**, a target covering the full **25° field of view**, and a
minimum **94% detection rate**. This standard-deviation figure is not a guaranteed
maximum absolute error for every reading.

Source: STMicroelectronics, [VL53L0X datasheet](https://www.st.com/resource/en/datasheet/vl53l0x.pdf),
**DS11555, Rev. 6, June 2024**, Section 6.3.1 and Table 13, **p. 23**.
These are manufacturer specifications; no hardware accuracy measurement has been performed.

## 4. Accuracy versus precision

Accuracy concerns how close a measured value is to the true value; in practice,
a suitable reference value is used for comparison. Precision concerns how closely
repeated measurements agree under the same specified conditions.

The following everyday examples are hypothetical.

- **Precise but inaccurate:** A bathroom scale is checked with a reference load
  of **20.0 kg**. It repeatedly displays **22.0 kg, 22.0 kg, and 22.0 kg**.
  The displayed readings agree closely, but they are all **2.0 kg too high**.
  A consistent offset can therefore give repeatable readings that are wrong.
- **Accurate but imprecise, in the everyday sense of correct on average:** Suppose
  a kitchen scale's readings are scattered around a **100 g** reference mass.
  Example readings are **95 g, 100 g, and 105 g**. Their mean is **100 g**, but
  the individual readings vary widely, so repeatability is poor.

In simple terms, accuracy asks "How close is the result to the reference?" and
precision asks "How close are the repeated results to each other?" Strictly, the
second example illustrates good trueness with low precision, assuming the long-run
mean remains near the reference. One correct sample mean does not establish the
instrument's accuracy or make every individual reading accurate.

Terminology checked against JCGM's International Vocabulary of Metrology:
[accuracy, 2.13](https://jcgm.bipm.org/vim/en/2.13.html),
[trueness, 2.14](https://jcgm.bipm.org/vim/en/2.14.html), and
[precision, 2.15](https://jcgm.bipm.org/vim/en/2.15.html).

## 5. I²C anticipation

**Initial explanation:** In a single-controller setup, several sensors connect in
parallel to the same **SDA** data line and **SCL** clock line. They also need a common
ground and compatible logic levels. Open-drain outputs pull a line low; pull-ups
restore the high level when it is released.

The controller starts a transfer and sends a target address with a read/write bit.
A ready sensor with the matching address acknowledges and participates. The address
therefore selects the sensor without a separate chip-select wire for every device.

For the two sensors in the [datasheet notes](datasheets.md), the default VL53L0X
address is **0x29** and the MPR121 address is **0x5A** when ADDR is tied to VSS.
Both are **7-bit addresses**, so this pair has no address conflict. The exact
breakout boards' logic levels and pull-ups still need checking before connection.

```mermaid
flowchart LR
    MCU["MCU / controller"] --- SDA["Shared SDA"]
    MCU --- SCL["Shared SCL"]
    SDA --- VL["VL53L0X: 0x29"]
    SCL --- VL
    SDA --- MP["MPR121: 0x5A"]
    SCL --- MP
```

This is a signal-topology diagram; power, ground, and pull-up wiring are omitted.

| Possible problem | Why it matters |
|---|---|
| Two devices with the same address | Both may respond, so the controller cannot select them independently. A supported address change or separate bus/multiplexer may be needed. |
| Wrong address convention | Passing an 8-bit address byte to an API expecting a 7-bit address selects the wrong target. |
| Missing or unsuitable pull-ups | Lines may not rise correctly, or devices may need to sink too much current. Pull-ups already fitted to several boards combine in parallel. |
| Incompatible logic levels or missing common ground | A valid high/low level may not be recognized; excessive pin voltage can damage a device. |
| Long wires, high bus capacitance, or excessive clock speed | Signal rise times and timing requirements may no longer be met, causing communication errors. |

**Question to revisit in Module 2:** How should the effective pull-up resistance be
chosen when several breakout boards already contain pull-ups, and how can the signal
rise time be checked?

Bus principles checked against NXP's [I²C-bus specification and user manual,
UM10204, Rev. 7.0, 1 October 2021](https://www.nxp.com/docs/en/user-guide/UM10204.pdf),
Sections **3.1.1**, **3.1.6**, **3.1.10**, and **7.1**.

## 6. Actuator choice: small door latch

**Choice and assumptions:** A small positional RC servo driving a short lever.
Assume the latch has two end positions, modest friction, and a mechanical catch
that holds the closed state without continuous motor torque. Movement is needed
only once every few minutes. The actual latch force and travel still need checking
before selecting a particular servo model.

**Torque:** For a tangential force, the required lever torque is `torque = force × radius`.
As an illustrative sizing assumption, **2 N** acting at **10 mm** gives
`2 N × 0.010 m = 0.020 N·m`. The selected servo must have operating torque margin
for starting friction and the linkage geometry. This example does not establish
the torque requirement of an actual latch.

**Control:** Command the two positions using the servo's control-pulse width.
Set the endpoints to match the linkage travel and avoid forcing the mechanism
against a stop. Pulse-width-to-angle mapping and allowed pulse limits depend on
the servo; they should be checked rather than assumed from an angle command alone.
[Pololu: servo control interface](https://www.pololu.com/blog/17/servo-control-interface-in-detail).

**Power:** Use a supply within the chosen servo's voltage rating and with sufficient
current for startup and load peaks. The MCU provides the control signal; the motor
supply carries the motor current, with a common ground. Infrequent movement can
reduce average demand, but a powered servo may still draw current while holding a
load. Any power-off strategy depends on the latch retaining its state mechanically.
[Arduino: powering servo motors](https://docs.arduino.cc/learn/electronics/servo-motors/#powering-servo-motors).

| Alternative | Force/torque and control | Power and fit for this task |
|---|---|---|
| Lock-style solenoid | Direct linear pull, with force depending on stroke; switched using a transistor and flyback diode. | A suitable alternative for a spring-return latch. A design that holds closed mechanically can use power only while retracting; supply and energization limits are model-specific. |
| Bare DC motor | Produces rotation; gearing and a linkage set the available latch force. A motor driver and endpoint feedback or switches are needed for controlled positioning. | Rejected on its own: applying power does not select a repeatable open/closed position. Adding the necessary control and mechanics makes it a more involved solution. |

The [Adafruit lock-style solenoid example](https://www.adafruit.com/product/1512)
illustrates an unpowered locked state, powered retraction, and the transistor/diode
driver requirement. The preferred actuator would be reconsidered if the actual
latch needs a direct linear stroke or continuous holding force.

## 7. LED power calculation

Using the guide's full-white assumption of **30 WS2812 LEDs**, each drawing up to
approximately **60 mA**, the design estimate is:

```text
Maximum LED current = 30 × 60 mA = 1800 mA = 1.8 A
LED input power at 5 V = 5 V × 1.8 A = 9 W
```

**Supply capability and margin:** The LEDs alone require approximately **1.8 A at
5 V** under this assumption. A regulated **5 V, 3 A** supply, rated for **15 W**
output, is an example that provides headroom. Add the controller and any other
loads to the budget if they share that supply. The current rating is the supply's
capacity; the LEDs draw the current required by their operating state.

**Why use a separate power path:** A board's **5 V** label identifies a voltage,
not a guarantee that its power path can carry **1.8 A** for the LEDs. USB input,
protection, regulators, connectors, and PCB traces have board-specific limits.
Without confirming those limits, routing this load through the board could overload
its power path. Feed the strip's power connections directly from the appropriately
rated external supply, connect its ground to MCU ground, and use the MCU for the
data signal.

The **60 mA** figure is the course's sizing assumption; actual current depends on
the LED version, color, and brightness. Check the particular strip's specifications
and measure its consumption when building the circuit.
[Adafruit's NeoPixel power guide](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels)
explains the full-white estimate, power-supply headroom, and power distribution.

## 8. Project abstract

**Tentative project: Touch-confirmed proximity storage box**

Status: **Concept selected; implementation and validation planned.**

This project proposes a small desktop storage box for students to keep keys or other small items together.<br>
The goal is convenient access with a deliberate touch confirmation instead of responding to a passing hand alone.<br>
An ESP32 will read a VL53L0X distance sensor to detect a hand approaching the front of the box.<br>
An MPR121 touch pad will provide the user's confirmation while the hand is nearby.<br>
When both conditions are met, a positional servo will release a lightweight latch so the user can open the lid manually.<br>
After closing the lid, the user will request relatching with a second deliberate touch.<br>
The prototype will test distance thresholds, touch sensitivity, servo travel, and power requirements.<br>
The main uncertainty is achieving repeatable latch movement while avoiding unintended triggers.

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

- Completed: portfolio structure, written answers for Questions 1-8, the Wokwi ADC/LED experiment with saved evidence, and both sensor datasheet notes.
- Remaining: personal review and understanding, supplementary study notes, instructor access, and Mac development-environment readiness.
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
