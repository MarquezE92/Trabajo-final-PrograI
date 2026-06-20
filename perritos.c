#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "perritos.h"

const char *porte[] =
{
    "CHICO",
    "MEDIANO",
    "GRANDE"
};

const char *genero[] =
{
    "MACHO",
    "HEMBRA"
};

const char *temperamento[] =
{
    "CALMADO",
    "JUGUETON",
    "ANSIOSO",
    "AGRESIVO",
    "SOCIABLE"
};

const char *estado[] =
{
    "DISPONIBLE",
    "ADOPTADO"
};

Perrito cargarPerrito()
{
    Perrito aux;
    int op;
    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);
    printf("Cargue la edad del perrito: ");
    scanf("%d", &aux.edad);
    getchar();
    printf("Cargue el nombre del perrito: ");
    gets(aux.nombre);
    printf("Cargue la raza del perrito: ");
    gets(aux.raza);
    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);

    sprintf(aux.fechaIngreso,
            "%02d/%02d/%04d",
            fecha->tm_mday,
            fecha->tm_mon + 1,
            fecha->tm_year + 1900);
    do
    {
        printf("Seleccione el porte (0-Chico, 1-Mediano, 2-Grande): ");
        scanf("%d", &op);
        if(op <0 || op>2)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>2);
    aux.porte = op;

    do
    {
        printf("Seleccione el genero (0-Macho, 1-Hembra): ");
        scanf("%d", &op);
        if(op <0 || op>1)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>1);
    aux.genero = op;

    do
    {
        printf("Seleccione el temperamento (0-Calmado, 1-Jugueton, 2-Ansioso, 3-Agresivo, 4-Sociable): ");
        scanf("%d", &op);
        if(op <0 || op>4)
        {
            printf("\nNo es una opcion valida,vuelva a intentarlo");
        }
    }
    while(op <0 || op>4);
    aux.temperamento = op;

    aux.estado = DISPONIBLE;

    return aux;
}

void mostrarPerrito(Perrito perri)
{
    printf("\n==============================\n");
    printf("\nID: %d", perri.idPerrito);
    printf("\nNombre: %s", perri.nombre);
    printf("\nEdad: %d", perri.edad);
    printf("\nRaza: %s", perri.raza);
    printf("\nGenero: %s", genero[perri.genero]);
    printf("\nPorte: %s", porte[perri.porte]);
    printf("\nTemperamento: %s", temperamento[perri.temperamento]);
    printf("\nEstado: %s", estado[perri.estado]);
    printf("\nFecha ingreso: %s", perri.fechaIngreso);
    printf("\n==============================\n");
}


void mostrarTodosPerritos(char nombreArchivo[])
{
    Perrito aux;
    FILE *pf= fopen(nombreArchivo,  "rb");
    if(pf == NULL)
    {
        printf("\nNo se pudo abrir el archivo para mostrar a los Perritos");
    }
    else
    {
        while(fread(&aux, sizeof(Perrito),1, pf)>0)
        {
            mostrarPerrito(aux);
        }
        fclose(pf);
    }
}

void cargarPerritoArchivo(char nombreArchivo[])
{
    Perrito aux;
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL)
    {
        printf("\nNo se pudo abrir el archivo para cargar al Perrito");
    }
    else
    {
        aux = cargarPerrito();
        fwrite(&aux, sizeof(Perrito),1, pf);
        fclose(pf);
    }
}

void filtrarPorPorte(char nombreArchivo[], Porte porteBuscado)
{
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.porte == porteBuscado)
            {
                mostrarPerrito(aux);
            }
        }

        fclose(pf);
    }
}

void filtrarPorGenero(char nombreArchivo[], Genero generoBuscado)
{
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.genero == generoBuscado)
            {
                mostrarPerrito(aux);
            }
        }

        fclose(pf);
    }
}

void filtrarPorEdad(char nombreArchivo[], int edadBuscada)
{
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.edad == edadBuscada)
            {
                mostrarPerrito(aux);
            }
        }

        fclose(pf);
    }
}

void filtrarPorTemperamento(char nombreArchivo[], Temperamento tempBuscado)
{
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.temperamento == tempBuscado)
            {
                mostrarPerrito(aux);
            }
        }

        fclose(pf);
    }
}

