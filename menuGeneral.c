#include <stdio.h>
#include <stdlib.h>

#include "menuGeneral.h"
#include "adminperritos.h"
#include "adoptantes.h"
#include "adopciones.h"
#include "perritos.h"

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
    Perrito lista[15]= {};

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| Quien nos visita hoy?                   |");
        printf("\n+-----------------------------------------+");
        printf("\n| \t 1.- Administrador                |");
        printf("\n| \t 2.- Adoptante                    |");
        printf("\n| \t 3.- Perrito                      |");
        printf("\n| \t 0.- Salir                        |");
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
//Reemplazar con función que pase los elementos del archivo a un array
            mostrarMenuAdoptante(lista, 0, archivoSolicitudes);
            break;
        case 3:
            printf("\nLa suplantacion de identidad perruna en una ofensa grave. Su accionar ha sido reportado al consejo canino\n");
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
            getchar();
        }

    }
    while(opcion != 0);
}
