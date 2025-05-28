import os
import glob
import numpy as np
from scipy.signal import find_peaks
from paa01 import paaFile

# CONFIGURACIÓN
carpeta = "LA-mml"              # Carpeta con los datos .paa
umbral = -300                   # Umbral mínimo
ns_por_punto = 8                # 8 ns por punto
distancia_minima = 100          # en puntos (~800 ns)

delta_ts = []

# OBTENER ARCHIVOS .paa
archivos_paa = glob.glob(os.path.join(carpeta, "*.paa"))

# PROCESAR CADA ARCHIVO
for archivo_path in archivos_paa:
    print(f"Procesando: {archivo_path}")
    try:
        archivo = paaFile(archivo_path)
        N = archivo.paaGetPulseCount()

        for i in range(N):
            pulso = archivo.paaGetPulseRP(i)
            señal_invertida = [-v for v in pulso]
            picos, _ = find_peaks(señal_invertida, height=-umbral, distance=distancia_minima)

            if len(picos) >= 2:
                p1, p2 = picos[:2]
                dt_us = abs(p2 - p1) * ns_por_punto / 1000
                delta_ts.append(dt_us)

    except Exception as e:
        print(f"Error al procesar {archivo_path}: {e}")

# GUARDAR RESULTADOS
np.savetxt("vdelta_t.txt", delta_ts, fmt="%.6f")
print(f"\nGuardados {len(delta_ts)} Δt en vdelta_t.txt")