void menuGestionPerritos(char nombreArchivo[])
{
    int opcion;
    int id;

    //mostrarTodosPerritos(nombreArchivo);

    printf("\n1- Modificar perrito");
    printf("\n2- Eliminar perrito");
    printf("\n3- Volver");
    printf("\nOpcion: ");
    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:

        printf("\nIngrese ID del perrito a modificar: ");
        scanf("%d", &id);

        modificarPerrito(nombreArchivo, id);

        break;

    case 2:

        printf("\nIngrese ID del perrito a eliminar: ");
        scanf("%d", &id);

        eliminarPerrito(nombreArchivo, id);

        break;

    case 3:

        printf("\nVolviendo...");
        break;

    default:

        printf("\nOpcion invalida");
    }
}

void modificarPerrito(char nombreArchivo[], int idBuscado)
{
    Perrito aux;
    int encontrado = 0;

    FILE *pf = fopen(nombreArchivo, "r+b");

    if(pf == NULL)
    {
        printf("\nNo se pudo abrir el archivo");
    }
    else
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0 && !encontrado)
        {
            if(aux.idPerrito == idBuscado)
            {
                encontrado = 1;

                printf("\nPerrito encontrado:");
                mostrarPerrito(aux);

                printf("\nIngrese los nuevos datos:");

                aux = cargarPerrito();

                aux.idPerrito = idBuscado;

                fseek(pf, -sizeof(Perrito), SEEK_CUR);

                fwrite(&aux, sizeof(Perrito), 1, pf);

                printf("\nModificacion realizada correctamente");
            }
        }

        fclose(pf);

        if(!encontrado)
        {
            printf("\nNo existe un perrito con ese ID");
        }
    }
}

void eliminarPerrito(char nombreArchivo[], int idBuscado)
{
    Perrito aux;
    int encontrado = 0;

    FILE *archivo = fopen(nombreArchivo, "rb");
    FILE *auxiliar = fopen("aux.dat", "wb");

    if(archivo == NULL || auxiliar == NULL)
    {
        printf("\nError al abrir archivos");
    }
    else
    {
        while(fread(&aux, sizeof(Perrito), 1, archivo) > 0)
        {
            if(aux.idPerrito == idBuscado)
            {
                encontrado = 1;

                printf("\nPerrito encontrado:");
                mostrarPerrito(aux);
            }
            else
            {
                fwrite(&aux, sizeof(Perrito), 1, auxiliar);
            }
        }

        fclose(archivo);
        fclose(auxiliar);

        if(encontrado)
        {
            remove(nombreArchivo);
            rename("aux.dat", nombreArchivo);

            printf("\n\nPerrito eliminado correctamente.\n");
        }
        else
        {
            remove("aux.dat");

            printf("\n\nNo existe un perrito con ID %d.\n", idBuscado);
        }
    }
}

void cargaMasivaPerritos(char nombreArchivo[])
{
    Perrito perros[10] =
    {
        {1,"Firulais",3,"Labrador",MEDIANO,DISPONIBLE,JUGUETON,MACHO,"15/01/2026"},
        {2,"Luna",5,"Caniche",CHICO,DISPONIBLE,CALMADO,HEMBRA,"28/01/2026"},
        {3,"Rocky",2,"Ovejero",GRANDE,DISPONIBLE,ANSIOSO,MACHO,"10/02/2026"},
        {4,"Mora",4,"Golden",GRANDE,DISPONIBLE,SOCIABLE,HEMBRA,"22/02/2026"},
        {5,"Toby",1,"Beagle",MEDIANO,DISPONIBLE,JUGUETON,MACHO,"05/03/2026"},
        {6,"Nina",6,"Labrador",GRANDE,DISPONIBLE,CALMADO,HEMBRA,"19/03/2026"},
        {7,"Simba",2,"Mestizo",CHICO,DISPONIBLE,AGRESIVO,MACHO,"08/04/2026"},
        {8,"Kira",3,"Border Collie",MEDIANO,DISPONIBLE,SOCIABLE,HEMBRA,"27/04/2026"},
        {9,"Bruno",7,"Dogo",GRANDE,DISPONIBLE,CALMADO,MACHO,"14/05/2026"},
        {10,"Lola",4,"Salchicha",CHICO,DISPONIBLE,JUGUETON,HEMBRA,"02/06/2026"}
    };

    FILE *pf = fopen(nombreArchivo, "wb");

    if(pf)
    {
        fwrite(perros, sizeof(Perrito), 10, pf);

        fclose(pf);

        printf("\nCarga masiva realizada correctamente.\n");
    }
    else
    {
        printf("\nError al abrir el archivo.\n");
    }
}
