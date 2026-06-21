#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adminperritos.h"
#include "menuGeneral.h"


void menuPerritosGeneral(char nombreArchivo[])
{
    int opcion;
    int contraseña;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Cargar Perrito               |");
        printf("\n| \t 2.- Mostrar Perritos             |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1:

            cargarPerritoArchivo(nombreArchivo);
            break;

        case 2:

            menuEdicionPerritos(nombreArchivo);
            break;

        case 777:
            system("cls");
            printf("Esta es una opcion oculta.\n");
            printf("si no sabe como llego aca\n");
            printf("pulse 0: ");
            scanf(" %d", &contraseña);
            if(contraseña==1985)
            {
                system("cls");
                cargaMasivaPerritos(nombreArchivo);
            }
            else
            {
                system("cls");
                menuPerritosGeneral(nombreArchivo);
            }
            break;

        case 0:

            printf("\nChau...\n");
            ///volver menu principal
            break;

        default:

            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 0);


}


Perrito cargarPerri()
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
    printf("\nEdad: %d", perri.edad);
    printf("\nNombre: %s", perri.nombre);
    printf("\nRaza: %s", perri.raza);
    printf("\nPorte: %s", porteTexto[perri.porte]);
    printf("\nGenero: %s", generoTexto[perri.genero]);
    printf("\nTemperamento: %s", temperamentoTexto[perri.temperamento]);
    printf("\nEstado: %s", estadoTexto[perri.estado]);
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
        aux = cargarPerri();
        fwrite(&aux, sizeof(Perrito),1, pf);
        fclose(pf);
    }
}


void menuEdicionPerritos(char nombreArchivo[])
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Mostrar Todos Los Perritos   |");
        printf("\n| \t 2.- Aplicar Filtro               |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1:

            int *vecIDs = NULL;
            int validos = 0;
            cargarTodosLosIDs(nombreArchivo, &vecIDs, &validos);
            mostrarTodosPerritos(nombreArchivo);
            menuGestionPerritos(nombreArchivo, vecIDs, validos);
            free(vecIDs);
            break;

        case 2:

            menuFiltro(nombreArchivo);
            break;

        case 0:

            menuPerritosGeneral(nombreArchivo);
            break;

        default:

            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 0);

}

void menuFiltro(char nombreArchivo[])
{
    int opcion;

    Porte port;
    Genero gen;
    Temperamento temp;
    int edad;

    int *vecIDs = NULL;
    int validos = 0;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Filtrar Por Porte            |");
        printf("\n| \t 2.- Filtrar Por Genero           |");
        printf("\n| \t 3.- Filtrar Por Edad             |");
        printf("\n| \t 4.- Filtrar Por Temperamento     |");
        printf("\n| \t 0.- Volver                       |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);
        system("cls");

        validos = 0;
        free(vecIDs);
        vecIDs = NULL;

        switch(opcion)
        {
        case 1:

            printf("\n0 - CHICO");
            printf("\n1 - MEDIANO");
            printf("\n2 - GRANDE");
            printf("\nSeleccione porte: ");
            scanf("%d", &port);

            filtrarPorPorte(nombreArchivo,
                            port,
                            &vecIDs,
                            &validos);

            menuGestionPerritos(nombreArchivo,
                                vecIDs,
                                validos);
            break;

        case 2:

            printf("\n0 - MACHO");
            printf("\n1 - HEMBRA");
            printf("\nSeleccione genero: ");
            scanf("%d", &gen);
            filtrarPorGenero(nombreArchivo, gen, &vecIDs, &validos);
            menuGestionPerritos(nombreArchivo, vecIDs, validos);
            break;

        case 3:

            printf("\nIngrese edad a buscar: ");
            scanf("%d", &edad);
            filtrarPorEdad(nombreArchivo, edad, &vecIDs, &validos);
            menuGestionPerritos(nombreArchivo, vecIDs,  validos);
            break;

        case 4:

            printf("\n0 - CALMADO");
            printf("\n1 - JUGUETON");
            printf("\n2 - ANSIOSO");
            printf("\n3 - AGRESIVO");
            printf("\n4 - SOCIABLE");
            printf("\nSeleccione temperamento: ");
            scanf("%d", &temp);
            filtrarPorTemperamento(nombreArchivo, temp, &vecIDs,&validos);
            menuGestionPerritos(nombreArchivo, vecIDs, validos);
            break;

        case 0:

            menuEdicionPerritos(nombreArchivo);
            break;

        default:

            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 0);

    free(vecIDs);
}

void filtrarPorPorte(char nombreArchivo[],Porte porteBuscado, int **vecIDs,int *validos)
{
    int encontrado = 0;
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.porte == porteBuscado)
            {
                mostrarPerrito(aux);

                agregarID(vecIDs, validos, aux.idPerrito);

                encontrado = 1;
            }
        }

        fclose(pf);
    }

    if(!encontrado)
    {
        printf("\nNo se encontraron perritos con ese Porte.\n");
    }
}

