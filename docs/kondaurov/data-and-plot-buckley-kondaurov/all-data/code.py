import numpy as np
import matplotlib.pyplot as plt
import os


# Domain and discretization
x_max = 1
nx = 200
x = np.linspace(0, x_max, nx)
dx = x[1] - x[0]

mu1 = 0.4
mu2 = 0.4
taus = [0.001, 0.01, 0.1, 1.0, 10.0]
#taus = [0.01, 0.1]


def buckley():
	# Time stepping
	t_max = 1.0
	dt = 0.001
	nt = int(t_max / dt)

	# Output times
	output_times = np.linspace(0, 0.9, 10)

	# Parameters
	S_sat = 0
	S_force = 1.0


	# Flux function
	def k1(S): return S**2 / mu1
	def k2(S): return (1 - S)**2 / mu2
	def f(S): return k1(S) / (k1(S) + k2(S))

	# Derivative of flux for wave speed estimate
	def df_dS(S):
		epsilon = 1e-6  # for numerical stability
		dk1 = 2 * S / mu1
		dk2 = -2 * (1 - S) / mu2
		num = dk1 * (k1(S) + k2(S)) - k1(S) * (dk1 + dk2)
		denom = (k1(S) + k2(S))**2 + epsilon
		return num / denom

	# Minmod limiter
	def minmod(a, b):
		result = np.zeros_like(a)
		mask = (a * b) > 0
		result[mask] = np.where(np.abs(a[mask]) < np.abs(b[mask]), a[mask], b[mask])
		return result

	# Initialize S
	S = np.ones_like(x) * S_sat
	S[0] = S_force

	# Store outputs
	results = [(0.0, S.copy())]

	# Time stepping
	time = 0.0
	next_output_idx = 1

	for n in range(1, nt + 1):
		dS = np.zeros_like(S)
		dS[1:-1] = minmod((S[1:-1] - S[0:-2]) / dx, (S[2:] - S[1:-1]) / dx)

		S_L = S - 0.5 * dx * dS
		S_R = S + 0.5 * dx * dS

		flux = np.zeros_like(S)
		for i in range(nx - 1):
			SL = S_R[i]
			SR = S_L[i + 1]
			fL = f(SL)
			fR = f(SR)
			a = max(abs(df_dS(SL)), abs(df_dS(SR)))
			flux[i] = 0.5 * (fL + fR) - 0.5 * a * (SR - SL)

		S_new = S.copy()
		for i in range(1, nx - 1):
			S_new[i] -= dt / dx * (flux[i] - flux[i - 1])

		S_new[0] = S_force
		S_new[-1] = S_new[-2]

		S = S_new
		time += dt

		if next_output_idx < len(output_times) and time >= output_times[next_output_idx]:
			results.append((time, S.copy()))
			next_output_idx += 1

	return results


