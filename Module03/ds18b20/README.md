# Task 2 — DS18B20 Lab Record

Date: 2026-11-04

## Current task status

The revised [course module](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md) was checked on 2026-11-04.

- [ ] 2.1: Complete the datasheet parameter notes.
- [x] 2.2: Connect one DS18B20 and confirm plausible readings.
- [ ] 2.3, optional and skipped: Connect 2–3 probes to one bus and identify each ROM ID.
- [ ] 2.4, partially completed under requirements checked on 2026-11-10: Four settings and five readings per setting were recorded. The revised task requires at least 20 readings per setting during a slow temperature sweep, checking the setResolution return value, address-specific readback and conversion-time documentation.
- [ ] 2.5, partially completed: Ten readings collected from one probe; reference and class unit-to-unit comparisons remain pending.
- [ ] 2.6: Outdoor measurements at 1–2 locations, including reference readings and field notes.
- [x] 2.7: Water and air response curves, conditional time-constant estimates and model-based settling estimates obtained. Air equilibrium was not reached; limitations are documented below.
- [ ] 2.8, optional: Self-heating comparison.

## 2.2 — Single-probe connection and first readings

- Board: ESP32 Dev Module.
- Software: Arduino IDE 2.3.10.
- Port: `/dev/cu.usbserial-0001`.
- Data pin: GPIO4.
- Libraries: OneWire 2.3.8 and DallasTemperature 4.0.6.
- Sketch: [task2-ds18b20.ino](firmware/task2-ds18b20/task2-ds18b20.ino), compiled and uploaded successfully. It was subsequently updated for the later experiments.
- Initial configuration: 12-bit resolution and 115200-baud serial output.
- One distinct probe ROM ID was observed, with plausible continuous readings. This satisfies revised Task 2.2; multiple probes are optional Task 2.3.

| Probe | ROM ID | First observed reading (°C) | Status |
|---|---|---:|---|
| A | `284E9CA200000040` | 21.3750 | Continuous reading successful |

The next three visible readings were 21.4375 °C. These were communication checks, not calibration results: thermal equilibrium was not confirmed and no reference thermometer was used. Serial output was shown in an Arduino IDE screenshot.

## 2.4 — Resolution versus accuracy

Requirements update, checked on 2026-11-10: The five constant readings per setting below do not meet the revised requirement for at least 20 readings per setting while slowly changing temperature. The earlier sketch used address-specific configuration readback, but did not report the return value of setResolution. A repeat run is required to demonstrate distinct output increments and complete the revised task.

An automatic comparison sketch was compiled and uploaded. Each setting was read back successfully and five readings were collected per setting. At the end of this run, resolution was restored to 12 bits and sampling stopped. That sketch was later replaced by the continuous logger.

| Resolution | Datasheet step (°C) | Datasheet maximum conversion time (ms) | Five observed readings (°C) |
|---:|---:|---:|---|
| 9 bit | 0.5 | 93.75 | 21.5000, 21.5000, 21.5000, 21.5000, 21.5000 |
| 10 bit | 0.25 | 187.5 | 21.2500, 21.2500, 21.2500, 21.2500, 21.2500 |
| 11 bit | 0.125 | 375 | 21.1250, 21.1250, 21.1250, 21.1250, 21.1250 |
| 12 bit | 0.0625 | 750 | 21.1250, 21.1250, 21.1250, 21.1250, 21.1250 |

Source: [Analog Devices DS18B20 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/DS18B20.pdf), pages 1–3 and 5. Conversion times above are datasheet maximum values, not measured times. The sketch requested asynchronous conversions and waited longer than the respective maximum before reading.

### Observations and limitations

- All settings were accepted and readings lie on their respective quantisation grids.
- Five identical values show no observed output change over that short segment. They do not demonstrate absence of noise or error, nor measure the minimum step directly.
- Settings were tested sequentially, so differences between their readings may also include temperature changes.
- No simultaneous reference reading was available, so closeness to the true temperature was not evaluated.
- The final summary was shown in an Arduino IDE screenshot.

### Mini check: What limits a 2 °C frost decision?

Resolution describes reporting increments; accuracy describes closeness to the true value. The specified accuracy is ±0.5 °C from −10 to +85 °C. A 0.0625 °C step at 12 bits does not imply ±0.0625 °C accuracy. At 12 bits, specified accuracy is a greater limitation than the reporting increment; placement, thermal response and independent validation also matter. At 9 bits, 0.5 °C quantisation further coarsens threshold decisions.

## 2.5 — Ten repeated readings from one probe

No reference thermometer was available. Before acquisition, the operator was asked to place the probe at a stable desktop location and avoid holding it. Ambient temperature and thermal equilibrium were not independently verified. No class data from other probes were available.

