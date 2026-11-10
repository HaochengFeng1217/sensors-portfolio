# Reflection 2 — Buses and I²C

> English draft for Haocheng Feng to review. This is the Module 2 portion of the Days 1–3 teaching-block reflection. [Reflection prompts](TEMPLATE.md) · [Module 2 evidence](../Module02/README.md)

## Take-away

The UART loopback helped me connect the configured baud rate and wiring to a checkable result. I²C adds a different question: which address acknowledged on the shared bus? Zhenning Yu's scan and PulseView capture are examples I can use to explain the difference between detecting a device and seeing an unacknowledged transaction. [UART log](../Module02/uart-loopback/evidence/observed-loopback.txt) · [Zhenning Yu's experiments](../Module02/README.md#teammate-contributions)

## What was good?

The ESP32 returned the same string that it transmitted in the saved UART loopback test. The SPI profile gave me a place to organize questions about chip select, clock mode and device-specific limits. The SPI presentation and physical kit example are still pending in the record. [UART test](../Module02/pins-and-dividers.md#observed-uart-result--28-october-2026) · [SPI profile](../Module02/bus-spi.md)

## What was difficult?

The photographed divider input was 3.316 V. The predicted output uses the nominal resistor values, and the output node still needs its own meter measurement. I would check the wiring and record the actual output before drawing a conclusion about the divider. [Divider notes and meter photo](../Module02/pins-and-dividers.md#input-voltage-observation)

## Exploration and show stoppers

Zhenning's SE95 direct register conversion and library read both reported 26.938 °C. His shared-bus test also shows two devices working on the same SDA and SCL lines at distinct addresses. I would use those records to plan an independent scan and a separate address-conflict exercise. [Zhenning Yu's Tasks 6 and 7](../Module02/README.md#teammate-contributions)

## Interaction with peers and instructors

The task notes record a class instruction to move on to Task 2 before the divider output was measured. **To confirm with Haocheng:** Add any individual instructor feedback or peer discussion, including what you personally contributed. [Task notes](../Module02/pins-and-dividers.md)

## How did you verify AI suggestions?

The SPI research notes record checks against technical sources. The UART serial log is the direct bench check for the transmitted and received text at the tested settings. **To confirm with Haocheng:** Identify the specific AI suggestion you checked, the source or test you used and any correction you made. [SPI research notes](../Module02/bus-spi-research.md) · [UART log](../Module02/uart-loopback/evidence/observed-loopback.txt)

## Help and extra work

Zhenning Yu is credited for Tasks 5, 6, 7 and 9. **To confirm with Haocheng:** Record any additional help given or received and any part of the group work you personally performed. [Contribution notes](../Module02/README.md#teammate-contributions)

## Learning-goal self-assessment

The UART and SPI records support parts of the interface comparison. The I²C scan, register read, shared-bus and logic-analyzer demonstrations are available as teammate evidence. My own hands-on I²C work, address-conflict resolution and a class-wide tool decision remain unverified. [Learning Goals](../Module02/README.md#learning-goals)
