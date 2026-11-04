import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

N0 = 172
intervals = [
    "0 – 1000",
    "1001 – 2000",
    "2001 – 3000",
    "3001 – 4000",
    "4001 – 5000",
    "5001 – 6000",
]
t_start = np.array([0, 1000, 2000, 3000, 4000, 5000])
t_end = np.array([1000, 2000, 3000, 4000, 5000, 6000])
dt = 1000
failures = np.array([59, 24, 29, 30, 17, 13])

N_start = np.zeros(len(failures), dtype=int)
N_start[0] = N0
for i in range(1, len(failures)):
    N_start[i] = N_start[i - 1] - failures[i - 1]
N_end = N_start - failures

cum_failures = np.cumsum(failures)

time_points = np.insert(t_end, 0, 0)
R_t = np.insert(N_end / N0, 0, 1.0)
F_t = np.insert(cum_failures / N0, 0, 0.0)

f_t = failures / (N0 * dt)
z_t_start = failures / (N_start * dt)
z_t_avg = failures / (((N_start + N_end) / 2.0) * dt)

df = pd.DataFrame(
    {
        "Interval (h)": intervals,
        "Failures (ni)": failures,
        "N_start": N_start,
        "N_end": N_end,
        "R(t_end)": R_t[1:],
        "F(t_end)": F_t[1:],
        "f(t) (1/h)": f_t,
        "z(t) [start] (1/h)": z_t_start,
        "z(t) [avg] (1/h)": z_t_avg,
    }
)

print("=" * 85)
print("COMPUTED RELIABILITY METRICS TABLE")
print("=" * 85)
print(df.to_string(index=False))
print("=" * 85)

fig, axs = plt.subplots(2, 2, figsize=(12, 10))

t_steps = np.repeat(time_points, 2)[1:-1]
z_steps = np.repeat(z_t_start * 1e4, 2)
f_steps = np.repeat(f_t * 1e4, 2)

axs[0, 0].plot(
    t_steps, z_steps, color="crimson", lw=2.5, label="z(t) (Start survivors)"
)
axs[0, 0].set_title("(a) Hazard Function $z(t)$", fontsize=12, fontweight="bold")
axs[0, 0].set_xlabel("Time $t$ (hours)")
axs[0, 0].set_ylabel("Hazard Rate ($\times 10^{-4} / h$)")
axs[0, 0].grid(True, linestyle="--", alpha=0.7)
axs[0, 0].legend()

axs[0, 1].plot(t_steps, f_steps, color="darkorange", lw=2.5, label="f(t)")
axs[0, 1].bar(
    t_start + 500,
    f_t * 1e4,
    width=1000,
    alpha=0.25,
    color="orange",
    edgecolor="darkorange",
)
axs[0, 1].set_title(
    "(b) Failure Density Function $f(t)$", fontsize=12, fontweight="bold"
)
axs[0, 1].set_xlabel("Time $t$ (hours)")
axs[0, 1].set_ylabel("Density ($\times 10^{-4} / h$)")
axs[0, 1].grid(True, linestyle="--", alpha=0.7)
axs[0, 1].legend()

axs[1, 0].plot(time_points, F_t, marker="o", color="forestgreen", lw=2.5, label="F(t)")
axs[1, 0].set_title(
    "(c) Cumulative Distribution Function $F(t)$", fontsize=12, fontweight="bold"
)
axs[1, 0].set_xlabel("Time $t$ (hours)")
axs[1, 0].set_ylabel("Cumulative Failure Probability $F(t)$")
axs[1, 0].set_ylim(-0.05, 1.05)
axs[1, 0].grid(True, linestyle="--", alpha=0.7)
axs[1, 0].legend()

axs[1, 1].plot(time_points, R_t, marker="s", color="royalblue", lw=2.5, label="R(t)")
axs[1, 1].set_title("(d) Reliability Function $R(t)$", fontsize=12, fontweight="bold")
axs[1, 1].set_xlabel("Time $t$ (hours)")
axs[1, 1].set_ylabel("Reliability $R(t)$")
axs[1, 1].set_ylim(-0.05, 1.05)
axs[1, 1].grid(True, linestyle="--", alpha=0.7)
axs[1, 1].legend()

plt.tight_layout()
plt.show()