- ROM ID: `284E9CA200000040`.
- Resolution: 12 bits, confirmed by configuration readback.
- Sample interval: approximately 2.014 s; first-to-last interval: 18.126 s.
- Each reading followed a new conversion request and a 760 ms wait. All ten reads succeeded.
- Data: [Task2.5-Temperature-Repeatability.csv](evidence/Task2.5-Temperature-Repeatability.csv).

| Sample | Time from acquisition start (ms) | Temperature (°C) |
|---:|---:|---:|
| 1 | 774 | 20.8125 |
| 2 | 2788 | 20.8125 |
| 3 | 4802 | 20.8750 |
| 4 | 6816 | 20.8750 |
| 5 | 8830 | 20.8750 |
| 6 | 10844 | 20.8750 |
| 7 | 12858 | 20.8750 |
| 8 | 14872 | 20.8750 |
| 9 | 16886 | 20.8125 |
| 10 | 18900 | 20.8750 |

### Statistics and interpretation

- Mean: 20.85625 °C, reportable as approximately 20.856 °C.
- Sample standard deviation, using n−1: 0.03019 °C, approximately 0.030 °C.
- Minimum: 20.8125 °C; maximum: 20.8750 °C.
- Range: 0.0625 °C, one 12-bit quantisation step.
- Readings alternate between adjacent codes. The observed short-term spread is small, but may include quantisation, environmental variation and sensor noise.
- Standard deviation is neither accuracy nor a complete uncertainty budget. This does not justify a verified “20.856 ± 0.030 °C” accuracy statement.
- Bias, accuracy and calibration remain unevaluated without a reference. Unit-to-unit comparisons require class data or additional probes.
- The summary was shown in a screenshot. The ten-sample sketch stopped after acquisition and was later replaced.

## Hot-water observation before the response experiments

The probe was already immersed when continuous logging began. A 12-bit logger collected a new reading approximately every 1.014 s. Sending `M` records when the software receives a transfer marker; this does not establish the exact physical transfer time.

The initial observation was 68.4375 °C with a downward trend. The logger was then simplified and uploaded again. Re-uploading resets sample numbering and elapsed time, so the two runs must not be joined as one uninterrupted time series. An anomalous block timestamp in the earlier version was excluded from analysis.

A ten-point excerpt from samples 21–30 of the simplified logger was saved as [Task2-Hot-Water-Observation.csv](evidence/Task2-Hot-Water-Observation.csv). This is an excerpt, not the entire log.

- Sample 21: 64.1250 °C at 22688 ms after program start.
- Sample 30: 63.8125 °C at 31814 ms.
- Mean: 63.98125 °C.
- Range and first-to-last decrease: 0.3125 °C over 9.126 s.
- This ongoing decrease cannot be treated as steady-point repeatability. Bath cooling and probe response cannot be separated from these data.
- The excerpt and statistics were shown in a screenshot.
- With no pre-immersion baseline or immersion timestamp, this segment cannot establish the immersion response time.
- All values are probe readings, not independently verified water temperatures.

## 2.7 — Hot-to-cold transfer observation

The probe was moved into cold water while continuous logging remained active. There was no upload or reset during transfer. Serial output was exported through Arduino IDE's Copy Output control.

- [Raw serial log](evidence/Task2-Thermal-Experiments-Serial-Log.txt), including earlier runs and startup characters; subsequently updated with later experiments.
- [Hot-to-cold data](evidence/Task2.7-Hot-to-Cold-Data.csv), 286 readings from the current program run at the time of export.
- [Hot-to-cold plot](evidence/Task2.7-Hot-to-Cold-Response.png).

This run began near 64.6875 °C. Sample 137 at 140.323 s was 60.7500 °C. Gradual cooling was followed by rapid cooling: sample 153 at 156.549 s was 53.6875 °C, sample 154 was 49.8750 °C and sample 155 was 44.8125 °C. Departure from the hot bath and entry into cold water were not synchronously timestamped, so none of these readings can be identified as an exact physical transfer instant.

The software marker occurred at 191.268 s, when the reading was already near 11 °C. It is delayed and cannot serve as time zero for a time-constant calculation.

The final 20 readings in that export averaged 7.76875 °C with a 0.0625 °C range, an approximate local plateau. Sample 286 at 291.424 s was 7.7500 °C. Screenshots showed the cooling and final segment.

The response is clearly observed, but the uncertain start, cooling initial bath and non-instantaneous transfer prevent a reliable 63% time-constant estimate from this run. The subsequent cold-to-hot and air experiments address the remaining comparison. No reference thermometer verified the plateau temperature.

