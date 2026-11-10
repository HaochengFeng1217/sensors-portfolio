# Task 4.1 — LDR hysteresis and repeatability

Date: 2026-11-10. Two paired card sweeps are recorded.

| Sweep | Report | Maximum absolute outward–return difference |
| --- | --- | ---: |
| 1 | [First paired sweep](sweep-1/README.md) | 84.73 ADC codes at mark 3 |
| 2 | [Second paired sweep](sweep-2/README.md) | 147.40 ADC codes at mark 2 |

Each included block contains 100 readings. Sweep 2 uses the second outward capture at mark 2, as selected by the operator. The full export retains both captures. The recorded difference is in divider ADC output at matched card marks. Actual light level, divider orientation, supply voltage and card travel speeds were not independently measured. Sweep 2 had a 119.142 s interval between the turnaround capture and the first return capture.

The controlled speed comparison and timed settling test remain pending. Potentiometer mechanical repeatability and the DS18B20 resolution and probe comparison are tracked in the [module checklist](../completion-checklist.md).

[Arduino acquisition sketch](firmware/task4-ldr-sweep/task4-ldr-sweep.ino) · [Module 3 overview](../README.md)
