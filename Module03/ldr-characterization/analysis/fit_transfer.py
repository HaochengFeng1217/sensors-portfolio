"""Reproduce Task 1's six-point fits; no device access or new measurements.

Run: python fit_transfer.py (requires numpy and matplotlib).
Source: accepted 2026-11-04 readings in ../README.md, transcribed below.
The changed-ambient-light repeatability set is deliberately excluded.
"""
from pathlib import Path
import csv
import json
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
OUT = HERE.parent / "evidence"
OUT.mkdir(exist_ok=True)
DISTANCE_CM = np.array([5., 10., 15., 20., 25., 30.])
LDR_VOLTAGE_V = np.array([0.13, 0.20, 0.36, 0.51, 0.62, 0.78])
SUPPLY_V = 3.35
FIXED_KOHM = 10.0  # nominal, not independently measured
relative_light = (5.0 / DISTANCE_CM) ** 2
resistance = FIXED_KOHM * LDR_VOLTAGE_V / (SUPPLY_V - LDR_VOLTAGE_V)
log_slope, log_intercept = np.polyfit(np.log(relative_light), np.log(resistance), 1)
amplitude = np.exp(log_intercept)
power_prediction = amplitude * relative_light ** log_slope
linear_slope, linear_intercept = np.polyfit(relative_light, resistance, 1)
linear_prediction = linear_slope * relative_light + linear_intercept
power_residual = power_prediction - resistance
linear_residual = linear_prediction - resistance
power_rmse = np.sqrt(np.mean(power_residual ** 2))
linear_rmse = np.sqrt(np.mean(linear_residual ** 2))
log_residual = np.log(power_prediction) - np.log(resistance)
log_r2 = 1 - np.sum(log_residual ** 2) / np.sum((np.log(resistance)-np.mean(np.log(resistance))) ** 2)
summary = {
    "source": "Accepted 2026-11-04 Task 1 readings, transcribed from ../README.md",
    "supply_V": SUPPLY_V, "nominal_fixed_resistor_kohm": FIXED_KOHM,
    "relative_light_model": "(5 cm / distance_cm)^2; not measured lux",
    "sample_count": 6, "all_points_used_for_fit": True,
    "power_fit": {"objective": "OLS in natural-log space", "A_kohm": float(amplitude),
                  "gamma": float(-log_slope), "log_intercept": float(log_intercept),
                  "R2_log_space": float(log_r2), "RMSE_kohm": float(power_rmse)},
    "linear_fit": {"objective": "OLS in resistance space", "slope_kohm": float(linear_slope),
                   "intercept_kohm": float(linear_intercept), "RMSE_kohm": float(linear_rmse)},
    "residual_definition": "predicted resistance minus measured-voltage-derived resistance",
    "limits": "In-sample fit statistics, not independent validation or a complete uncertainty budget."
}
(OUT / "Task1-LDR-Six-Point-Fit.json").write_text(json.dumps(summary, indent=2) + "\n")
with (OUT / "Task1-LDR-Six-Point-Fit.csv").open("w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["distance_cm", "measured_LDR_voltage_V", "derived_node_voltage_V",
                     "relative_light_estimate", "derived_resistance_kohm", "power_prediction_kohm",
                     "power_residual_kohm", "linear_prediction_kohm", "linear_residual_kohm"])
    writer.writerows(zip(DISTANCE_CM, LDR_VOLTAGE_V, SUPPLY_V-LDR_VOLTAGE_V, relative_light,
                         resistance, power_prediction, power_residual, linear_prediction, linear_residual))
plt.rcParams.update({"font.size": 11, "axes.spines.top": False, "axes.spines.right": False})
light_grid = np.geomspace(relative_light.min(), relative_light.max(), 400)
fig, axes = plt.subplots(1, 2, figsize=(12, 4.7), constrained_layout=True)
for ax in axes:
    ax.scatter(relative_light, resistance, color="#162f4b", zorder=3, label="Six voltage-derived readings")
    ax.plot(light_grid, amplitude*light_grid**log_slope, color="#126b9a", label="Power law: log-space OLS")
    ax.plot(light_grid, linear_slope*light_grid+linear_intercept, color="#c65a2e", linestyle="--", label="Linear: resistance-space OLS")
    ax.set_xlabel("Estimated relative illuminance (1 at 5 cm)")
    ax.set_ylabel("LDR resistance (kΩ)")
    ax.grid(alpha=.2)
axes[0].set_title("Original resistance and light coordinates")
axes[1].set_xscale("log"); axes[1].set_yscale("log")
axes[1].set_title("Same models on logarithmic axes")
axes[0].legend(fontsize=9)
fig.suptitle("Task 1: all six points used in each fit; relative light is inferred")
fig.savefig(OUT / "Task1-LDR-Six-Point-Fits.png", dpi=220)
plt.close(fig)
fig, ax = plt.subplots(figsize=(9, 4.8), constrained_layout=True)
ax.axhline(0, color="#6f7479", linewidth=1)
ax.plot(DISTANCE_CM, power_residual, "o-", color="#126b9a", label=f"Power law: RMSE {power_rmse:.3f} kΩ")
ax.plot(DISTANCE_CM, linear_residual, "s--", color="#c65a2e", label=f"Linear: RMSE {linear_rmse:.3f} kΩ")
ax.set(xlabel="Recorded source distance (cm)", ylabel="Prediction minus derived resistance (kΩ)",
       title="Task 1: in-sample residuals in the same resistance units")
ax.set_xticks(DISTANCE_CM); ax.grid(alpha=.2); ax.legend()
fig.savefig(OUT / "Task1-LDR-Six-Point-Residuals.png", dpi=220)
plt.close(fig)
print(json.dumps(summary, indent=2))
