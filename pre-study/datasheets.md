# Datasheet reading notes

Status: **Manufacturer specifications recorded on 2026-10-21.**

These are datasheet findings. Hardware performance has not been measured.
Page numbers below refer to the printed pages in the linked revisions.

## VL53L0X: optical distance sensor

Source: STMicroelectronics, [VL53L0X datasheet](https://www.st.com/resource/en/datasheet/vl53l0x.pdf),
**DS11555, Rev. 6, June 2024** (p. 1).

| Field | Finding and source location |
|---|---|
| Physical principle | Optical Time-of-Flight: VCSEL emission and a SPAD receiver array (p. 1; Section 3.6.2, p. 11). |
| Bare-module supply | AVDD: **2.6-3.5 V**, nominal **2.8 V**. I/O mode has separate requirements (Table 8, p. 19). |
| Interface | I²C, up to **400 kHz** (Table 2, p. 3). |
| Address | Default **0x29, 7-bit**. The datasheet's **0x52/0x53** are the write/read address bytes including R/W (Section 4, Figure 14, p. 15). |
| Address configuration | Programmable I²C address (p. 1). Check the API procedure before using multiple identical devices. |
| Range | Advertised up to **2 m** (p. 1); achievable distance depends on reflectance, infrared background, and profile (Table 12, p. 23). |
| Resolution | A fixed distance-output step is not separately specified in the reviewed datasheet sections; check the API output format before assuming one. |
| Accuracy | Condition-dependent standard-deviation figures; see the selected example in [Question 3](README.md#3-datasheet-question) (Table 13, p. 23). |
| Timing | Default sequence budget **33 ms** (Section 3.10, p. 14); configurable profiles trade time against performance (Table 14, p. 24). |
| Temperature | Operating range **-20 to +70°C** (Table 8, p. 19); calibration depends on temperature (Section 3.3.1, p. 9). |
| Limitations | Check cover-glass crosstalk and calibration (Section 3.3, pp. 8-9), and target/background conditions (Section 6.2, p. 23). Breakout-board input limits require that board's documentation. |

## MPR121: capacitive touch controller

Source: NXP-hosted Freescale Semiconductor,
[MPR121 datasheet](https://www.nxp.com/docs/en/data-sheet/MPR121.pdf),
**Rev. 4, February 2013** (p. 1).

| Field | Finding and source location |
|---|---|
| Physical principle | Constant-current charging; electrode voltage depends on capacitance. Touch detection compares filtered data with a tracked baseline (Section 3, p. 4). |
| Supply configuration | **1.71-2.75 V** with regulator bypassed, or **2.0-3.6 V** using the internal regulator (Figures 1-2 and Section 3, pp. 3-4). |
| Interface | I²C with IRQ; maximum clock **400 kHz** (Table 7, p. 10; Section 6.1, p. 21). |
| Address/configuration | **7-bit:** ADDR tied to VSS → **0x5A**; VDD → **0x5B**; SDA → **0x5C**; SCL → **0x5D** (Table 10, p. 21). |
| Range | **10 pF to over 2000 pF** (Section 3, p. 4); proximity distance depends on electrode/application design. |
| Resolution | Internal **10-bit ADC**; capacitance resolution up to **0.01 pF**, depending on charging configuration (Section 3, p. 4). |
| Accuracy | No universal absolute ±capacitance or ±distance specification is given. Resolution is a different quantity; touch detection also depends on baseline, thresholds, and noise (Sections 3 and 5.6, pp. 4, 13). |
| Timing | ESI configurable **1-128 ms**, default **16 ms**. Filtering, scanning, and debounce affect actual response (Table 8 and Section 5.8, pp. 14-15; Section 5.7, p. 13). |
| Temperature | Operating **-40 to +85°C** (p. 1); no numerical capacitance temperature coefficient identified. |
| Limitations | Respect the VREG supply configuration (pp. 3-4); tune baseline, thresholds, and filters for the electrode layout and environment (Sections 3, 5.6-5.8). |

## Address convention to remember

For a 7-bit address `a`, the transmitted address byte is `(a << 1) | R/W`.
Thus VL53L0X `0x29` becomes `0x52` for writing and `0x53` for reading.
Pass the form expected by the particular driver/API.

Before wiring hardware, check the exact breakout board's power input, logic levels,
and pull-ups against the manufacturer's requirements above.

[Back to Module 0](README.md)
