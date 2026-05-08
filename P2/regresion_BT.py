import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import os

# Crear carpeta para figuras si no existe para evitar errores
if not os.path.exists('figurasBT'):
    os.makedirs('figurasBT')

# Leer CSV
df = pd.read_csv('resultados_asignacion_BT.csv')

# --- SINCRONIZACIÓN DE NOMBRES ---
# Cambiamos 'N' por 'n' para el resto del script
df['n'] = df['N'] 
df['t_sin'] = df['Tiempo_Sin_Poda']
df['t_con'] = df['Tiempo_Con_Poda']
df['n2'] = np.power(df['n'], 2)

# --- REGRESIÓN PARA PEOR CASO (Poda): T(n) vs n^2 ---
# Usamos 't_con' que es lo que tenemos en el CSV
slope_poda, intercept_poda, r_poda, p_poda, _ = stats.linregress(df['n2'], df['t_con'])

# Resultados por consola
print("   Regresión lineal Caso con Poda ~ n^2")
print(f"  Pendiente: {slope_poda:.6f}")
print(f"  R²: {r_poda**2:.4f}")
print(f"  p-valor: {p_poda:.4e}")

# 1. Gráfico de dispersión comparativo
plt.figure()
plt.plot(df['n'], df['t_sin'], 'ro', label='Sin Poda')
plt.plot(df['n'], df['t_con'], 'bx', label='Con Poda')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Comparativa Backtracking')
plt.legend()
plt.grid(True)
plt.savefig('figurasBT/comparativa_tiempos.pdf')

# 2. Ajuste cuadrático para la versión con poda
plt.figure()
plt.plot(df['n'], df['t_con'], 'x', label='Tiempos reales')
plt.plot(df['n'], slope_poda * df['n2'] + intercept_poda, label=r'Ajuste $\Theta(n^2)$')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Ajuste Teórico Con Poda')
plt.legend()
plt.grid(True)
plt.savefig('figurasBT/ajuste_poda_BT.pdf')
