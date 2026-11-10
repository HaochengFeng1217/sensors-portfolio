# Task 1 — LDR Transfer Function Lab Record

Date: 2026-11-04  
Status: Six distance measurements completed. A separate 15 cm repeatability set has been calculated under changed ambient light using a newly measured 3.330 V supply. All three voltages have been confirmed by the operator; ADC acquisition remains pending.

## Objective

Measure LDR resistance at different light-source distances, investigate the relationship between light and resistance, and compare power-law and linear models.

## Circuit and method

- Board: ESP32.
- Recorded circuit orientation: `3V3 → LDR → divider node → 10 kΩ fixed resistor → GND`.
- Measured supply voltage: `Vs = 3.35 V`.
- The fixed resistor is treated as its nominal value of `10 kΩ`; its actual resistance has not been measured.
- Multimeter readings in this dataset are **voltages across the LDR**, not divider-node voltages relative to ground.
- The photographs appear to show a phone flashlight; its exact settings have not been confirmed. No lux readings were recorded.
- The six photographs were identified as 5, 10, 15, 20, 25 and 30 cm, respectively. Voltages were transcribed from the photographs.

## Accepted dataset

```text
Vout = Vs − V_LDR
R_LDR = R_fixed × V_LDR / (Vs − V_LDR)
E_relative = (5 cm / d)²
```

Relative illuminance assumes inverse-square behaviour and is normalised to 1 at 5 cm. It is not measured lux and does not subtract ambient light.

| Distance d (cm) | Measured V_LDR (V) | Calculated Vout (V) | Calculated R_LDR (kΩ) | Estimated relative illuminance |
|---:|---:|---:|---:|---:|
| 5 | 0.13 | 3.22 | 0.404 | 1.00000 |
| 10 | 0.20 | 3.15 | 0.635 | 0.25000 |
| 15 | 0.36 | 2.99 | 1.204 | 0.11111 |
| 20 | 0.51 | 2.84 | 1.796 | 0.06250 |
| 25 | 0.62 | 2.73 | 2.271 | 0.04000 |
| 30 | 0.78 | 2.57 | 3.035 | 0.02778 |

Calculated decimal places preserve the calculation; they do not establish measurement accuracy.

## Preliminary analysis

Both the voltage across the LDR and its calculated resistance increase with distance, consistent with resistance increasing as illumination decreases. Resistance increases by approximately 7.5 times between 5 and 30 cm.

A least-squares fit of `ln(R_LDR / kΩ)` against `ln(E_relative)` using all six points gives:

```text
R_LDR ≈ 0.352 × E_relative^(−0.579) kΩ
γ ≈ 0.579
R² in log space ≈ 0.976
Resistance-space fit RMSE ≈ 0.121 kΩ
```

These provisional results depend on the inverse-square assumption. Ambient light, source directionality, distance and angle errors may affect the fit. This is not an absolute lux calibration. Fit residuals are not a complete measurement uncertainty budget. All six points were used here, so this particular fit has no held-out validation point.

## Study log

- Source: [Module 3 — Sensor Characterization, Calibration & Data Quality](https://github.com/iotempire/iotempire-teaching/blob/main/full-classes/hsbi-sensors-actuators-10d/modules/03-sensor-characterization-and-calibration.md).
- Main understanding: When measuring across the LDR, subtract that voltage from the supply to obtain the fixed-resistor voltage. The series current then determines LDR resistance.
- Observation: Resistance increases monotonically with source distance in the accepted dataset.
- LLM assistance: Reading the photographs, calculating resistance and fitting a provisional power law. Independent verification with ADC data or direct resistance measurements remains pending.
- Data revision: The earlier distance-series voltages of 0.65, 0.50, 0.78, 0.74, 0.78 and 0.81 V were replaced by the accepted dataset above and are excluded from this fit. The earlier 1.43 V ambient-light reading was a separate circuit check and is also excluded.

## Pending work

- [x] Record three repeated voltages at nominally 15 cm and calculate resistance spread. This separate run used changed ambient light and a confirmed 3.330 V supply.
- [ ] Record the ADC pin, acquisition settings and raw codes at each level; compare against the multimeter.
- [ ] Compare repeatability spread with the resistance change corresponding to one ADC step at that light level.
- [ ] Produce the all-six-point log–log fit plot and residuals.
- [ ] Fit a linear `R = a E_relative + b` model to the same six points and compare residuals in resistance units.
- [ ] Document source settings, distance measurement, ambient-light control and fixed-resistor information.
- [ ] Submit class-table rows and compare slopes with a neighbouring pod, if applicable.

Additional hardware measurements were postponed because the multimeter was temporarily unavailable.

The subsequent [Task 3b record](../ldr-calibration/README.md) uses only the 5 and 30 cm points for calibration and the 15 cm point for validation. That analysis is separate from this all-six-point characterization fit.

## Additional 15 cm readings under changed ambient light

Three photographs were supplied in response to the request for 15 cm repeated measurements. The operator explicitly reported that ambient light had changed. The meter in this set is a UNI-T UT139B, different from the meter in the original distance series. Exact measurement intervals and stability of illumination within this new set were not confirmed.

The operator subsequently reported a measured supply voltage of **3.330 V**. With the fixed resistor still treated as its nominal 10 kΩ value:

```text
R_LDR = 10000 × V_LDR / (3.330 − V_LDR) [Ω]
```

| Reading | Voltage across LDR (V), operator-confirmed | Calculated resistance (kΩ) |
|---:|---:|---:|
| 1 | 0.709 | 2.70507 |
| 2 | 0.704 | 2.68088 |
| 3 | 0.698 | 2.65198 |

The operator confirmed the second reading as 0.704 V and corrected the first reading to 0.709 V. The final accepted sequence is 0.709, 0.704 and 0.698 V. Voltage is interpreted as being measured across the LDR, consistent with the preceding procedure; the complete electrical connections cannot be established solely from the photographs.

Voltage statistics for the confirmed readings:

- Mean: 0.70367 V.
- Sample standard deviation, denominator n−1: 0.00551 V.
- Range: 0.011 V.

The sequence decreases slightly. With only three readings and no simultaneous light measurement, this cannot distinguish noise from illumination changes, settling, contact changes or operator shadowing. If conditions were constant within this set, it provides a short repeatability check under the new lighting conditions.

Resistance statistics using the new 3.330 V supply and confirmed voltages:

- Mean resistance: 2679.31 Ω, approximately 2.679 kΩ.
- Sample standard deviation, denominator n−1: 26.58 Ω.
- Minimum: 2651.98 Ω; maximum: 2705.07 Ω.
- Range: 53.10 Ω.

Calculate each resistance before taking its mean. These statistics describe the observed spread, not absolute accuracy or a complete measurement uncertainty. Supply variation during the three readings was not separately recorded. The comparison with one ADC step remains pending.

Data file: [Task1-LDR-15cm-Repeatability.csv](evidence/Task1-LDR-15cm-Repeatability.csv).

Keep this dataset separate from the original 15 cm reading of 0.36 V and from the six-point calibration dataset. A changed physical light input and a different meter mean the difference from the earlier reading is not evidence of LDR drift, hysteresis or calibration error. This set is not an equivalent-condition validation of the Task 3b model.

Repeatability requires stable conditions within the new run; it does not require recreating the earlier ambient light. To validate or replace the earlier distance model under the new lighting, remeasure calibration and validation levels under a common controlled setup.
