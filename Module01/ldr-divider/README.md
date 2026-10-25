# Task 4: An Analog Light Sensor — the LDR

Experiment date: 25 October 2026. Student: Haocheng Feng.

The LDR divider was built and photographed. Twelve hardware trials, each containing ten readings, were saved with serial screenshots: room light, partial shade, an initial cover attempt, a revised dark cover, phone flashlight, and restored room light. The core Task 4 experiment and documentation are complete. Voltage estimates have not been checked with an external multimeter.

## Circuit and operating principle

```text
3V3 ---- LDR ----+---- 10 kOhm ---- GND
                |
             GPIO34
```

![Actual divider wiring](wiring.jpg)

Hardware: Joy-IT SBC-NodeMCU-ESP32-C, a bare two-terminal LDR and a nominal 10 kOhm fixed resistor. The photographed resistor bands appear to be brown-black-black-red-brown, read from the right side of the component photograph, indicating 10 kOhm with 1% tolerance. Its resistance and the supply voltage were not independently measured. The LDR model is unknown.

The LDR has no polarity. The junction of the LDR and fixed resistor is the measurement node. For this orientation, increasing light typically lowers LDR resistance, raises the measurement-node voltage and increases the ADC code. A high-impedance ADC input is assumed in the divider equation.

## Acquisition method

The firmware compiled and uploaded successfully, with the upload hash verified. It uses GPIO34, 12-bit output, ADC_11db attenuation, a nominal 300 ms sampling interval and 115200 baud. Ten readings span approximately 2.7 seconds from first to last sample. Each trial pauses after printing its summary, allowing its data to be captured before the next trial. Twelve trials contain 120 saved DATA rows; each trial's sample numbers 1–10 were checked, and computed summaries agree with the printed summaries.

Commands D, S, R and F label the conditions Dark, Shade, Room and Flashlight. The labels represent the lighting established by the student, not automatic recognition of illumination. The student confirmed the shade, cover, revised cover, flashlight and restored-room conditions before acquisition. For the initial room trial, the student had been asked to leave the circuit exposed to unchanged room lighting.

The student was instructed to keep the flashlight about 15–20 cm away and hold its angle fixed; the distance and illumination were not independently measured. There was no lux meter or controlled light source. Two sequential trials were taken at each setup without a deliberate repositioning between those two trials; room light was additionally measured again after removing the other lighting conditions.

`analogRead()` provides Raw and `analogReadMilliVolts()` provides ADC_mV using the installed ESP32 core's calibration routine. These APIs perform two successive conversions, so a row's Raw and ADC_mV are not one shared conversion. ADC_mV is an ADC-based voltage estimate, not an external meter measurement. It is different from the assumed raw × 3.3 / 4096 voltage used in Task 3.

## Results

| Condition | Trials | Samples | Raw range (12-bit) | ADC voltage range (V) | Mean ADC voltage (V) |
| --- | --- | ---: | --- | --- | ---: |
| Dark — revised cover | 3, 4 | 20 | 0–0 | 0.142–0.142 | 0.14200 |
| Shade | 1, 2 | 20 | 1163–1187 | 1.069–1.095 | 1.08275 |
| Room — initial | 1, 2 | 20 | 3394–3445 | 2.795–2.839 | 2.80490 |
| Flashlight | 1, 2 | 20 | 3715–3779 | 2.977–2.998 | 2.98535 |
| Room — restored | 3, 4 | 20 | 3389–3439 | 2.791–2.820 | 2.80575 |

Each row above combines two ten-reading trials. The revised dark cover reached the lower raw limit: Raw = 0 in all twenty readings. The ADC routine returned 0.142 V for those readings; this repeated endpoint value must not be treated as a verified physical voltage or evidence that electrical noise is absent. It was excluded from the resistance calculation.

The main observed ordering was revised dark < shade < room light < phone flashlight. The flashlight readings remained below Raw = 4095. No lux calibration or claim of a linear raw-code-to-light relationship is made.

### Initial cover attempt and method correction

The initial attempts labelled Dark (trials 1–2) produced higher values than Shade and more variation. Trial 1 had a raw range of 1815–1887 and trial 2 had 1667–1951. This did not support treating the initial cover as darker than the shade setup. The student then changed the covering method to block the front and sides without disturbing the connections, and confirmed readiness before trials 3–4. Those revised trials reached Raw = 0.

The initial trials were retained in the dataset and full table below. Light leakage, changes in geometry or movement are possible explanations, but none was isolated experimentally. Conditions were defined by the physical procedure, not relabelled to force the expected numerical ordering.

## Worked resistance estimate

For the chosen divider:

`Vout = Vsupply × Rfixed / (RLDR + Rfixed)`

