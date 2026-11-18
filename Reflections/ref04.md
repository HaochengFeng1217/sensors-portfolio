# Reflection 4 — Liquid measurement and sensor selection

[Reflection index](README.md) · [Module evidence](../Module04/README.md) · [Portfolio](../README.md)

> **Retrospective study draft** · Haocheng was absent; Zhenning Yu performed all Module 4 experiments. This reflection interprets the shared records and does not claim attendance or hands-on participation. [Reflection prompts](TEMPLATE.md) · [Contribution statement][contribution]

## Take-away

My takeaway is to start with the decision the measurement must support. Knowing remaining volume needs a continuous estimate; detecting water at a critical height may only need a binary switch. A hybrid arrangement can provide both information and a separate alarm. I would choose the sensing principle, calibration and failure response together, then verify them in the intended liquid and tank. [Selection evidence][selection]

## What was good?

The report includes calibration points and a separate validation point, making its calculation checkable. Interpolation at 6.9 cm gives 213.83 mL against approximately 219 mL reference volume: an underestimation of about 5.17 mL, or 2.36% relative deviation. Keeping that point outside the fit makes it a useful local check; one result does not establish accuracy across the whole tank. [Calibration and validation][calibration]

## What was difficult?

The foam-and-tilt test shows that a plausible electronic reading can still be affected by the physical setup. Foam distribution, surface position and container orientation changed together, so the observations do not isolate their individual effects. I would repeat the test with fixed mounting and one controlled disturbance at a time before attributing a change to foam alone. Filtering can reduce fluctuations, but it cannot establish that the measured surface is the intended one. [Interference test][interference]

## Exploration and show stoppers

Motion classification could help qualify a level reading, but the ultrasonic sensor and IMU were not recorded synchronously. I would test whether unreliable level readings actually coincide with the motion indicator. The near-boundary classification at approximately 0.024 g also shows why laboratory thresholds must be validated rather than treated as real sea-state definitions. Slow tilt can leave the acceleration magnitude close to 1 g, so that metric alone cannot reliably characterize orientation. [Motion experiments and limitations][motion]

## Interaction with peers and instructors

I was absent from this session, so I have no first-hand classroom discussion or instructor feedback to report. Zhenning Yu's documented work provides the learning material for this retrospective reflection. I would use the limitations identified in the report to prepare questions for a future discussion, especially how to validate motion thresholds and test an independent alarm.

## How did you verify AI suggestions?

Codex checked the source-table interpolation during this review:

```text
205 + (7.0 − 6.9) / (7.0 − 6.4) × (258 − 205) = 213.833 mL
Absolute deviation from 219 mL = 2.359% ≈ 2.36%
```

This verifies the arithmetic against the recorded table; it does not verify the scale, distance readings or reference volume. The review also distinguishes proposed marine and brewery designs from tested laboratory hardware. This was a documentation check, not my independent bench verification. [Source data][calibration] · [Portfolio study log](../Module04/README.md#study-log)

## Help and extra work

Zhenning Yu’s report, photographs and programs provided the learning material. Codex helped draft this reflection and check the arithmetic. I did not perform the experiments, give a classroom presentation or provide bench assistance during the missed session.

## Learning-goal self-assessment

The reviewed evidence supports a discussion of continuous and binary measurements, volume calibration, motion effects and application-specific selection. I can use the recorded examples to explain why a demonstrated laboratory principle still needs validation for a real installation. Independent alarm operation, performance with the actual liquids and tank geometry, a numerical uncertainty budget, and synchronized motion/level testing remain open. Because I missed the session, my practical competency is not demonstrated by this review of a teammate's evidence; a future hands-on repeat would provide separate evidence. [Learning-goal coverage](../Module04/README.md#learning-goals)

[calibration]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#2-volume-calibration-and-validation
[interference]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#3-foam-and-tilt-interference-tests
[motion]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#5-imu-motion-detection-and-sea-state-classification
[selection]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#6-decision-sheet--sensor-selection-for-four-tanks
[contribution]: https://github.com/LudwigMo/sensorik-aktorik-portfolio/blob/a91cfa6491b854ff9ea7858242c6c1142b48ca65/Module04/README.md#contribution-note
