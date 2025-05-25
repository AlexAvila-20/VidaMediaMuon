Se describen los dos archivos utilizados para el análisis experimental de la vida media del muón.

## Archivos

### `CPDE.py`

Este programa se encarga de:
- Leer todos los archivos `.paa` en una carpeta específica.
- Detectar eventos de decaimiento de muones caracterizados por dos picos en la señal.
- Calcular el intervalo de tiempo $Delta t$ entre dichos picos.
- Guardar todos los valores válidos en un archivo `vdelta_t.txt`.

### `muon_lifetime_fit.C`

Este programa para ejecución en ROOT se encarga de:
- Leer los valores de $\Delta t$ guardados en `vdelta_t.txt`.
- Crear un histograma con los tiempos de decaimiento.
- Ajustar una función exponencial del tipo $A \cdot e^{-t/\tau} + C$ a los datos.
- Calcular la vida media experimental del muón y el chi-cuadrado reducido.
