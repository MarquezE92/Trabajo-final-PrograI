#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menuGeneral.h"
#include "adopciones.h"
#include "adminperritos.h"
#include "adoptantes.h"
#include "perritos.h"
#include "menuAdmin.h"
#include "pila.h"
#include <time.h>

PilaAdopciones historial;

void menuGestionarAdopciones()
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Cargar Adopcion              |");
        printf("\n| \t 2.- Mostrar Adopciones           |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        if (scanf("%d", &opcion) != 1)
        {
            printf("\nDebe ingresar un numero.\n");
            while (getchar() != '\n');
            opcion = -1;
        }
        system("cls");

        switch(opcion)
        {
        case 1:

            registrarAdopcion(ARCHIVO_PERRITOS, ARCHIVO_ADOPTANTES, ARCHIVO_ADOPCIONES);
            break;

        case 2:
            ordenarArchivoAdopciones(ARCHIVO_ADOPCIONES);
            mostrarAdopciones(ARCHIVO_ADOPCIONES);
            menuSeleccionAdopciones();
            break;

        case 0:
            break;

        default:
            printf("\nOpcion invalida.\n");
            system("pause");
            system("cls");
            getchar();
        }

    }
    while(opcion != 0);

}
void menuSeleccionAdopciones()
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Registrar Adopcion           |");
        printf("\n| \t 2.- Agregar Observacion          |");
        printf("\n| \t 3.- Pasar a Historico            |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        if (scanf("%d", &opcion) != 1)
        {
            printf("\nDebe ingresar un numero.\n");
            while (getchar() != '\n');
            opcion = -1;
        }
        system("cls");

        switch(opcion)
        {
        case 1:

            registrarAdopcion(ARCHIVO_PERRITOS, ARCHIVO_ADOPTANTES,ARCHIVO_ADOPCIONES);
            ordenarArchivoAdopciones(ARCHIVO_ADOPCIONES);
            break;

        case 2:
        {
            int idPerrito;

            do
            {
                printf("\nIngrese el ID del perrito: ");

                if(scanf("%d", &idPerrito) != 1)
                {
                    printf("\nDebe ingresar un numero.\n");

                    while(getchar() != '\n');

                    idPerrito = -1;
                }

                if(idPerrito <= 0 && idPerrito != -1)
                {
                    printf("\nEl ID debe ser mayor a 0.\n");
                }

            }
            while(idPerrito <= 0);

            getchar();
            cargarObservacion(ARCHIVO_ADOPCIONES, idPerrito);

            break;
        }

        case 3:
        {
            int idPerrito;

            do
            {
                printf("\nIngrese el ID del perrito: ");

                if(scanf("%d", &idPerrito) != 1)
                {
                    printf("\nDebe ingresar un numero.\n");

                    while(getchar() != '\n');

                    idPerrito = -1;
                }

                if(idPerrito <= 0 && idPerrito != -1)
                {
                    printf("\nEl ID debe ser mayor a 0.\n");
                }

            }
            while(idPerrito <= 0);

            pasarAHistorico(ARCHIVO_ADOPCIONES, ARCHIVO_HISTORICO, idPerrito);
            //mostrarPila(&historial);

            break;
        }

        case 0:

            break;

        default:

            printf("\nOpcion invalida.\n");
            system("pause");
            system("cls");
        }

    }
    while(opcion != 0);
}

