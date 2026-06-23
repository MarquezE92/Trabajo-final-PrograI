#include <stdio.h>

int obtenerMes(char fecha[])
{
    int dia; mes, anio;

    sscanf(fecha, "%d/%d/%d",&dia, &mes, &anio);

    return mes;
}

void inicializarMatriz(int estadisticas[MESES][COLUMNAS])
{
    int i, j;

    for(i = 0; i < MESES; i++)
    {
        for(j = 0; j < COLUMNAS; j++)
        {
            estadisticas[i][j] = 0;
        }
    }
}

void cargarMetricasPerros(char nombreArchivo[], int metricasMat[MESES][COLUMNAS]){
    Perrito perro;

    FILE *fp = fopen(nombreArchivo, "rb");

    if(fp == NULL){
        printf("No se pudo abrir el archivo para contar los perritos");
    }else
    {
        while(fread(&perro, sizeof(Perrito), 1, fp) > 0)
        {
            int mes = obtenerMes(perro.fechaIngreso);

            if(mes >= 1 && mes <= 12)
            {
                metricasMat[mes - 1][COL_PERROS]++;
            }
        }

        fclose(fp);
    }
}

void cargarMetricaaAdopciones(char nombreArchivo[], int metricasMat[MESES][COLUMNAS])
{
    Adopcion adopcion;

    FILE *fp = fopen(nombreArchivo, "rb");

    if(fp == NULL){
        printf("No se pudo abrir el archivo para contar las adopciones");
    }else
    {
        while(fread(&adopcion, sizeof(Adopcion), 1, fp) > 0)
        {
            if(strlen(adopcion.observaciones[0].fecha) > 0)
            {
                int mes = obtenerMes(adopcion.observaciones[0].fecha);

                if(mes >= 1 && mes <= 12)
                {
                    metricasMat[mes - 1][COL_ADOPCIONES]++;
                }
            }
        }

        fclose(fp);
    }
}

void generarEstadisticasMensuales(int estadisticas[MESES][COLUMNAS], char archivoPerros[], char archivoAdopciones[])
{
    inicializarMatriz(estadisticas);

    cargarEstadisticasPerros(archivoPerros, estadisticas);

    cargarEstadisticasAdopciones(archivoAdopciones, estadisticas);
}

void mostrarEstadisticas(int estadisticas[MESES][COLUMNAS])
{
    char meses[MESES][15] =
    {
        "Enero",
        "Febrero",
        "Marzo",
        "Abril",
        "Mayo",
        "Junio",
        "Julio",
        "Agosto",
        "Septiembre",
        "Octubre",
        "Noviembre",
        "Diciembre"
    };

    int i;

    printf("\n%-12s %-10s %-12s\n",
           "Mes",
           "Perros",
           "Adopciones");

    for(i = 0; i < MESES; i++)
    {
        printf("%-12s %-10d %-12d\n",
               meses[i],
               estadisticas[i][COL_PERROS],
               estadisticas[i][COL_ADOPCIONES]);
    }
}