void filtrarPorGenero(char nombreArchivo[],Genero generoBuscado, int **vecIDs, int *validos)
{
    int encontrado = 0;
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.genero == generoBuscado)
            {
                mostrarPerrito(aux);

                agregarID(vecIDs, validos, aux.idPerrito);

                encontrado = 1;
            }
        }

        fclose(pf);
    }

    if(!encontrado)
    {
        printf("\nNo se encontraron perritos con ese Genero.\n");
    }
}

void filtrarPorEdad(char nombreArchivo[],int edadBuscada, int **vecIDs,int *validos)
{
    int encontrado = 0;
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.edad == edadBuscada)
            {
                mostrarPerrito(aux);

                agregarID(vecIDs, validos, aux.idPerrito);

                encontrado = 1;
            }
        }

        fclose(pf);
    }

    if(!encontrado)
    {
        printf("\nNo se encontraron perritos con esa edad.\n");
    }
}

void filtrarPorTemperamento(char nombreArchivo[], Temperamento tempBuscado, int **vecIDs, int *validos)
{
    int encontrado = 0;
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            if(aux.temperamento == tempBuscado)
            {
                mostrarPerrito(aux);

                agregarID(vecIDs, validos, aux.idPerrito);

                encontrado = 1;
            }
        }

        fclose(pf);
    }

    if(!encontrado)
    {
        printf("\nNo se encontraron perritos con ese Temperamento.\n");
    }
}

void menuGestionPerritos(char nombreArchivo[], int vecIDs[], int validos)
{
    int opcion;
    int id;

    printf("+-----------------------------------------+");
    printf("\n| \t 1.- Modificar Perrito           |");
    printf("\n| \t 2.- Eliminar Perrito            |");
    printf("\n| \t 3.- Mejor me vuelvo             |");
    printf("\n+-----------------------------------------+");

    printf("\nElige la opcion correcta: ");
    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:

        printf("\nIngrese ID del perrito a modificar: ");

        do
        {
            scanf("%d", &id);

            if(!validarID(vecIDs, validos, id))
            {
                printf("\nID invalido.\n");
                printf("\nIngrese ID del perrito a modificar: ");
            }

        }
        while(!validarID(vecIDs, validos, id));

        modificarPerrito(nombreArchivo, id);
        break;

    case 2:

        printf("\nIngrese ID del perrito a eliminar: ");
        do
        {
            scanf("%d", &id);

            if(!validarID(vecIDs, validos, id))
            {
                printf("\nID invalido.\n");
                printf("\nIngrese ID del perrito a eliminar: ");
            }

        }
        while(!validarID(vecIDs, validos, id));
        eliminarPerrito(nombreArchivo, id);
        break;

    case 3:

        printf("\nVolviendo...\n\n");
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
                printf("\n");
                aux = cargarPerri();

                aux.idPerrito = idBuscado;

                fseek(pf, -sizeof(Perrito), SEEK_CUR);

                fwrite(&aux, sizeof(Perrito), 1, pf);

                printf("\nModificacion realizada correctamente\n");
            }
        }

        fclose(pf);

        if(!encontrado)
        {
            printf("\nNo existe un perrito con ese ID\n");
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
    menuPerritosGeneral(nombreArchivo);
}

void agregarID(int **vec, int *validos, int id)
{
    *vec = realloc(*vec, sizeof(int) * (*validos + 1));

    if(*vec != NULL)
    {
        (*vec)[*validos] = id;
        (*validos)++;
    }
}

int validarID(int vec[], int validos, int idBuscado)
{
    int i;

    for(i = 0; i < validos; i++)
    {
        if(vec[i] == idBuscado)
        {
            return 1;
        }
    }

    return 0;
}

void cargarTodosLosIDs(char nombreArchivo[],int **vecIDs, int *validos)
{
    Perrito aux;

    FILE *pf = fopen(nombreArchivo, "rb");

    if(pf)
    {
        while(fread(&aux, sizeof(Perrito), 1, pf) > 0)
        {
            agregarID(vecIDs, validos, aux.idPerrito);
        }

        fclose(pf);
    }
}