/// reg adop: busca perri y adoptante en arch, crea reg de adop y lo guarda.
void registrarAdopcion(char archPerritos[], char archAdoptantes[], char archAdopciones[])
{
    int idPerrito;
    int idAdoptante;
    Perrito perri;
    Adoptante adoptante;
    Adopcion nueva;

    int encontroPerrito = 0;
    int encontroAdoptante = 0;
    int exito = 1;

    FILE *pfPerrito = NULL;
    FILE *pfAdoptante = NULL;
    FILE *pfAdopcion = NULL;

    long posicionRegistro=0;

    do
    {
        printf("\nIngrese ID del perrito a adoptar <3: ");

        if(scanf("%d", &idPerrito) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            idPerrito = -1;
        }

        if(idPerrito <= 0 && idPerrito != -1)
        {
            printf("\nEl ID debe ser mayor a 0.\n");
        }

    }
    while(idPerrito <= 0);


    do
    {
        printf("Ingrese ID del adoptante: ");

        if(scanf("%d", &idAdoptante) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            idAdoptante = -1;
        }

        if(idAdoptante <= 0 && idAdoptante != -1)
        {
            printf("\nEl ID debe ser mayor a 0.\n");
        }

    }
    while(idAdoptante <= 0);

    pfPerrito = fopen(archPerritos, "rb+");

    if(pfPerrito == NULL)
    {
        printf("\nError al abrir archivo de perritos.\n");
        exito = 0;
    }

    if(exito)
    {
        while(fread(&perri, sizeof(Perrito), 1, pfPerrito) > 0)
        {
            if(perri.idPerrito == idPerrito)
            {
                encontroPerrito = 1;
                if(perri.estado == 1)
                {
                    printf("\nEse perrito ya fue adoptado.\n");
                    exito = 0;
                }
                else
                {
                    posicionRegistro = ftell(pfPerrito) - sizeof(Perrito);
                }

            }
        }

        if(!encontroPerrito)
        {
            printf("\nNo se encontro el perrito con ID %d.\n", idPerrito);
            exito = 0;
        }
    }

    if(exito)
    {
        pfAdoptante = fopen(archAdoptantes, "rb");

        if(pfAdoptante == NULL)
        {
            printf("\nError al abrir archivo de adoptantes.\n");
            exito = 0;
        }
    }

    if(exito)
    {
        while(fread(&adoptante, sizeof(Adoptante), 1, pfAdoptante) > 0 && !encontroAdoptante)
        {
            if(adoptante.idAdoptante == idAdoptante)
            {
                encontroAdoptante = 1;
            }
        }

        fclose(pfAdoptante);
        pfAdoptante = NULL;

        if(!encontroAdoptante)
        {
            printf("\nNo se encontro el adoptante con ID %d.\n", idAdoptante);
            exito = 0;
        }
    }

    if(exito)
    {
        nueva.idPerrito = idPerrito;
        nueva.idAdoptante = idAdoptante;

        for(int i = 0; i < 6; i++)
        {
            nueva.observaciones[i].fecha[0] = '\0';
            nueva.observaciones[i].comentario[0] = '\0';
        }

        fseek(pfPerrito, posicionRegistro, SEEK_SET);

        perri.estado = 1;

        fwrite(&perri, sizeof(Perrito), 1, pfPerrito);

        pfAdopcion = fopen(archAdopciones, "ab");

        if(pfAdopcion == NULL)
        {
            printf("\nError al guardar la adopcion.\n");
        }
        else
        {
            fwrite(&nueva, sizeof(Adopcion), 1, pfAdopcion);

            fclose(pfAdopcion);

            printf("\nAdopcion registrada con exito!");
            printf("\n%s ahora tiene un hogar <3\n", perri.nombre);
        }
    }

    if(pfPerrito != NULL)
    {
        fclose(pfPerrito);
    }

    if(pfAdoptante != NULL)
    {
        fclose(pfAdoptante);
    }
}

