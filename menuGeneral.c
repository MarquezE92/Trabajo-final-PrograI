#include <stdio.h>
#include <stdlib.h>

#include "menuGeneral.h"
#include "adminperritos.h"
#include "adoptantes.h"
//#include "adopciones.h"
//#include "solicitudes.h"

const char *porteTexto[] =
{
    "CHICO",
    "MEDIANO",
    "GRANDE"
};

const char *generoTexto[] =
{
    "MACHO",
    "HEMBRA"
};

const char *estadoTexto[] =
{
    "DISPONIBLE",
    "ADOPTADO"
};

const char *temperamentoTexto[] =
{
    "CALMADO",
    "JUGUETON",
    "ANSIOSO",
    "AGRESIVO",
    "SOCIABLE"
};

void menuPrincipal(const char archivoPerritos[],
                   const char archivoAdoptantes[],
                   const char archivoSolicitudes[],
                   const char archivoAdopciones[])
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Administrador              |");
        printf("\n| \t 2.- Adoptante                 |");
        printf("\n| \t 0.- Salir                     |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion)
        {
        case 1:

            menuPerritosGeneral((char *)archivoPerritos);
            break;

        case 2:

            printf("\nModulo Adoptante en construccion.\n");
            system("pause");
            system("cls");
            break;

        case 0:

            printf("\nHasta luego.\n");
            break;

        default:

            printf("\nOpcion invalida.\n");
            system("pause");
            system("cls");
        }

    }
    while(opcion != 0);
}