`RLDR = Rfixed × (Vsupply − Vout) / Vout`

The first saved reading of Shade trial 1 was Raw = 1168 with ADC_mV = 1089. Using this actual intermediate-range ADC voltage estimate, nominal Rfixed = 10000 ohm and assumed Vsupply = 3.3 V:

`RLDR ≈ 10000 × (3.3 − 1.089) / 1.089 ≈ 20303 ohm ≈ 20.3 kOhm`

This is an approximate resistance inferred from the divider, not a resistance-meter measurement. Assumptions include a 3.3 V supply, nominal 10 kOhm resistance, negligible ADC loading, an adequate ADC voltage estimate and a sufficiently stable input. Unknown supply voltage, resistor tolerance, ADC error, source impedance and contact quality limit the estimate. No finite resistance is inferred from a zero-voltage reading, and endpoint readings are not used for this calculation.

## Repeatability and limitations

Initial room trials had mean raw values of 3412.6 and 3402.9. After the student turned off the flashlight, removed the cover and restored the initial room-light arrangement, the means were 3403.5 and 3406.0. The combined initial and restored ADC-voltage means were 2.80490 V and 2.80575 V, a difference of 0.00085 V (0.85 mV). The observed return to a similar room-light reading supports approximate repeatability in this session; it does not establish calibrated accuracy or reproducibility across different setups or days.

Shade trial means were 1167.2 and 1171.1 raw codes; flashlight trial means were 3742.4 and 3753.5. These close sequential trial means describe short-term stability while the setup was held approximately fixed. The initial covering attempt shows that lighting geometry and procedure can have a much larger effect than this within-setup variation.

An LDR is nonlinear, temperature-dependent and relatively slow when illumination changes. No lux calibration, temperature dependence or response time was measured. Dark endpoint saturation prevents a quantitative comparison of very low light levels. A multimeter was unavailable, so voltage accuracy remains independently unverified.

## Full trial table

| Condition | Trial | n | Raw min–max | Raw mean | ADC voltage min–max (V) | Mean ADC voltage (V) |
| --- | ---: | ---: | --- | ---: | --- | ---: |
| Room | 1 | 10 | 3403–3445 | 3412.6 | 2.795–2.839 | 2.8084 |
| Room | 2 | 10 | 3394–3423 | 3402.9 | 2.797–2.806 | 2.8014 |
| Shade | 1 | 10 | 1163–1168 | 1167.2 | 1.074–1.095 | 1.0828 |
| Shade | 2 | 10 | 1163–1187 | 1171.1 | 1.069–1.088 | 1.0827 |
| Dark (initial cover) | 1 | 10 | 1815–1887 | 1853.4 | 1.596–1.714 | 1.6335 |
| Dark (initial cover) | 2 | 10 | 1667–1951 | 1830.4 | 1.544–1.970 | 1.6839 |
| Dark | 3 | 10 | 0–0 | 0.0 | 0.142–0.142 | 0.1420 |
| Dark | 4 | 10 | 0–0 | 0.0 | 0.142–0.142 | 0.1420 |
| Flashlight | 1 | 10 | 3715–3760 | 3742.4 | 2.977–2.991 | 2.9835 |
| Flashlight | 2 | 10 | 3735–3779 | 3753.5 | 2.983–2.998 | 2.9872 |
| Room | 3 | 10 | 3389–3436 | 3403.5 | 2.791–2.814 | 2.8045 |
| Room | 4 | 10 | 3392–3439 | 3406.0 | 2.800–2.820 | 2.8070 |

## Evidence and reproducibility

- [Firmware](ldr-divider.ino)
- [Original circuit photograph](wiring.jpg)
- [Resistor photograph](fixed-resistor.jpg)
- [LDR photograph](ldr-component.jpg)
- [Upload verification screenshot](upload-result.png)
- [All 120 readings with source files](measurements/readings.csv)
- [Trial summaries](measurements/trial-summary.csv)
- [Room-light evidence](measurements/room-02.png)
- [Shade evidence](measurements/shade-02.png)
- [Initial cover evidence](measurements/dark-02.png)
- [Revised dark-cover evidence](measurements/dark-04.png)
- [Flashlight evidence](measurements/flashlight-02.png)
- [Restored-room evidence](measurements/room-04.png)

Screenshots are original captures of the live Serial Monitor; corresponding AX text records preserve the displayed serial data. Summary CSV and tables are derived from the recorded DATA rows. Some header fragments in the monitor were duplicated or incomplete; those were not interpreted as DATA readings.

Source: [HSBI Module 1, Task 4](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/01-foundations-measurement-and-sensor-chain.md).

The instructor-requested scope ends after Task 4. Task 5 filtering has not been performed.
