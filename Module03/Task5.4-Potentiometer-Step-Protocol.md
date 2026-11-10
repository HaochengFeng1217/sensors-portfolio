# Task 5.4 — Potentiometer Step Protocol

Date: 2026-11-10

Status: acquisition program prepared; no step measurement recorded yet.

## Setup

Retain potentiometer wiring: outer terminals to 3V3 and GND; wiper to GPIO34. ADC settings: 12 bits, 11 dB attenuation. Choose two operating levels away from both rails, for example approximately 1.0 and 2.0 V when a meter is available. These are targets, not measured voltages.

## Acquisition

The sketch waits for command `S`; uploading alone does not start acquisition. It stores 2000 raw samples at a target interval of 10 ms, covering approximately 20 seconds. Hold the initial position still. At about five seconds, the Serial Monitor prints `TURN NOW`. Turn once quickly to a clearly different level, then hold until `DONE`. Do not move the wiring. The cue marks a requested action, not the measured time of the electrical step.

After capture, the sketch prints raw values, timestamps and three causal filtered replays: trailing moving average (5), trailing median (5), and EMA (alpha = 0.2, initialized to the first raw sample). The first four window outputs are `nan`. No per-sample printing occurs during acquisition. A single short cue is printed after sample 501; check the actual timestamps for any timing disturbance. Processing and serial printing after capture do not measure processor execution latency.

`P` reprints the stored dataset. `S` begins a fresh capture and overwrites RAM, so export before repeating.

## Planned analysis

Check sequential sample indices, actual intervals, input clipping and stable plateaus. Independently recompute the filters. Estimate pre-step and post-step levels from stable segments. Measure each filter's 50% crossing delay relative to the raw 50% crossing, stating the crossing rule and time resolution. If noise causes repeated crossings, report the ambiguity rather than claiming sub-sample precision. Inspect 10–90% transition duration to document the finite manual turn. A slow manual ramp is not an ideal instantaneous step and limits interpretation of filter latency.

The five-point moving average has an analytical group delay of two samples (about 20 ms at 100 Hz). This is a prediction, not a measured result. Report measured crossing delays separately. No latency result is claimed before capture and analysis.

[Acquisition sketch](./task5-step-acquisition/task5-step-acquisition.ino)
