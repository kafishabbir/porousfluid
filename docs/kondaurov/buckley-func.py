import numpy as np
import matplotlib.pyplot as plt
import os

output_dir = "results"
os.makedirs(output_dir, exist_ok=True)


S_max = 1
nS = 1000
Sv = np.linspace(0, S_max, nS)

def b_equilibrium_case():
	def k1(S):
		return S**2

	def k2(S):
		return (1 - S)**2

	def b(S):
		return k1(S) /  (k1(S) + k2(S))

	return b(Sv)


def b_non_equilibrium_case():
	def k1(S):
		return (2*S)**2

	def k2(S):
		return (1 - 2*S)**2

	def b(S):
		return k1(S) /  (k1(S) + k2(S))

	return b(Sv)


def tangent(x, y):
	mn = 1e9
	n = len(y)
	point = -1
	slope = -1
	for i in range(10, n):
		delta_y = y[i] - y[i - 1]
		delta_x = x[i] - x[i - 1]
		tangent = delta_y / delta_x

		average_slope = y[i] / x[i]

		difference = abs(tangent - average_slope)

		if(difference < mn):
			mn = difference
			point = i
			slope = average_slope

	def line(x):
		return slope * x

	return (line(x), y[point], x[point])

b_eq = b_equilibrium_case()
b_neq = b_non_equilibrium_case()
(tangent_eq, y_eq, S_star_eq) = tangent(Sv, b_eq)
(tangent_neq, y_neq, S_star_neq) = tangent(Sv, b_neq)

for i in range (nS//2, nS):
	b_neq[i] = 2

plt.figure(figsize=(8, 8))
plt.plot(Sv, b_eq, label=f"b(S),equilibrium", color='blue', lw=2)
plt.plot(Sv, tangent_eq, label=f"tangent,equilibrium", linestyle='--', color='blue')
plt.axvline(x=S_star_eq, ymax=y_eq, linestyle='--', color='blue')
plt.plot(S_star_eq, y_eq, 'bo')
plt.plot(S_star_eq, 0, 'bo')
plt.text(S_star_eq + 0.02, 0.02, fr'$S^*_{{eq}}={S_star_eq:.2f}$', color='blue')
plt.text(S_star_eq + 0.02, y_eq - 0.02, fr'$v_{{eq}}={y_eq / S_star_eq:.2f}$', color='blue')


print(f'x={S_star_eq} y={y_eq}')
print(f'x={S_star_neq} y={y_neq}')
plt.plot(Sv, b_neq, label=f"b(S),non-equilibrium", color='red', lw=2)
plt.plot(Sv, tangent_neq, label=f"tangent,non-equilibrium", linestyle='--', color='red')
plt.axvline(x=S_star_neq, ymax=y_neq, linestyle='--', color='red')
plt.plot(S_star_neq, y_neq, 'ro')
plt.plot(S_star_neq, 0, 'ro')
plt.plot(S_star_neq, 0, 'ro')
plt.text(S_star_neq + 0.02, 0.02, fr'$S^*_{{neq}}={S_star_neq:.2f}$', color='red')
plt.text(S_star_neq + 0.02, y_neq, fr'$v_{{neq}}={y_neq / S_star_neq:.2f}$', color='red')


plt.xlabel("S")
plt.ylabel("b(S)")
plt.title(f"b(S)")

plt.xlim(0, 1)
plt.ylim(0, 1)
plt.grid()
plt.legend()
plt.tight_layout()
filename = os.path.join(output_dir, f"buckley-func.png")
filename_txt = os.path.join(output_dir, f"buckley-funс.txt")
plt.savefig(filename)
plt.close()

data = np.column_stack((Sv, b_eq, b_neq, tangent_eq, tangent_neq))
np.savetxt(filename_txt, data, delimiter='\t', fmt='%.3f', header='S\tb_eq\tb_neq\ttangent_eq,\ttangent_neq', comments='')


