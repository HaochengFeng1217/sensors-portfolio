# Sensor Characterization and Calibration — Lab Records

Measurements: 2026-11-04 and 2026-11-10. Compiled: 2026-11-10. All lab records, plot labels, filenames and data headings are in English.

## Records

- [Task 5.4 — Potentiometer transition and qualified delay estimates](./Task5.4-Potentiometer-Step-Lab-Record.md)
- [Task 5.3 — Potentiometer filter rehearsal](./Task5.3-Potentiometer-Filter-Rehearsal.md)
- [Module 3 completion checklist, reviewed 2026-11-10](./Module3-Completion-Checklist.md)
- [Task 1 — LDR characterization](./Task1-LDR-Lab-Record.md)
- [Task 2 — DS18B20 characterization and thermal response](./Task2-DS18B20-Lab-Record.md)
- [Task 3a — ADC chain calibration and fresh validation](./Task3a-ADC-Calibration-Lab-Record.md)
- [Task 3b — LDR two-point calibration and validation](./Task3b-LDR-Calibration-and-Validation.md)
- [Task 5 — Noise and filtering, 5.1–5.5 evidence and limitations](./Task5-Noise-and-Filtering-Lab-Record.md)

## Plots

- [Potentiometer Run 3: steadier chain baseline](./Task5.1-Potentiometer-Run3-Noise.png)
- [Two potentiometer acquisitions compared](./Task5.1-Potentiometer-Runs-Comparison.png)
- [Potentiometer raw-noise acquisition](./Task5.1-Potentiometer-Noise.png)
- [ADC calibration and fresh validation](./Task3a-ADC-Calibration-and-Validation.png)
- [Hot-to-cold response](./Task2.7-Hot-to-Cold-Response.png)
- [Cold-to-hot response](./Task2.7-Cold-to-Hot-Response.png)
- [Water and air comparison](./Task2.7-Water-and-Air-Comparison.png)
- [LDR models and validation](./Task3b-LDR-Models-and-Validation.png)

## Data and firmware

- [LDR repeatability at 15 cm under changed ambient light](./Task1-LDR-15cm-Repeatability.csv)
- [Temperature repeatability](./Task2.5-Temperature-Repeatability.csv)
- [Hot-water observation excerpt](./Task2-Hot-Water-Observation.csv)
- [Hot-to-cold data](./Task2.7-Hot-to-Cold-Data.csv)
- [Cold-to-hot data](./Task2.7-Cold-to-Hot-Data.csv)
- [Air-cooling data](./Task2.7-Air-Cooling-Data.csv)
- [Raw serial log](./Task2-Thermal-Experiments-Serial-Log.txt)
- [LDR calibration and validation calculations](./Task3b-LDR-Calibration-and-Validation.csv)
- [LDR calculation results](./Task3b-Calculation-Results.json)
- [DS18B20 acquisition sketch](./task2-ds18b20/task2-ds18b20.ino)

Measured values and pending work are documented separately from assumptions, calculations and model estimates in each record.

- [Task 5.4 Run 3: trace and validity assessment](./Task5.4-Potentiometer-Step-Lab-Record.md#repeat--run-3)
- [Task 5.4 Run 3 full trace](./Task5.4-Potentiometer-Step-Run3.png)

- [Task 5.4 Run 4 full trace and crossing detail](./Task5.4-Potentiometer-Step-Run4.png)

- [Task 5.2 — LDR noise and qualified chain-baseline comparison](./Task5.2-LDR-Noise-Lab-Record.md)

- [Task 5.3 — LDR filter and synthetic spike comparison](./Task5.3-LDR-Filter-Comparison.md)

- [Task 5.5 — measured hysteresis chatter reduction and limits](./Task5.5-LDR-Hysteresis-Lab-Record.md)


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

Two independently found characterization examples, a complete search log, peer-verified mini checks, the neighbouring-pod exchange and agreed-learning note remain unrecorded. The thermal-response and LDR-model plots are candidate artefacts for discussion, not substitutes for those required external examples or a documented peer exchange. See the [completion checklist](./Module3-Completion-Checklist.md).
