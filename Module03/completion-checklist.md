# Module 3 — Completion Checklist

Reviewed: 2026-11-10. This audit compares the saved evidence and this session's measurements with the current [course module](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md). Unrecorded work performed elsewhere is not assessed. Prepared for repository submission under Module03. Discord posting has not been verified.

## Task status

| Task | Status | Existing evidence | Remaining work |
|---|---|---|---|
| 1: LDR characterization | Partial | Six distances, measured voltages, calculated resistance, six-point power-law coefficients; separate three-reading repeatability set | ADC measurements and meter comparison; one-ADC-step resistance comparison; all-six-point fit/residual plots and same-data linear comparison; conditions and class comparison where applicable |
| 2.1: Datasheet notes | Partial | Resolution, conversion times, accuracy and pull-up discussed | Complete active/standby-current notes and consolidate the required parameters |
| 2.2: Single DS18B20 | Complete | Successful upload, ROM ID and plausible continuous readings | None for this subtask |
| 2.3: Multiple probes | Optional, not performed | One probe only | May be skipped |
| 2.4: Resolution sweep | Partial under revised requirements | Four settings read back; five readings per setting; datasheet timing table | At least 20 readings per setting while slowly changing temperature; check setResolution return value; demonstrate distinct increments and document conversion time |
| 2.5: Unit comparison | Partial | Ten 12-bit readings from one probe, mean and sample standard deviation | Reference comparison and class unit-to-unit comparison |
| 2.6: Outdoor transect | Not recorded | None | Measure 1–2 locations with the specified reference and field notes |
| 2.7: Thermal response | Completed with experimental qualifications | Water and air curves; approximate water τ of 10 s and model-based air τ of 140–160 s; model-based settling estimates | Retain the timing, wet-probe and inferred-air-endpoint limitations; a controlled repeat would strengthen evidence |
| 2.8: Self-heating | Optional, not performed | None | May be skipped |
| 3a: ADC-chain calibration | Core experiment completed on 2026-11-10 | Calibration at 0.482 and 2.009 V; fresh 1.207 V validation; residual reduced from +21.72 to +3.05 mV; English record and plot | Meter/supply details, numerical uncertainty and neighbouring-pod comparison/check |
| 3b: LDR calibration | Partial | Two-point power-law and linear models, held-out existing-point comparison, plot and residuals | Fresh validation in equivalent conditions, completed calibration-record template, uncertainty statement and peer check |
| 3c: DS18B20 correction | Not completed | No suitable reference thermometer | Reference comparisons at two temperatures, cold-point offset correction and independent ice-water validation |
| 4: Hysteresis and repeatability | Mostly not performed | Ten 12-bit DS18B20 readings can support part of the analysis | LDR up/down sweeps at two speeds and with pauses; ten potentiometer returns; ten DS18B20 readings at 9 and 12 bits, with specified probe comparisons; conclusions |
| 5: Noise and filtering | 5.1–5.5 evidence recorded on 2026-11-10, with stated limitations | Three separate 500-sample potentiometer runs; Run 3 has SD 11.281 codes and steadier block means; earlier runs retained; potentiometer filter/spike rehearsal saved; three disturbed step captures retained; Run 4 provides qualified filter crossing-delay evidence (20/20/40 ms) | Run 3 is a provisional chain baseline with unverified meter stability; 5.5 demonstrates 5 versus 1 switches; complete hysteresis return/reset remains unmeasured |
| 6: Uncertainty and declarative filtering | Extension, not performed | Qualitative limitations only | Full numerical uncertainty budget and filter comparison if attempted; a final uncertainty statement is also suggested portfolio evidence |
| A: Study log | Partial | English notes, references, findings and calibration reasoning across records | A consolidated study log is included in Module03/README.md; complete search notes, verified LLM Q&A, two found examples and mini-check answers; identify contributors |
| B: Peer exchanges | Not documented | None | Calibration peer check, mutual findings, 3–5 agreed takeaways, shared artefact, Discord post and individual agreed-learning note |

## Important distinctions

- Three LDR repeats at 15 cm are recorded: 0.709, 0.704 and 0.698 V with a 3.330 V supply. Mean resistance is 2.679 kΩ, sample SD is 26.6 Ω and range is 53.1 Ω. Changed ambient light prevents merging them with the original distance series.
- Task 3b's two-point plots do not replace Task 1's all-six-point model comparison.
- The earlier 2.4 run met only the simpler earlier procedure; the revised sweep requirement remains outstanding.
- The existing Task 3b held-out point was excluded from fitting but was not freshly measured. Its +15.5% power-law error is model error, not uncertainty.
- A temperature-capable multimeter was considered but rejected as an accuracy reference; it did not complete reference-dependent tasks.
- Optional exercises include the dead-band study, optional LDR dynamic/field work, DHT11 comparison, wider filter toolbox and 5a. None is counted as a missing core experiment here.

## Suggested order before the checkpoint

1. Organise and verify portfolio placement and submission; prepare water/air response and LDR model comparison as the two discussion examples.
2. Finish documentation-only gaps, including Task 1 plots and the unified study log.
3. Retain the completed ADC-chain calibration and both 500-point datasets; strengthen matched-condition noise comparison and the hysteresis return/reset evidence.
4. Repeat the revised resolution sweep and obtain a fresh controlled LDR validation point.
5. Arrange reference-dependent measurements and peer exchange with the instructor or neighbouring pod.

This checklist describes evidence available here; it does not claim completion or submission of unverified work.
