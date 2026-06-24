#include <stdio.h>
#include <stdlib.h>


#include "adminperritos.h"
#include "adoptantes.h"
#include "adopciones.h"
#include "perritos.h"
#include "menuAdmin.h"
#include "metricas.h"

void menuAdminGeneral()
{
    int opcion;
    int contra;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Gestionar Perrito            |");
        printf("\n| \t 2.- Gestionar Adoptantes         |");
        printf("\n| \t 3.- Gestionar Adopciones         |");
        printf("\n| \t 4.- Ver Metricas                 |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1:

            menuPerritosGeneral(ARCHIVO_PERRITOS);
            break;

        case 2:

            menuAdoptante();
            break;

        case 3:

            menuGestionarAdopciones();
            break;

        case 4:
            invocarMetricas();
            break;

        case 0:

            printf("\nChau...\n");
            ///volver menu principal
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