/// carga obs: busca adop por idPerrito y agrega observ en el primer lugar vacio
void cargarObservacion(char archAdopciones[], int idPerrito)
{
    Adopcion aux;
    int encontrado = 0;
    int posLibre = 0;
    FILE *pfAdopcion = fopen(archAdopciones, "r+b");

    if (pfAdopcion == NULL)
    {
        printf("\nError al abrir archivo de adopciones.\n");
    }
    else
    {
        while (!encontrado && fread(&aux, sizeof(Adopcion), 1, pfAdopcion) > 0 )
        {
            if (aux.idPerrito == idPerrito)
            {
                encontrado = 1;
                int i = 0;
                while (i < 6 && !posLibre)
                {
                    if (aux.observaciones[i].fecha[0] == '\0')
                    {
                        posLibre = 1;

                        time_t t = time(NULL);
                        struct tm *fechaHoy = localtime(&t);
                        sprintf(aux.observaciones[i].fecha, "%02d/%02d/%04d",
                                fechaHoy->tm_mday,
                                fechaHoy->tm_mon + 1,
                                fechaHoy->tm_year + 1900);

                        do
                        {
                            printf("Ingrese observacion: ");

                            fgets(aux.observaciones[i].comentario, sizeof(aux.observaciones[i].comentario), stdin);

                            aux.observaciones[i].comentario[strcspn(aux.observaciones[i].comentario, "\n")] = '\0';

                            if (strlen(aux.observaciones[i].comentario) == 0)
                            {
                                printf("\nEl campo no puede estar vacio. Intente de nuevo.\n");
                            }
                        }
                        while (strlen(aux.observaciones[i].comentario) == 0);

                        fseek(pfAdopcion, -(long)sizeof(Adopcion), SEEK_CUR);
                        fwrite(&aux, sizeof(Adopcion), 1, pfAdopcion);
                        printf("\nObservacion guardada.\n");
                    }
                    i++;
                }
                if (!posLibre)
                {
                    printf("\nYa se cargaron todas las observaciones para este perrito.\n");
                }
            }
        }
        if (!encontrado)
        {
            printf("\nNo se encontro adopcion para el perrito ID %d.\n", idPerrito);
        }
        fclose(pfAdopcion);
    }
}


/// show adop (adop activas con observ cargadas)
void mostrarAdopciones(char archAdopciones[])
{
    Adopcion aux;
    int cont = 0;

    FILE *pfAdopcion = fopen(archAdopciones, "rb");

    if(pfAdopcion == NULL)
    {
        printf("\nNo hay adopciones registradas aun.\n");
    }
    else
    {
        printf("\n========== ADOPCIONES ACTIVAS ==========\n");

        while(fread(&aux, sizeof(Adopcion), 1, pfAdopcion) > 0)
        {
            int hayObservaciones = 0;

            char nombrePerrito[35] = "No encontrado";
            char nombreAdoptante[35] = "No encontrado";

            Perrito perri;
            Adoptante adop;

            FILE *pfP = fopen(ARCHIVO_PERRITOS, "rb");

            if(pfP)
            {
                while(fread(&perri, sizeof(Perrito), 1, pfP) > 0)
                {
                    if(perri.idPerrito == aux.idPerrito)
                    {
                        strcpy(nombrePerrito, perri.nombre);
                        break;
                    }
                }

                fclose(pfP);
            }

            FILE *pfA = fopen(ARCHIVO_ADOPTANTES, "rb");

            if(pfA)
            {
                while(fread(&adop, sizeof(Adoptante), 1, pfA) > 0)
                {
                    if(adop.idAdoptante == aux.idAdoptante)
                    {
                        strcpy(nombreAdoptante, adop.nombre);
                        break;
                    }
                }

                fclose(pfA);
            }

            cont++;

            printf("\nPerrito ID   : %d - %s",
                   aux.idPerrito,
                   nombrePerrito);

            printf("\nAdoptante ID : %d - %s",
                   aux.idAdoptante,
                   nombreAdoptante);

            printf("\nObservaciones:");

            for(int i = 0; i < 6; i++)
            {
                if(aux.observaciones[i].fecha[0] != '\0')
                {
                    printf("\n[%s] %s",
                           aux.observaciones[i].fecha,
                           aux.observaciones[i].comentario);

                    hayObservaciones = 1;
                }
            }

            if(!hayObservaciones)
            {
                printf("\nSin observaciones cargadas.");
            }

            printf("\n----------------------------------------\n");
        }

        if(cont == 0)
        {
            printf("\nNo hay adopciones activas.\n");
        }

        fclose(pfAdopcion);
    }
}


