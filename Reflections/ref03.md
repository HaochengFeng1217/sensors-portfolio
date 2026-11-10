# Reflection 3 — Sensor characterization and calibration

> English draft for Haocheng Feng to review. This is the Module 3 portion of the Days 1–3 teaching-block reflection. [Reflection prompts](TEMPLATE.md) · [Module 3 evidence](../Module03/README.md)

## Take-away

I would reserve a fresh point to check any calibration. At the 1.207 V reference point, the ADC residual dropped from +21.72 mV to +3.05 mV after the two-point correction. This gives me a check on the correction at one point. I would still need a meter specification and other error contributions to state a numerical uncertainty. [ADC calibration and validation](../Module03/adc-calibration/README.md)

## What was good?

The DS18B20 traces made the difference between the water and air response visible for this probe and setup. The potentiometer step record also made the cost of smoothing visible: on Run 4, the moving average and median crossed the midpoint 20 ms after the raw signal and the exponential average crossed it 40 ms after. I would repeat the step under controlled conditions before choosing a filter for a time-critical decision. [Thermal response](../Module03/ds18b20/README.md) · [Step response](../Module03/noise-and-filtering/potentiometer-step/README.md)

## What was difficult?

Neither decision switched in the first LDR threshold run because the trace did not reach the required trigger levels. New thresholds were set before Run 2. Replaying the same new trace with both rules gave five single-threshold switches and one hysteresis switch. A return through the reset threshold is still needed to show the full cycle. [LDR decision hysteresis](../Module03/noise-and-filtering/ldr-hysteresis/README.md)

## Exploration and show stoppers

Changing ambient light made the later LDR repeats unsuitable for pooling with the original distance series. Next time I would control the light geometry and reserve a fresh LDR validation point under matching conditions. The DS18B20 correction also still needs a suitable reference thermometer. [LDR characterization](../Module03/ldr-characterization/README.md) · [Completion checklist](../Module03/completion-checklist.md)

## Interaction with peers and instructors

**To confirm with Haocheng:** Record any discussion or feedback from the instructor or neighbouring pod, with the question or artefact discussed. The peer check and agreed-learning note remain unrecorded. [Study log](../Module03/README.md#remaining-study-log-work)

## How did you verify AI suggestions?

The study log records LLM help with procedures, calculations, plots and documentation. It also records checking numerical results against saved data or identified operator readings. For Task 5.5, independent replay reproduced both decision columns from the saved raw samples and fixed thresholds. **To confirm with Haocheng:** Specify which checks you performed yourself and add an example of a suggestion you corrected, if applicable. [Scope and assistance](../Module03/README.md#scope-and-assistance) · [Run 2 verification](../Module03/noise-and-filtering/ldr-hysteresis/README.md#run-2--corrected-preselected-thresholds-and-observed-chatter-reduction)

## Help and extra work

**To confirm with Haocheng:** Record any human assistance, peer checks or sharing of results that took place. Identify your own contribution to any shared work.

## Learning-goal self-assessment

The ADC third-point check and the noise/latency comparisons are supported by saved evidence. The characterization has experimental limits, and a numerical uncertainty budget remains to be completed. [Learning Goals](../Module03/README.md#learning-goals)
