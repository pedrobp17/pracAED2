import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs('figurasPoda', exist_ok=True)

# Leer CSV con los resultados
df = pd.read_csv('resultados_poda.csv')

# Agrupamos por 'nw' y sacamos la mediana de los tiempos
agg = df.groupby('nw').agg(
    sinPoda_median=('Tiempo_Sin_Poda', 'median'),
    conPoda_median=('Tiempo_Con_Poda', 'median')
).reset_index()

plt.figure(figsize=(8, 6))

# Graficar únicamente las medianas. 
plt.plot(agg['nw'], agg['sinPoda_median'], 'ro-', label='Sin Poda (Mediana)', markersize=8)
plt.plot(agg['nw'], agg['conPoda_median'], 'bx-', label='Con Poda (Mediana)', markersize=8, markeredgewidth=2)

# Aplicar escala logarítmica al eje Y
plt.yscale('log')

# Configuración de los ejes
plt.xlabel('n', fontsize=12)
plt.ylabel('Tiempo (ms) - Escala Log', fontsize=12)

plt.legend(fontsize=12, loc='upper left')
plt.grid(True, which='both', linestyle='--', alpha=0.6)

# guardar
plt.title('Comparativa Backtracking')
plt.tight_layout()
plt.savefig('figurasPoda/comparativa_tiempos.pdf')

print("\n[PROCESO COMPLETADO]: Gráfica generada en 'figurasPoda/comparativa_tiempos.pdf'.")