def kondaurov(tau):

	# Parameters
	S_sat = 0.0
	S_force = 1.0
	alpha = 1
	beta = 1
	z_initial = alpha / beta
	z_force = 0

	# Time stepping
	t_max = 1.0
	dt = 0.0001
	nt = int(t_max / dt)

	# Output times
	output_times = np.linspace(0, 0.9, 10)

	# Flux function
	def Sz(S, z):
		return 2 * S + beta / alpha * z - 1

	def k1(S):
		return S**2 / mu1

	def k2(S):

		return (1 - S)**2 / mu2

	def f(S, z):
		S_new = Sz(S, z)
		return k1(S_new) / (k1(S_new) + k2(S_new))

	def df_dS(S, z):
		epsilon = 1e-6  # for numerical stability
		S_new = Sz(S, z)
		dk1 = 4 * S_new / mu1
		dk2 = -4 * (1 - S_new) / mu2
		num = dk1 * (k1(S_new) + k2(S_new)) - k1(S_new) * (dk1 + dk2)
		denom = (k1(S_new) + k2(S_new))**2 + epsilon
		return num / denom

	# Minmod limiter
	def minmod(a, b):
		result = np.zeros_like(a)
		mask = (a * b) > 0
		result[mask] = np.where(np.abs(a[mask]) < np.abs(b[mask]), a[mask], b[mask])
		return result

	# Initialize S and z
	S = np.ones_like(x) * S_sat
	z = np.ones_like(x) * z_initial
	z[0] = z_force
	S[0] = S_force

	# Store outputs
	results = [(0.0, S.copy())]
	results_z = [(0.0, z.copy())]


	# Time stepping
	time = 0.0
	next_output_idx = 1

	for n in range(1, nt + 1):
		dS = np.zeros_like(S)
		dS[1:-1] = minmod((S[1:-1] - S[0:-2]) / dx, (S[2:] - S[1:-1]) / dx)

		S_L = S - 0.5 * dx * dS
		S_R = S + 0.5 * dx * dS


		flux = np.zeros_like(S)
		for i in range(nx - 1):
			SL = S_R[i]
			SR = S_L[i + 1]

			zL = z[i]
			zR = z[i + 1]

			fL = f(SL, zL)
			fR = f(SR, zR)
			a = max(abs(df_dS(SL, zL)), abs(df_dS(SR, zR)))
			flux[i] = 0.5 * (fL + fR) - 0.5 * a * (SR - SL)

		S_new = S.copy()
		for i in range(1, nx - 1):
			S_new[i] -= dt / dx * (flux[i] - flux[i - 1])

		S_new[0] = S_force
		S_new[-1] = S_new[-2]


		for i in range(1, nx):
			z[i] = (z[i] + dt / tau * (1 - S[i])) / (1 + dt / tau)

		S = S_new
		time += dt

		if next_output_idx < len(output_times) and time >= output_times[next_output_idx]:
			print(f't={n}')
			results.append((time, S.copy()))
			results_z.append((time, z.copy()))
			next_output_idx += 1


	for n in range(1, nt + 1):
		dS = np.zeros_like(S)
		dS[1:-1] = minmod((S[1:-1] - S[0:-2]) / dx, (S[2:] - S[1:-1]) / dx)

		S_L = S - 0.5 * dx * dS
		S_R = S + 0.5 * dx * dS


		flux = np.zeros_like(S)
		for i in range(nx - 1):
			SL = S_R[i]
			SR = S_L[i + 1]

			zL = z[i]
			zR = z[i + 1]

			fL = f(SL, zL)
			fR = f(SR, zR)
			a = max(abs(df_dS(SL, zL)), abs(df_dS(SR, zR)))
			flux[i] = 0.5 * (fL + fR) - 0.5 * a * (SR - SL)

		S_new = S.copy()
		for i in range(1, nx - 1):
			S_new[i] -= dt / dx * (flux[i] - flux[i - 1])

		S_new[0] = S_force
		S_new[-1] = S_new[-2]


		for i in range(1, nx):
			z[i] = (z[i] + dt / tau * (1 - S[i])) / (1 + dt / tau)

		S = S_new
		time += dt

		if next_output_idx < len(output_times) and time >= output_times[next_output_idx]:
			print(f't={n}')
			results.append((time, S.copy()))
			results_z.append((time, z.copy()))
			next_output_idx += 1

	return (results, results_z)

# Output directory
output_dir = "results"
os.makedirs(output_dir, exist_ok=True)
kondaurov_tau = []
for tau in taus:
	(result, result_z) = kondaurov(tau)
	kondaurov_tau.append((tau, result, result_z))

results_eq = buckley()

for i in range(6):
	mat_s_x_tau = []
	mat_z_x_tau = []
	(t, Seq_plot) = results_eq[i]
	mat_s_x_tau.append((0, Seq_plot))

	plt.figure(figsize=(8, 4))
	plt.plot(x, Seq_plot, label=f"$\\tau$=0 (Buckley)")

	for j in kondaurov_tau:
		(tau, result, result_z) = j
		(t_kon, S_plot) = result[i]
		(t_kon, z_plot) = result_z[i]
		mat_s_x_tau.append((tau, S_plot))
		mat_z_x_tau.append((tau, z_plot))
		#print(f't_kon - t = {t_kon - t}')
		plt.plot(x, S_plot, label=f"$S(x),\\tau$={tau}")
		plt.plot(x, z_plot, label=f"$\\xi(x),\\tau$={tau}")

	plt.xlabel("x")
	plt.ylabel("S(x)")
	plt.title(f"t = {t:.2f}, $\\mu_1/\\mu_2$ = {mu1/mu2:.3f}")
	plt.xlim(0, 1)
	plt.ylim(0, 1)
	plt.grid()
	plt.legend()
	plt.tight_layout()
	filename = os.path.join(output_dir, f"plot_t-{t:.1f}.png")
	filename_data = os.path.join(output_dir, f"data_t-{t:.1f}.txt")
	plt.savefig(filename)
	plt.close()
	with open(filename_data, 'w') as file:
		file.write("x\t")
		file.write(f'S(x),tau={0}(buckley)\t')
		for tau in taus:
			file.write(f'S(x),tau={tau}\t')
		for tau in taus:
			file.write(f'xi(x),tau={tau}\t')
		file.write('\n')

		for x_i in range(len(x)):
			file.write(f'{x[x_i]:0.4f}\t')
			for col in mat_s_x_tau:
				(tau, S) = col
				file.write(f'{S[x_i]:0.4f}\t')
			for col in mat_z_x_tau:
				(tau, z) = col
				file.write(f'{z[x_i]:0.4f}\t')
			file.write('\n')

