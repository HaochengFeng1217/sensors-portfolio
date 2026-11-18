# Eight-pixel strip: power budget and measurements

Date: 18 November 2026. Meter: UNI-T UT131C.

Only an eight-pixel strip was available. The 30-, 60- and 144-pixel rows are calculated budgets, not hardware measurements. The full-white estimates use the course's conservative 60 mA per RGB pixel before brightness limiting, and exclude ESP32 consumption.

| Pixel count | Estimated full-white strip current at 255/255 (A) | Estimated power at 5 V (W) | Measured strip current |
| --- | --- | --- | --- |
| 8 | 0.48 | 2.4 | 0.09 A, white at luminance 80/255 |
| 30 | 1.80 | 9.0 | Not measured; hardware unavailable |
| 60 | 3.60 | 18.0 | Not measured; hardware unavailable |
| 144 | 8.64 | 43.2 | Not measured; hardware unavailable |

The operator used a UNI-T UT131C in its 10 A DC range and confirmed the meter was in series between ESP32 VIN and the strip's 4–7VDC input. These readings cover the strip branch only, excluding ESP32 consumption. The connection and display were reported by the operator, without a measurement photograph.

| Eight-pixel output | Luminance setting | Reported indication (A) |
| --- | --- | --- |
| All pixels white (255, 255, 255) | 80/255 | 0.09 |
| All pixels off after clear | 80/255 | 0.00 |

The off-state indication is below the current range's display resolution, not proof of zero idle current. Preserve the reported 0.09 A precision; finer precision and instrument uncertainty were not established. The estimated strip power at nominal 5 V and the white-load indication is approximately 0.45 W. An earlier voltage check read 5.17 V, but it was not simultaneous with the current reading.

Scaling the conservative 0.48 A full-brightness estimate by 80/255 gives about 0.151 A. The measured 0.09 A was obtained at this reduced luminance, so it must not be presented as a measurement at full brightness. Device revision, actual pixel channel currents and idle electronics affect agreement with the generic estimate.

The USB source capacity and board power path must include the ESP32 load as well as the strip. The ESP32's current was not measured. Larger strips require a suitably rated separate 5 V supply and common ground; the calculated full-brightness loads exceed an ordinary USB 2.0 power budget.


Source for the conservative 60 mA estimate: [Module 5 workbook](https://github.com/iotempire/iotempire-teaching/blob/43ee9338bdec8c83d568d07a27174865cb453552/full-classes/hsbi-sensors-actuators-10d/modules/05-leds-and-light-output.md).

[Experiment report](README.md) · [Module index](../README.md)
