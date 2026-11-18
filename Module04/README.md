# Module 4: Liquid Measurement and Sensor Selection

[Portfolio](../README.md) · [Evidence](#experiment-records) · [Reflection 4](../Reflections/ref04.md) · [Review](../PORTFOLIO-REVIEW.md)

Portfolio owner Haocheng Feng. Evidence reviewed on 18 November 2026.

Zhenning Yu performed and documented all experiments in this module. Haocheng was absent from the session; this page and its reflection record a retrospective study of Zhenning's evidence. [Source report][yu-module] · [Contribution statement][yu-contribution]

## At a glance

| Item | Recorded scope |
| --- | --- |
| Sensing principles | Ultrasonic distance/volume, conductive water detection and IMU motion classification. |
| Volume validation | 213.83 mL predicted against about 219 mL reference: 2.36% deviation at one point. |
| Contribution | Teammate experiments; retrospective study by Haocheng. |
| Main limit | Lab results do not validate the proposed marine or brewery installations. |

## Learning goals

Goal numbers follow the course workbook. The evidence column points to Zhenning Yu's report. [Module 4 workbook](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/04-liquid-measurement-and-sensor-selection.md)

| Goal | Recorded evidence | Coverage and remaining checks |
| --- | --- | --- |
| LG1 — Explain binary, thresholded, continuous and hybrid sensing. | [Ultrasonic measurement][yu-ultrasonic], [conductive water detection][yu-binary] and [four-tank decision sheet][yu-decisions]. | Continuous distance and binary wet/dry tests are documented, with hybrid arrangements proposed for the tanks. |
| LG2 — Match sensing principles to liquids, decisions, installation and failure modes. | [Decision sheet][yu-decisions] and [recommendation report][yu-recommendations]. | Diesel, fresh water, waste water and bilge selections consider motion, contamination and maintenance. Proposed installation choices require application-specific validation. |
| LG3 — Calibrate continuous and binary mock-tank measurements and convert readings into level and volume. | [Seven-point volume calibration and validation][yu-calibration] and [HD-38 threshold test][yu-binary]. | One volume validation and the wet/dry switching test are recorded. A full numerical uncertainty budget remains a gap. |
| LG4 — Detect motion and explain its effect on tank readings. | [Foam and tilt observations][yu-foam] and [BMI270 classification][yu-imu]. | Three motion conditions are documented. Simultaneous IMU and ultrasonic measurements remain a proposed extension. |
| LG5 — Recommend sensors, explain the theory and transfer the reasoning to industry. | [Recommendation report][yu-recommendations], [theory report][yu-theory] and [brewery scenario][yu-brewery]. | The report includes tank recommendations and a theoretical brewery design using radar and an independent high-level switch. |

## Experiment records

| Experiment or analysis | Result reported by Zhenning Yu | Report and source program |
| --- | --- | --- |
| Ultrasonic level and volume calibration | Seven reference points span 0–309 mL and 12.1–4.9 cm. A separate 6.9 cm reading gives 213.83 mL by interpolation against approximately 219 mL reference volume, a 2.36% deviation. | [Calibration and validation][yu-calibration] · [HC-SR04 program][yu-ultrasonic-code] |
| Foam and container tilt | The report describes approximately 4.33 cm at rest, 5.61 cm during tilt and a temporary raw peak of approximately 6.47 cm. Readings returned near 4.33 cm after settling. | [Observations and screenshots][yu-foam] |
| Binary water detection | The HD-38 digital output changed from dry=1 to wet=0 and returned to 1 after removal and drying. A 300 ms debounce and approximately 0.3 cm trigger immersion are documented. | [Setup and output][yu-binary] · [HD-38 program][yu-binary-code] |
| Motion classification | The reported stationary mean deviation is approximately 0.002 g, gentle motion 0.027–0.066 g and rough motion 0.598–1.389 g. One window near 0.024 g was classified as in harbor. | [BMI270 test and classification][yu-imu] · [Measurement program][yu-imu-code] · [Classification program][yu-classification-code] |
| Tank selection and industrial transfer | The report compares continuous, binary and hybrid solutions for four yacht tanks, then proposes radar and independent overflow protection for a fictional brewery. | [Decision sheet][yu-decisions] · [Test cards][yu-tests] · [Brewery scenario][yu-brewery] |

## Study log

The volume-validation arithmetic was checked against the report's calibration table. Interpolating between 205 mL at 7.0 cm and 258 mL at 6.4 cm gives 213.833 mL at 6.9 cm. Relative to 219 mL, the absolute deviation is 2.359%, consistent with the reported 2.36%. This check covers that validation point. [Calibration data][yu-calibration]

The experiments connect sensor choice with the physical quantity being measured. The ultrasonic sensor measures surface distance, the conductive probe provides a water-contact decision, and the IMU identifies motion conditions that can affect liquid-level readings. The report identifies foam, sensor alignment, conductivity, contamination and motion thresholds as limitations. [Theory and limitations][yu-theory]

The laboratory record supports the proposed sensing principles. The brewery radar arrangement and the marine installation recommendations remain designs awaiting field validation. Haocheng was absent and does not claim individual hands-on work. The [retrospective Reflection 4](../Reflections/ref04.md) discusses learning from Zhenning's report. [Contribution note][yu-contribution] · [Industrial transfer][yu-brewery]

## Source record

Links below pin the reviewed evidence to Zhenning Yu's repository revision `a91cfa6491b854ff9ea7858242c6c1142b48ca65`. The current report can also be opened from his Module04 directory. [Current Module04](https://github.com/LudwigMo/sensorik-aktorik-portfolio/tree/main/Module04)

[Reflection 4 — retrospective study](../Reflections/ref04.md) · [Portfolio home](../README.md)

[yu-module]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md
[yu-contribution]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#contribution-note
[yu-ultrasonic]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#1-ultrasonic-liquid-level-measurement
[yu-calibration]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#2-volume-calibration-and-validation
[yu-foam]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#3-foam-and-tilt-interference-tests
[yu-binary]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#4-binary-water-detection
[yu-imu]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#5-imu-motion-detection-and-sea-state-classification
[yu-decisions]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#6-decision-sheet--sensor-selection-for-four-tanks
[yu-tests]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#7-test-cards
[yu-recommendations]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#8-recommendation-report
[yu-theory]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#9-theory-report
[yu-brewery]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#brewery-in-bielefeld
[yu-ultrasonic-code]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/code/ultrasonic_raw.ino
[yu-binary-code]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/code/water_sensor_binary.ino
[yu-imu-code]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/code/imu_motion_test.ino
[yu-classification-code]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/code/imu_sea_state.ino
