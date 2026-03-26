import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Leer CSV
df = pd.read_csv('resultados.csv')

# Calcular variables auxiliares
df['n'] = df['Longitud']

# --- REGRESIÓN PARA MEJOR CASO: T(n) vs n ---
slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['n'], df['MejorCaso'])

# --- REGRESIÓN PARA PEOR CASO: T(n) vs n ---
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n'], df['PeorCaso'])

# Resultados<
print("   Regresión lineal MejorCaso ~ n")
print(f"  Pendiente: {slope_mejor:.6f}")
print(f"  R²: {r_mejor**2:.4f}")
print(f"  MSE: {np.mean((df['MejorCaso'] - (slope_mejor * df['n'] + intercept_mejor))**2):.4f}")
print(f"  p-valor: {p_mejor:.4e}\n")


print("   Regresión lineal PeorCaso ~ n")
print(f"  Pendiente: {slope_peor:.6f}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  MSE: {np.mean((df['PeorCaso'] - (slope_peor * df['n'] + intercept_peor))**2):.4f}")
print(f"  p-valor: {p_peor:.4e}")



# 1. Gráfico de dispersión sin ajuste
plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot_log.pdf')

# 2. Ajuste mejor caso
plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['n'] + intercept_mejor, label=r'Ajuste $\Theta(n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Mejor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_mejor_lineal.pdf')

# 3. Ajuste peor caso
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_peor_lineal.pdf')

# idem pero sin log

# 1. Gráfico de dispersión sin ajuste
plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot.pdf')

# 2. Ajuste mejor caso ~ Θ(n)
plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['n'] + intercept_mejor, label=r'Ajuste $\Theta(n)$')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Mejor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_mejor.pdf')

# 3. Ajuste peor caso ~ Θ(n)
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Mejor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_peor.pdf')