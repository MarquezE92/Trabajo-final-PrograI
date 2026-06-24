#ifndef METRICAS_H_INCLUDED
#define METRICAS_H_INCLUDED
#define MESES 12
#define COLUMNAS 2

enum
{
    COL_PERROS,
    COL_ADOPCIONES
};

int obtenerMes(char fecha[]);
void inicializarMatriz(int estadisticas[MESES][COLUMNAS]);
void cargarMetricasPerros(char nombreArchivo[], int metricasMat[MESES][COLUMNAS]);
void cargarMetricasAdopciones(char nombreArchivo[], int metricasMat[MESES][COLUMNAS]);
void generarEstadisticasMensuales(int estadisticas[MESES][COLUMNAS], char archivoPerros[], char archivoAdopciones[]);
void mostrarEstadisticas(int estadisticas[MESES][COLUMNAS]);
void invocarMetricas();

#endif // METRICAS_H_INCLUDED
