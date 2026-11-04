import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

failure_times = np.array([8, 20, 34, 46, 63, 86, 111, 141, 186, 266])

n = len(failure_times)

times = np.insert(failure_times, 0, 0)

dt = np.diff(times)

i = np.arange(1, n + 1)

F = i / n

R = 1 - F

R_previous = np.insert(R[:-1], 0, 1)

f = (1 / n) / dt

z = (1 / n) / (R_previous * dt)

midpoints = (times[:-1] + times[1:]) / 2

df = pd.DataFrame(
    {
        "Failure Time": failure_times,
        "Interval": dt,
        "CDF F(t)": F,
        "Reliability R(t)": R,
        "Density f(t)": f,
        "Hazard z(t)": z,
    }
)

print("\nFailure Data Analysis:\n")
print(df.to_string(index=False))

fig, axes = plt.subplots(2, 2, figsize=(12, 9))

axes[0, 0].plot(midpoints, z, marker="o")
axes[0, 0].set_title("Hazard Function z(t)")
axes[0, 0].set_xlabel("Operating Time (hours)")
axes[0, 0].set_ylabel("Hazard Rate")
axes[0, 0].grid(True)

axes[0, 1].plot(midpoints, f, marker="s")
axes[0, 1].set_title("Density Function f(t)")
axes[0, 1].set_xlabel("Operating Time (hours)")
axes[0, 1].set_ylabel("Probability Density")
axes[0, 1].grid(True)

axes[1, 0].step(failure_times, F, where="post", marker="o")
axes[1, 0].set_title("Cumulative Distribution F(t)")
axes[1, 0].set_xlabel("Operating Time (hours)")
axes[1, 0].set_ylabel("F(t)")
axes[1, 0].set_ylim(0, 1.05)
axes[1, 0].grid(True)

axes[1, 1].step(failure_times, R, where="post", marker="s")
axes[1, 1].set_title("Reliability Function R(t)")
axes[1, 1].set_xlabel("Operating Time (hours)")
axes[1, 1].set_ylabel("R(t)")
axes[1, 1].set_ylim(0, 1.05)
axes[1, 1].grid(True)

plt.tight_layout()
plt.show()
