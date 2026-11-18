# Portfolio completeness review

[Portfolio](README.md) · [Module records](README.md#modules) · [Reflections](Reflections/README.md)

Reviewed: 18 November 2026. Scope: Module 0 (pre-study) and Modules 1–5 currently represented in the portfolio. Later modules are not assessed. This is an evidence audit, not a claim of complete course competency. All additions below are documentation, source checks or calculations from saved data; no new hardware experiments were performed during this review.

## What was added or corrected now

| Module | Immediate addition / correction | Remaining evidence gaps |
| --- | --- | --- |
| 0 · Pre-study | Replaced nine supplementary-study TODOs with linked notes and explanations; recognized later Arduino/PlatformIO readiness; separated written answers from personal understanding. | Personal review, instructor-access confirmation, and implementation of the proposed storage-box project. |
| 1 · Foundations | Added measurement vocabulary, ideal ADC step calculations, sampling/aliasing and calibration-versus-averaging notes; corrected stale 10-bit sweep status; linked later filtering separately. | Independent voltage/current checks on the original setup, personal feedback/help entries in Reflection 1. Task 5 filtering was outside the instructor-requested scope ending at Task 4. |
| 2 · Buses | Consolidated existing group notes and SPI/pin material into an interface comparison; added sourced repeated-START and clock-stretching notes; corrected the obsolete awaiting-presentations wording. | Divider output measurement, exact SPI kit device/settings and pitch contribution, individual hands-on I²C role, class-wide analyzer choice, and personal feedback entries. Optional address-conflict/bit-capture exercises are not mandatory omissions. |
| 3 · Characterization | Added reproducible all-six-point LDR fits, same-data linear comparison and residual plots; completed DS18B20 parameter notes; added two primary-source characterization examples, a review trail and conditional uncertainty/bandwidth calculations. | Revised ≥20-readings-per-resolution sweep; LDR ADC/meter comparison and one-step comparison; fresh matched-condition LDR validation; controlled hysteresis/settling/returns; reference-dependent temperature work; full uncertainty and actual peer exchange. See the detailed checklist. |
| 4 · Liquid measurement | Added Reflection 4 and navigation, explicitly based on Zhenning's report. The student confirmed absence and no practical participation. | Haocheng's practical competency is not established by a teammate's experiment. Any practical make-up should be agreed with the instructor. Synchronous IMU/level and industrial field validation remain proposals, not missing completed lab evidence. |
| 5 · LEDs | Organized three projects and evidence; added theory notes, Reflection 5 draft, and the measured-versus-calculated power table; corrected stale pending text. | Illuminated-strip photograph/video, actual pod discussion/agreed-learning/share, optional extension if chosen, and total-system/Wi-Fi testing if required. Only eight pixels available: larger-strip rows remain calculations. |

[Module 3 detailed checklist](Module03/completion-checklist.md) · [Reflection index](Reflections/README.md) · [Observed hardware inventory](Hardware/README.md)

## Suggested next actions

1. **Quick evidence:** add an actual photograph/video of the eight lit pixels and, if available, the meter setup/display. The 0.09 A is strip-only at luminance 80/255; do not call it full-brightness or total USB current.
2. **Personal information:** finish Reflections 1–3 with actual interactions/help/individual checks. Reflections 4 and 5 are drafted but should be read before being presented as the student's final words. No pod consensus or personal experiences can be generated from numeric data alone.
3. **Short bench work when equipment is available:** complete the Module 2 divider-output reading and Module 3 controlled resolution sweep/fresh LDR validation. Check the current instructor scope first; the divider had been postponed when class moved on.
4. **Reference/coordination work:** arrange a suitable thermometer, class unit comparison and genuine peer review. Do not retroactively label an unvalidated probe as calibrated.
5. **Sharing:** the reviewed code, evidence and documentation are packaged in this repository. Posting the repository link or selected artifact to a class channel remains a separate action; no Discord post is claimed.

## Scope and measurement cautions

- Later notes fill written explanations; they do not demonstrate that a concept was understood before the session.
- Module 3 Task 2.3 and 2.8 are optional, Task 6 is an extension. Full combined uncertainty remains a learning-goal gap even though the extension experiment is optional.
- The all-six-point LDR fits use every original point: residuals are in-sample. Task 3b uses a separate two-point procedure with an existing held-out point; a fresh validation is still missing.
- The initial failed current measurements and reported short circuit in Module 5 remain documented. Subsequent working LEDs do not identify the fault or prove absence of latent damage.
- The UT131C model is confirmed for Module 5 strip current only; it is not assumed to be the Module 3 ADC reference meter or RGB-voltage meter.
- Firmware, original measured datasets and raw evidence were preserved. The new LDR fit outputs are derived artifacts with a reproduction script.

## Publication state

This revision packages Module05, the cross-module documentation supplements, Reflections 4–5 and the presentation updates for repository publication at the student's request. The review started from main at 58c0895. Course-channel sharing remains unrecorded.

[Portfolio home](README.md)
