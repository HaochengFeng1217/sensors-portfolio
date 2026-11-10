# Reflection 1 — Foundations and measurement

> English draft for Haocheng Feng to review. This is the Module 1 portion of the Days 1–3 teaching-block reflection. [Reflection prompts](TEMPLATE.md) · [Module 1 evidence](../Module01/README.md)

## Take-away

My main takeaway is to trace a reading back through the whole chain. With the LDR, light changes the sensor's resistance, the divider converts that change to a voltage and the ESP32 reports an ADC code. A repeatable code is evidence of stability under those conditions. An independent voltage reference would let me check accuracy. [LDR divider and repeatability](../Module01/ldr-divider/README.md)

## What was good?

The potentiometer captures reached both code endpoints at 12 and 10 bits, and the fixed-position excerpts gave me a way to compare spread. The button experiment also made the effect of software debouncing visible by logging raw and accepted transitions separately. The cumulative counts leave the accuracy of an individual press count open. [ADC comparison](../Module01/potentiometer-adc/README.md) · [Button counter log](../Module01/button-debounce/observed-serial.csv)

## What was difficult?

The board's power indicator went out when the potentiometer was connected and returned when the external wiring was removed. Clearer photographs supported the explanation that the potentiometer terminals shared one connected breadboard group. The indicator stayed on after the terminals were separated. I would check continuity with the circuit unpowered on a repeat run to verify the suspected short. [Wiring troubleshooting](../Module01/potentiometer-adc/README.md#wiring-troubleshooting-2026-10-25)

## Exploration and show stoppers

The first attempts at covering the LDR gave higher readings than the shade setup. Blocking light from the front and sides changed the result, and restoring room light brought readings back near the initial range. Next time I would fix the geometry and record an independent divider voltage alongside the raw code. [Covering trials and repeat measurements](../Module01/ldr-divider/README.md#initial-cover-attempt-and-method-correction)

## Interaction with peers and instructors

**To confirm with Haocheng:** Add any specific discussion about the wiring, experiment scope or results and explain how it affected the work.

## How did you verify AI suggestions?

The wiring record shows how clearer photographs corrected an earlier misreading of the board pins, and the power indicator provided a separate check after rewiring. For the ADC comparison, the theoretical steps can be recalculated from the assumed 3.3 V span and checked against the observed code endpoints. The voltage estimates still need a meter comparison. **To confirm with Haocheng:** Identify which suggestions came from AI and which checks you personally performed. [Wiring and ADC evidence](../Module01/potentiometer-adc/README.md)

## Help and extra work

**To confirm with Haocheng:** Record any assistance received or given and any additional work you personally carried out.

## Learning-goal self-assessment

The LDR chain, button circuit and serial tools are supported by the lab records. I can use the ADC results to explain quantization. Independent voltage checks, an explicit sampling-theorem explanation and the Module 1 filter exercise remain gaps in the evidence. [Learning Goals](../Module01/README.md#learning-goals)
