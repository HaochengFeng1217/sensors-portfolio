# Module 3: Sensor Characterization and Calibration

Student: Haocheng Feng. Measurements recorded on 4 and 10 November 2026.

## Learning Goals

Goal numbers follow the [Module 3 workbook](https://github.com/iotempire/iotempire-teaching/blob/129d3f0ab4d9acd43e1659769cf4777e4e2aa41e/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md#-learning-goals). Status describes the available evidence. The [completion checklist](completion-checklist.md) tracks the remaining work by task.

| Workbook goal | Experiment | Evidence | Status |
| --- | --- | --- | --- |
| **LG1 · Static characteristics.** Describe transfer function, offset, sensitivity, span, linearity, hysteresis, repeatability and resolution. | Tasks 1, 2.4–2.5, 3 and 4 · LDR, DS18B20 and ADC | [Distance response and LDR repeats](ldr-characterization/README.md), [LDR model comparison](ldr-calibration/README.md), [paired card sweeps](ldr-hysteresis/README.md), [DS18B20 resolution and repeatability](ds18b20/README.md) and [ADC offset/gain calibration](adc-calibration/README.md). | Partial. The LDR characterization and DS18B20 resolution sweep have remaining checks. Controlled hysteresis and settling comparisons are pending. |
| **LG2 · Dynamic characteristics.** Describe response time, time constant, bandwidth and self-heating. | Task 2.7 · DS18B20 water and air response | [Thermal response log and plots](ds18b20/README.md) support about 10 s in water and a model-based estimate of 140–160 s in air for the recorded setup. | Partial. The transfer timing and air conditions limit the estimates. Bandwidth and self-heating were not measured. |
| **LG3 · Calibration.** Calibrate at two points and validate at a third point. | Tasks 3a–3c · ADC, LDR and DS18B20 | [ADC calibration and fresh 1.207 V validation](adc-calibration/README.md). The [LDR model](ldr-calibration/README.md) uses an existing point held out of the fit. | Demonstrated for the ADC chain. Fresh LDR validation and reference-based DS18B20 correction remain pending. |
| **LG4 · Noise and filtering.** Quantify noise, improve data quality with filtering and explain the latency trade-off. | Tasks 5.1–5.5 · Potentiometer and LDR | [Raw noise statistics, filter replay and step response](noise-and-filtering/README.md). The [step record](noise-and-filtering/potentiometer-step/README.md) gives 20/20/40 ms relative crossing delays for MA5/median5/EMA on Run 4. | Demonstrated on the recorded traces with setup limitations. The separate decision-hysteresis test still lacks a return/reset capture. |
| **LG5 · Uncertainty.** State a simple uncertainty budget for a measured value. | Task 3a · ADC validation and Task 6 · Uncertainty | The [ADC report](adc-calibration/README.md) identifies meter, supply and acquisition limitations. | Partial. Qualitative contributions are documented. A combined numerical uncertainty budget remains pending. |

## Experiment records

| Task | Report | Recorded work and limits |
| --- | --- | --- |
| 1 | [LDR characterization](ldr-characterization/README.md) | Six distances and a separate repeatability set. ADC comparison remains pending. |
| 2 | [DS18B20 characterization](ds18b20/README.md) | Single-probe readings, resolution and repeatability observations, and thermal response in water and air. |
| 3a | [ADC-chain calibration](adc-calibration/README.md) | Two calibration points and fresh third-point validation. |
| 3b | [LDR calibration](ldr-calibration/README.md) | Power-law and linear models checked against an existing point. Fresh validation remains pending. |
| 4.1 | [LDR hysteresis and repeatability](ldr-hysteresis/README.md) | Two paired card sweeps. Controlled speed and timed settling comparisons remain pending. |
| 5 | [Noise, filtering and hysteresis](noise-and-filtering/README.md) | Five subtask reports with raw traces, filter comparisons and decision results. |

The [completion checklist](completion-checklist.md) covers the remaining measurements and peer review. [Reflection 3 — draft for review](../Reflections/ref03.md) · [Portfolio home](../README.md) · [Course workbook](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md)

## Study log

### Scope and assistance

This portfolio records the measurements available from these sessions. The student handled physical wiring, light changes and probe movements. An LLM assisted with procedures, Arduino IDE operation, calculations, plots and documentation. Numeric results were checked against saved raw logs or explicitly identified operator readings. Unrecorded partner contributions and peer checks are not claimed.

### References used

- [Module 3 workbook](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md): distinguish measurement-chain noise, sensor-chain variability, calibration validation and decision hysteresis.
- [DS18B20 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/DS18B20.pdf): resolution and conversion time differ from accuracy. Recorded thermal response times describe the experimental assembly and conditions, not a universal datasheet time constant.

### Questions, findings and verification

| Question or issue | Finding | Verification and limitation |
| --- | --- | --- |
| Can changed-light LDR repeats be merged with the original distance sweep? | Keep them as separate conditions. | The operator reported changed ambient light; the separate repeatability record preserves its measured supply and three readings. |
| Does calibration improve the chain at a fresh point? | The fresh 1.207 V validation residual is approximately +3.05 mV after correction, compared with +21.72 mV from the library voltage conversion. | See the ADC record, raw evidence and plot; this is not a complete uncertainty statement. |
| Which filter handles one isolated spike best here? | The LDR median5 replay changes by at most 2 codes for the explicitly synthetic +500-code single-sample spike. | Same measured input and matching indices; original logs are unchanged. See Task 5.3. |
| What does smoothing cost? | Potentiometer Run 4 has relative 50%-crossing delays of 20/20/40 ms for MA5/median5/EMA. | Independent filter recomputation; finite-speed manual input and one later zero-code outlier limit generalisation. |
| Did hysteresis reduce repeated switching? | The same measured LDR Run 2 gives five single-threshold switches versus one hysteresis switch. | Both decision columns independently replayed exactly; no full return/reset was captured. |
| Where was the initial approach wrong? | The first 5.5 thresholds were above the observed signal excursion and neither decision switched. | Run 1 is preserved. Corrected thresholds were fixed before Run 2, rather than changing Run 1 retrospectively. |

### Mini-check answers supported by these records

- Which filter would I ship for the frost alarm? Use a filter suited to measured temperature noise together with decision hysteresis; justify the total response delay and uncertainty at the alarm threshold. The light demonstration alone does not validate a temperature alarm.
- What is the difference between hysteresis and smoothing? Hysteresis preserves the previous decision inside two thresholds; smoothing changes the signal and adds lag. Task 5.5 changes the decision without filtering its input.
- What would I improve next? Obtain the missing reference comparisons and controlled validation, check sensor response direction, and record the hysteresis return/reset cycle.

### Remaining study-log work

Two independently found characterization examples, a complete search log, peer-verified mini checks, the neighbouring-pod exchange and agreed-learning note remain unrecorded. The thermal-response and LDR-model plots are candidate artefacts for discussion, not substitutes for those required external examples or a documented peer exchange. See the [completion checklist](completion-checklist.md).
