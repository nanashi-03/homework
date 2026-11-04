import matplotlib.pyplot as plt
import numpy as np

lam = 0.3
k = 0.9
m = 0.5

t = np.arange(1, 11)

R1 = np.exp(-lam * t)

R2 = np.exp(-(k * t**2) / 2)

R3 = np.exp(-(k * t ** (m + 1)) / (m + 1))

print("Time\tCase I\t\tCase II\t\tCase III")
print("-" * 65)

for i in range(len(t)):
    print(f"{t[i]}\t{R1[i]:.6f}\t{R2[i]:.6f}\t{R3[i]:.6f}")

plt.figure(figsize=(10, 6))

plt.plot(t, R1, marker="o", label="Case I: Constant Hazard")
plt.plot(t, R2, marker="s", label="Case II: Linear Hazard")
plt.plot(t, R3, marker="^", label="Case III: Weibull Hazard")

plt.xlabel("Time to Failure (hours)")
plt.ylabel("Reliability R(t)")
plt.title("Reliability vs Time to Failure")

plt.xticks(t)
plt.ylim(0, 1.05)
plt.grid(True)
plt.legend()

plt.show()
