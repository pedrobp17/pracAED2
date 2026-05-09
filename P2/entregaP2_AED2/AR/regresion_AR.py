import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import os

# --- Configuración de carpetas ---
os.makedirs('figurasAR', exist_ok=True)

# Leer CSV generado por el programa de C++
df = pd.read_csv('resultados_AR.csv')

# --- Cálculo de variables auxiliares para las regresiones ---
# Peor Caso: Teóricamente n³
df['n3'] = df['Longitud']**3
# Mejor Caso: Teóricamente n² log n
df['n2logn'] = (df['Longitud']**2) * np.log(df['Longitud'])

# --- CÁLCULO DE REGRESIONES ---

# Regresión Peor Caso
slope_p, intercept_p, r_p, p_p, _ = stats.linregress(df['n3'], df['PeorCaso'])

# Regresión Mejor Caso
slope_m, intercept_m, r_m, p_m, _ = stats.linregress(df['n2logn'], df['MejorCaso'])

# --- PRINT DE RESULTADOS POR CONSOLA ---

print("=== ANÁLISIS DE REGRESIÓN: AVANCE RÁPIDO ===")
print(f"\nPEOR CASO (~n³):")
print(f"  Pendiente: {slope_p:.10f}")
print(f"  R²: {r_p**2:.4f} (Calidad del ajuste)")
mse_p = np.mean((df['PeorCaso'] - (slope_p * df['n3'] + intercept_p))**2)
print(f"  MSE: {mse_p:.4f}")
print(f"  p-valor: {p_p:.4e}")

print(f"\nMEJOR CASO (~n² log n):")
print(f"  Pendiente: {slope_m:.10f}")
print(f"  R²: {r_m**2:.4f}")
mse_m = np.mean((df['MejorCaso'] - (slope_m * df['n2logn'] + intercept_m))**2)
print(f"  MSE: {mse_m:.4f}")
print(f"  p-valor: {p_m:.4e}")

# --- GENERACIÓN DE GRÁFICAS ---

# 1. PEOR CASO CON ESCALA LINEAL
plt.figure(figsize=(8, 5))
plt.plot(df['Longitud'], df['PeorCaso'], 'bx', label='Tiempos Reales')
plt.plot(df['Longitud'], slope_p * df['n3'] + intercept_p, 'r-', label=r'Ajuste $\Theta(n^3)$')
plt.xlabel('n (Tamaño entrada)')
plt.ylabel('Tiempo (ms)')
plt.title('Peor Caso: Escala Lineal (Crecimiento Cúbico)')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_peor_lineal_AR.pdf')

# 2. PEOR CASO CON ESCALA LOG
plt.figure(figsize=(8, 5))
plt.plot(df['Longitud'], df['PeorCaso'], 'bx', label='Tiempos Reales')
plt.plot(df['Longitud'], slope_p * df['n3'] + intercept_p, 'r-', label=r'Ajuste $\Theta(n^3)$')
plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('log(n)')
plt.ylabel('log(Tiempo)')
plt.title('Peor Caso: Escala Log-Log (Verificación de Potencia)')
plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.savefig('figurasAR/ajuste_peor_log_AR.pdf')

# 3. MEJOR CASO CON ESCALA LINEAL
plt.figure(figsize=(8, 5))
plt.plot(df['Longitud'], df['MejorCaso'], 'gx', label='Tiempos Reales')
plt.plot(df['Longitud'], slope_m * df['n2logn'] + intercept_m, 'r-', label=r'Ajuste $\Theta(n^2 \log n)$')
plt.xlabel('n (Tamaño entrada)')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor Caso: Escala Lineal')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_mejor_lineal_AR.pdf')

# 4. MEJOR CASO CON ESCALA LOG
plt.figure(figsize=(8, 5))
plt.plot(df['Longitud'], df['MejorCaso'], 'gx', label='Tiempos Reales')
plt.plot(df['Longitud'], slope_m * df['n2logn'] + intercept_m, 'r-', label=r'Ajuste $\Theta(n^2 \log n)$')
plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('log(n)')
plt.ylabel('log(Tiempo)')
plt.title('Mejor Caso: Escala Log-Log')
plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.savefig('figurasAR/ajuste_mejor_log_AR.pdf')

print("\n[PROCESO COMPLETADO]: Se han generado 4 archivos PDF en la carpeta 'figurasAR/'.")