/// de arch a historiarch. reescribe arch sacando el dato pasado
void pasarAHistorico(char archAdopciones[], char archHistorico[], int idPerrito)
{
    Adopcion aux;
    int encontrado = 0;

    FILE *pfOrigen = fopen(archAdopciones, "rb");
    FILE *pfTemp = fopen("temp_adopciones.dat", "wb");
    FILE *pfHistorico = fopen(archHistorico, "ab");

    if (!pfOrigen || !pfTemp || !pfHistorico)
    {
        printf("\nError al abrir archivos para mover al historico.\n");

        if (pfOrigen) fclose(pfOrigen);
        if (pfTemp) fclose(pfTemp);
        if (pfHistorico) fclose(pfHistorico);
    }
    else
    {
        while (fread(&aux, sizeof(Adopcion), 1, pfOrigen) > 0)
        {
            if (aux.idPerrito == idPerrito && !encontrado)
            {
                fwrite(&aux, sizeof(Adopcion), 1, pfHistorico);

                apilarAdopcion(&historial, aux);

                encontrado = 1;
            }
            else
            {
                fwrite(&aux, sizeof(Adopcion), 1, pfTemp);
            }
        }

        fclose(pfOrigen);
        fclose(pfTemp);
        fclose(pfHistorico);

        pfOrigen = fopen(archAdopciones, "wb");
        pfTemp = fopen("temp_adopciones.dat", "rb");

        if (pfOrigen && pfTemp)
        {
            while (fread(&aux, sizeof(Adopcion), 1, pfTemp) > 0)
            {
                fwrite(&aux, sizeof(Adopcion), 1, pfOrigen);
            }
        }

        if (pfOrigen) fclose(pfOrigen);
        if (pfTemp) fclose(pfTemp);

        if (encontrado)
        {
            printf("\nAdopcion del perrito ID %d movida al historico.\n", idPerrito);

            printf("\nHistorial actualizado:\n");
            mostrarPila(&historial);
        }
        else
        {
            printf("\nNo se encontro adopcion con ID de perrito %d.\n", idPerrito);
        }
    }
}


void inicializarPila(PilaAdopciones *pila)
{
    pila->tope = -1;
}

int pilaLlena(PilaAdopciones *pila)
{
    return pila->tope == MAX_PILA - 1;
}

int pilaVacia(PilaAdopciones *pila)
{
    return pila->tope == -1;
}

void apilarAdopcion(PilaAdopciones *pila, Adopcion a)
{
    if (pilaLlena(pila))
    {
        printf("\nEl historial esta lleno.\n");
    }
    else
    {
        pila->tope++;
        pila->elementos[pila->tope] = a;
    }
}

Adopcion desapilarAdopcion(PilaAdopciones *pila)
{
    Adopcion vacia = {0};
    if (!pilaVacia(pila))
    {
        vacia = pila->elementos[pila->tope--];
    }
    else
    {
        printf("\nEl historial esta vacio.\n");
    }
    return vacia;
}

void mostrarPila(PilaAdopciones *pila)
{
    if (pilaVacia(pila))
    {
        printf("\nNo hay historial de adopciones.\n");
    }
    else
    {
        printf("\n===== HISTORIAL =====\n");
        int i;
        for (i = pila->tope; i >= 0; i--)
        {
            printf("\n  Perrito ID: %d  |  Adoptante ID: %d",
                   pila->elementos[i].idPerrito,
                   pila->elementos[i].idAdoptante);
        }
        printf("\n============================================\n");
    }
}

void insertarAdopcion(Adopcion lista[], int pos)
{
    Adopcion aux = lista[pos];
    int i = pos - 1;

    while(i >= 0 && lista[i].idPerrito > aux.idPerrito)
    {
        lista[i + 1] = lista[i];
        i--;
    }

    lista[i + 1] = aux;
}

void ordenamientoInsercionAdopciones(Adopcion lista[], int validos)
{
    int i;

    for(i = 1; i < validos; i++)
    {
        insertarAdopcion(lista, i);
    }
}

void ordenarArchivoAdopciones(char archAdopciones[])
{
    Adopcion lista[100];
    int validos = 0;

    FILE *pf = fopen(archAdopciones, "rb");

    if(pf)
    {
        while(fread(&lista[validos], sizeof(Adopcion), 1, pf) > 0)
        {
            validos++;
        }

        fclose(pf);

        ordenamientoInsercionAdopciones(lista, validos);

        pf = fopen(archAdopciones, "wb");

        if(pf)
        {
            fwrite(lista, sizeof(Adopcion), validos, pf);
            fclose(pf);

            printf("\nArchivo de adopciones ordenado por ID de perrito.\n");
        }
    }
}
