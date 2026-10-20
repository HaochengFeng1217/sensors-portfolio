# Wokwi: potentiometer to LED

Run date: 2026-10-21

Project: [HSBI Module 0 - Potentiometer and LED](https://wokwi.com/projects/478439382770685953)

An ESP32 reads a potentiometer on GPIO34 and maps the reading to PWM brightness
on GPIO2. A 330 ohm resistor is in series with the red LED.

## Files

- [sketch.ino](sketch.ino): baseline program, with `ADC_BITS = 12` and `LED_LEVELS = 256`.
- [diagram.json](diagram.json): the complete circuit.
- [Captured serial output](serial-output.md): readings from the three runs.

## Wiring

| Connection | Destination |
|---|---|
| Potentiometer VCC | ESP32 3V3 |
| Potentiometer GND | ESP32 GND.1 |
| Potentiometer SIG | ESP32 GPIO34 |
| ESP32 GPIO2 | 330 ohm resistor, then LED A |
| LED C | ESP32 GND.2 |

## Reproduce the three runs

Open the saved project and click Run. Turn the potentiometer, or focus its value
control and change the setting. The control settings below use the simulator's
integer scale of 0-1023, not volts.

1. Baseline: `ADC_BITS = 12`, `LED_LEVELS = 256`.
2. Stop the simulation, change `ADC_BITS` to `10`, then run again.
3. Keep `ADC_BITS = 10`, change `LED_LEVELS` to `4`, then run again.

The saved project and source file are left at the baseline settings.
The program prints a line only when the ADC reading changes.

## Recorded results: ADC comparison

| Potentiometer control | Raw, 12-bit | Raw, 10-bit | PWM, 12-bit run | PWM, 10-bit run |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 |
| 256 | 1025 | 256 | 64 | 64 |
| 512 | 2050 | 512 | 128 | 128 |
| 513 | 2054 | 513 | 128 | 128 |
| 768 | 3074 | 768 | 192 | 192 |
| 1023 | 4095 | 1023 | 255 | 255 |

The observed endpoints were 0 and 4095 at 12 bits, and 0 and 1023 at 10 bits.
The theoretical code counts are 4096 and 1024 respectively. These are representable
code counts; the table does not claim that every possible code was sampled.

Changing the control from 512 to 513 produced 2050 to 2054 at 12 bits, but 512 to
513 at 10 bits. The simulator's input control has its own granularity. The LED PWM
value remained 128 for these neighbouring settings in both runs because the output
mapping has 256 brightness levels.

Reducing the ADC resolution makes the nominal ADC step four times coarser for the
same input span. It does not establish improved accuracy. This simulation checks
program behaviour; it does not measure real ESP32 ADC error or calibrate a sensor.

## Recorded results: deliberately coarse output

ADC resolution was 10 bits and the brightness mapping had four levels.

| Potentiometer control | Observed ADC raw | Observed PWM brightness |
|---|---|---|
| 0 | 0 | 0 |
| 255 | 255 | 0 |
| 256 | 256 | 85 |
| 511 | 511 | 85 |
| 512 | 512 | 170 |
| 767 | 767 | 170 |
| 768 | 768 | 255 |
| 1023 | 1023 | 255 |

The four PWM values were 0, 85, 170, and 255. Crossing 255 to 256 changed the output
from 0 to 85; crossing 511 to 512 changed it from 85 to 170; crossing 767 to 768
changed it from 170 to 255. The LED stayed at one level between thresholds and
changed abruptly at a boundary. This is deliberate output quantization.

## Screenshots

- [12-bit ADC and circuit](../images/wokwi-adc12.png)
- [10-bit ADC and circuit](../images/wokwi-adc10.png)
- [Four-level output and threshold crossings](../images/wokwi-coarse4.png)

## References

- [Wokwi potentiometer pins and value control](https://docs.wokwi.com/parts/wokwi-potentiometer)
- [Wokwi LED pins](https://docs.wokwi.com/parts/wokwi-led)
- [Espressif ADC API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html)
- [Espressif PWM / analogWrite API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html#analogwrite)

[Back to Module 0](../README.md)