## 2.7 — Cold-to-hot water response

The probe was subsequently transferred back to hot water without interrupting the logger. A screenshot showed the local plateau after warming.

- [Cold-to-hot data](evidence/Task2.7-Cold-to-Hot-Data.csv): samples 430–579, 150 readings including the baseline and transfer.
- [Cold-to-hot plot](evidence/Task2.7-Cold-to-Hot-Response.png).

### Approximate 63% estimate

The cold baseline was approximately 7.9 °C. Transfer involved gradual warming before the rapid rise. The exact immersion instant was unavailable, so sample 470 was selected as an approximate start: `t0 = 478.018 s`, `T0 = 8.9375 °C`. Samples 471 and 472 were 9.9375 and 14.5000 °C, respectively.

The mean of samples 541–560 provides a local endpoint estimate: `Tf = 51.571875 °C`. It is a local probe plateau, not an independently measured constant bath temperature. The bath later cooled slowly.

```text
T63 = T0 + (1 − exp(−1)) × (Tf − T0)
    ≈ 35.8876 °C
```

Sample 480 was 35.6875 °C at 488.159 s; sample 481 was 37.0000 °C at 489.174 s. Linear interpolation gives `t63 ≈ 488.314 s` and an approximate `τ ≈ 10.30 s`. Report this as **approximately 10 s**; interpolation digits do not establish accuracy.

If a first-order model applies, 4–5τ is approximately 41–51 s. This is a model-based settling estimate, not a directly established settling time. The trace is not a perfect single exponential and the bath was cooling.

### Limitations

- Sampling was approximately every 1.014 s and the start was selected from the trace.
- Air exposure during transfer, bath cooling, mixing and immersion depth may influence the result.
- This is an effective response estimate under the experiment's conditions, not an invariant sensor specification.
- Water-temperature accuracy was not validated without a reference thermometer.
- The following air experiment completes the conditional comparison.

## 2.7 — Cooling in air and comparison with water

After removal from hot water, the operator was asked to keep the metal probe suspended without touching a desk or hand. Airflow, residual water and the exact removal instant were not independently verified. This was not a rigorously controlled dry-probe still-air test.

The logger continued without a reset:

- [Air-cooling data](evidence/Task2.7-Air-Cooling-Data.csv): samples 680–991, 312 readings including the pre-removal baseline.
- [Water and air comparison](evidence/Task2.7-Water-and-Air-Comparison.png).
- The raw serial log was updated and a screenshot showed the ongoing cooling.

Sample 700, at 711.261 s and 49.3750 °C, was selected as the approximate removal start. Subsequent readings were 49.1250, 48.8750 and 48.6250 °C. The last saved point was sample 991 at 1006.365 s and 24.2500 °C, approximately 295.104 s after the selected start. Final room-temperature equilibrium had not been reached.

### Conditional air-response estimate

Because the final plateau was not observed, `T(t) = Tf + A × exp(−t/τ)` was fitted with both final temperature and time constant as parameters. The endpoint is model-inferred, not an independent room-temperature measurement.

| First fitted sample | Fitted Tf (°C) | τ (s) | Fit RMSE (°C) |
|---:|---:|---:|---:|
| 700 | 20.793 | 140.5 | 0.213 |
| 710 | 21.081 | 136.1 | 0.187 |
| 750 | 20.915 | 139.8 | 0.074 |
| 800 | 20.103 | 155.7 | 0.030 |

Variation between fitting windows shows that the response is not perfectly described by one model. A rounded **effective air time constant of approximately 140–160 s** summarises the estimate. This is a sensitivity range, not a statistical confidence interval or full measurement uncertainty.

Compared with approximately 10 s in water, the observed air response is about an order of magnitude slower, approximately 14–16 times. Heating direction, temperature difference, surface water and fluid motion differed, so this ratio is specific to these experiments.

Under a first-order model, 4–5τ is approximately 560–800 s, or 9–13 minutes. This is an estimated settling range; an actual plateau at that duration was not observed in the saved data.

### Explanation and remaining limitations

Water generally exchanges heat with the probe more effectively than still air, consistent with the faster water response. Evaporation of residual water, natural airflow, the probe housing and cable conduction can all affect cooling in air. A more controlled repeat should fix immersion depth, stirring, position, transfer procedure and surface condition, mark transfer locally and continue to the final plateau.

Task 2.7 now has curves, conditional response estimates and a water/air comparison. Preserve these qualifications in any submission; the effective time constants are not datasheet constants. Reference-thermometer comparisons remain pending. At the end of this session's acquisition, the ESP32 continuous logger was left running.
