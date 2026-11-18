# Measurement vocabulary and sampling notes

Added: 18 November 2026, during the portfolio review. These are explanatory study notes based on the existing experiments, not additional Module 1 measurements.

## Measurement vocabulary

| Term | Meaning in these experiments |
| --- | --- |
| True value / reference value | The true value is generally unknown. A suitable independent meter or reference provides a comparison value, with its own uncertainty. |
| Error | Measured value minus the reference value. The Module 3 ADC example reduced a signed residual at one validation point; that does not establish zero error elsewhere. |
| Uncertainty | A quantified account of plausible values given the available information and assumptions. It is not interchangeable with one error or with repeatability SD. |
| Accuracy | Closeness to the true value; it cannot be inferred just from a stable display or many decimal places. |
| Precision / repeatability | Agreement among repeats under stated conditions. The stationary ADC excerpts and LDR repeats address short-term spread. |
| Resolution | The smallest distinguishable output increment. For an ideal n-bit converter, the nominal bin width is input span divided by 2^n. |
| Range | The specified input interval, or an explicitly labelled observed minimum-to-maximum interval. Observed code endpoints do not calibrate the input-voltage span. |
| Sensitivity | Change of output per change of input, such as ADC codes per volt. The LDR chain's sensitivity can change with the operating point. |

At an assumed 3.3 V span, ideal 12-bit and 10-bit bin widths are about 0.806 mV and 3.223 mV. The fourfold ratio follows from code count; neither value is an independent characterization of this ESP32's usable analog range or accuracy. The ideal-bin convention uses 2^n bins; an endpoint interpolation formula using 2^n−1 is a different convention.

Averaging can reduce some random variation when samples and conditions permit. It does not remove a systematic offset. Calibration estimates a correction using references; it must be checked at a point not used for fitting. [Later fresh ADC validation](../Module03/adc-calibration/README.md)

Terminology reference: [JCGM International Vocabulary of Metrology](https://jcgm.bipm.org/vim/en/), particularly accuracy 2.13, precision 2.15 and uncertainty 2.26.

## Sampling and aliasing

For a signal band-limited below B Hz, ideal reconstruction requires a sampling frequency greater than 2B. A practical acquisition also needs margin and filtering before sampling; digital smoothing cannot remove an alias that has already entered the sampled band.

As a purely theoretical example, cosine signals at 40 Hz and 60 Hz give identical sample values at 100 samples/s: cos(2π60n/100) = cos(2π40n/100) for integer n. A slowly refreshed Serial Plotter therefore cannot establish the absence of fast button bounce. The existing trace's displayed sample interval must be compared with the event duration. This example was not measured on the board.

Quantization maps each sampled amplitude to a discrete code. More bits improve the ideal reporting increment but cannot fix an unsuitable sampling rate, clipping, an incorrect reference or analog noise. [ADC evidence](potentiometer-adc/README.md) · [Plot timing](serial-plotter/README.md#loop-timing)

## Later cross-module evidence

Module 1 Task 5 was outside the instructor-requested scope ending at Task 4 and remains unperformed in Module 1. Later [Module 3 filtering and latency experiments](../Module03/noise-and-filtering/README.md) provide separate evidence for moving-average, median and exponential filters. They do not retroactively become Module 1 measurements.

[Module 1](README.md)
