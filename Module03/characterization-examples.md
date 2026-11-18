# Two external characterization examples

Added during the 18 November 2026 documentation review. Codex located and checked these manufacturer examples. They are later study material, not an invented in-class search or pod consensus, and neither device was tested in this review.

## 1. VL53L0X: ranging dispersion depends on test conditions

ST's Table 13 characterizes ranging accuracy using standard deviation, including measurement and part variation. At 120 cm with a white 88%-reflectance target indoors without infrared background, it gives 4% for a 33 ms budget and 3% for 66 ms. Conditions include 2.8 V, 23 °C, full 25° field-of-view coverage, prior 10 cm offset correction and at least 94% detection.

Lesson: a range or accuracy number needs its test conditions and statistical meaning. Those percentages are not a universal maximum absolute error. Similarly, the lab LDR distance model is conditional on illumination and geometry, and cannot establish calibrated lux.

Source checked: [ST VL53L0X datasheet, DS11555 Rev. 6, June 2024](https://www.st.com/resource/en/datasheet/vl53l0x.pdf), Section 6.3.1, Table 13, printed page 23.

## 2. ADXL345: noise changes with acquisition settings

Analog Devices' Noise Performance section compares normal and low-power modes. For normal mode above 100 Hz output data rate, noise increases approximately by a factor of square root of two for each rate doubling. Figure 51 compares noise against output data rate, with axes and power modes separated. The typical data apply under stated configuration conditions, not to every accelerometer installation.

Lesson: compare noise only after stating bandwidth/rate and mode. A lower spread from a slower or differently filtered acquisition need not mean the sensor itself became better. This reinforces the Module 3 separation of chain baseline, changed sensor conditions and filtering latency. ADXL345 is an external example here, not the BMI270 tested by Zhenning in Module 4.

Source checked: [Analog Devices ADXL345 datasheet, Rev. G](https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf), Noise Performance, Figure 51, printed page 33.

## Review trail

| Review question | Source location checked | What was established |
| --- | --- | --- |
| Is the VL53L0X percentage a context-free error guarantee? | Table 13 and its measurement conditions | No; the definition and conditions must accompany it. |
| Can acquisition mode/rate affect observed sensor noise? | ADXL345 Noise Performance and Figure 51 | Yes; mode/rate belong in a noise comparison. |

The checked primary documents and conclusions are recorded here; no earlier search activity or personal verification is inferred. [Module 3 study log](README.md#study-log)
