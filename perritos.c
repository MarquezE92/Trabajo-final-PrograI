#include <stdio.h>
#include <stdlib.h>
#include "perritos.h"
#include "menuGeneral.h"
#include <time.h>
#include <string.h>


void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[])
{
    int opcion;
    int idBuscar;
    int encontrado;

    do
    {
        printf("\n-----------------------------------------");
        printf("\n|            MENU ADOPTANTE             |");
        printf("\n-----------------------------------------");
        printf("\n| 1.- Ver listado de perritos (Todos)   |");
        printf("\n| 2.- Aplicar filtro                    |");
        printf("\n| 3.- Solicitar adopcion                |");
        printf("\n| 4.- Ver informacion de contacto       |");
        printf("\n| 0.- Volver al Menu Principal          |");
        printf("\n-----------------------------------------\n");
        printf("\n Elija una opcion: ");
        scanf("%i", &opcion);
        system("cls");

        switch(opcion)
        {

        case 0:

            printf("\nGuau! digo Chau...\n");
            system("pause");
            system("cls");
            ///volver menu principal
            break;
        case 1:
            printf("\n--- LISTADO COMPLETO DE PERRITOS ---");
            mostrarListadoPerritosRecursivo(lista, validos, 0);

            printf("\n Desea ver el detalle de algun perrito? Ingrese el ID (0 para volver):\n");
            scanf("%i", &idBuscar);
            if(idBuscar != 0)
            {
                encontrado = 0;
                for(int i = 0; i < validos; i++)
                {
                    if(lista[i].idPerrito == idBuscar)
                    {
                        mostrarUnPerrito(lista[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado) printf("\nNo se encontro el ID ingresado.\n");
                system("pause");
                system("cls");
            }
            break;

        case 2:
            filtrarPerritos(lista, validos);
            system("pause");
            system("cls");
            break;

        case 3:
            printf("\nIngrese el ID del perrito que desea adoptar: ");
            scanf("%i", &idBuscar);
            encontrado = 0;
            for(int i = 0; i < validos; i++)
            {
                if(lista[i].idPerrito == idBuscar)
                {
                    encontrado = 1;
                    if(lista[i].estado == DISPONIBLE)
                    {
                        cargarSolicitud(archivoSolicitudes);
                        lista[i].estado = ADOPTADO;
                    }
                    else
                    {
                        printf("\nLo sentimos, este perrito ya fue adoptado.\n");
                    }
                    break;
                }
            }
            if(!encontrado)
            {
                printf("\nNo existe ningun perrito con ese ID.\n");
            }

            system("pause");
            system("cls");
            break;

        case 4:
            mostrarInfoContacto();
            system("pause");
            system("cls");
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


void cargarSolicitud(char nombreArchivo[])
{
    Solicitud aux;
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL)
    {
        printf("\nNo se pudo abrir el archivo para cargar la solicitud");
    }
    else
    {
        aux = cargarSolicitudSimple();
        fwrite(&aux, sizeof(Solicitud),1, pf);
        fclose(pf);
    }
}

Solicitud cargarSolicitudSimple()
{
    Solicitud aux;
    char buffer[100];

///Agregar validaciones
    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);

    /// nombre solicitante
    do
    {
        printf("Cargue nombre del solicitante: ");
        fgets(buffer, sizeof(buffer), stdin);
        if((strlen(buffer) >= 35) || (strlen(buffer) < 2))
        {
            printf("\nError: El nombre no es valido.");
        }
    }
    while(strlen(buffer) >= 35);
    strcpy(aux.solicitante, buffer);

    ///email

    do
    {
        printf("Ingrese su email: ");
        fgets(buffer, sizeof(buffer), stdin);
        if((strlen(buffer) >= 35) || (strlen(buffer) < 5))
        {
            printf("\nError: El email no es valido.");
        }
    }
    while(strlen(buffer) >= 35);
    strcpy(aux.email, buffer);
    ///telefono

    do
    {
        printf("Ingrese su Telefono: ");
        fgets(buffer, sizeof(buffer), stdin);
        if((strlen(buffer) >= 20) || (strlen(buffer) < 6))
        {
            printf("\nError: El telefono no es valido.");
        }
    }
    while(strlen(buffer) >= 20);
    strcpy(aux.tel, buffer);

    return aux;
}

Perrito cargarPerrito()
{
    Perrito aux;
    int op;
    char buffer[100];

    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);

    ///edad
    do
    {
        printf("Cargue la edad del perrito (0-30): ");
        scanf("%d", &aux.edad);

        if (aux.edad < 0 || aux.edad > 30)
        {
            printf("Edad inválida. Por favor, ingrese un rango coherente.\n");
        }
    }
    while (aux.edad < 0 || aux.edad > 30);

    ///nombre
    do
    {
        printf("Cargue el nombre del perrito: ");
        fgets(buffer, sizeof(buffer), stdin);
        if((strlen(buffer) >= 35) || (strlen(buffer) < 2))
        {
            printf("\nError: El nombre no es valido.");
        }
    }
    while(strlen(buffer) >= 35);
    strcpy(aux.nombre, buffer);
    ///raza
    do
    {
        printf("Cargue la raza del perrito: ");
        fgets(buffer, sizeof(buffer), stdin);
        if((strlen(buffer) >= 35) || (strlen(buffer) < 2))
        {
            printf("\nError: La raza no es valida.");
        }
    }
    while(strlen(buffer) >= 35);
    strcpy(aux.raza, buffer);

    ///ingreso
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

void mostrarUnPerrito(Perrito perri)
{
    printf("\n---------------------------------\n");
    printf("\n  Ficha del perrito id %i", perri.idPerrito);
    printf("\n---------------------------------\n");
    printf("\n Nombre:%s\n", perri.nombre);
    printf("\n Edad:%i anos\n", perri.edad);
    printf("\n Raza:%s\n", perri.raza);
    printf("\n Genero:%s\n", generoTexto[perri.genero]);
    printf("\n Porte:%s\n", porteTexto[perri.porte]);
    printf("\n Temperamento:%s\n",temperamentoTexto[perri.temperamento]);
    printf("\n Estado:%s\n", estadoTexto[perri.estado]);
    printf("\n Ingreso:%s\n", perri.fechaIngreso);
    printf("\n---------------------------------\n");
}

void mostrarListadoPerritosRecursivo(Perrito lista[], int valido, int i)
{

    if (i < valido)
    {
        printf("\n[%i] ID: %i -%s %s, %s\n",
               i + 1,
               lista[i].idPerrito,
               lista[i].nombre,
               generoTexto[lista[i].genero],
               porteTexto[lista[i].porte]);

        mostrarListadoPerritosRecursivo(lista, valido, i + 1);
    }

}

void filtrarPerritos(Perrito lista[], int validos)
{
    int opcion;
    int criterio;
    int i;
    int encontrados = 0;

    do
    {
        printf("\n--- APLICAR FILTRO ---\n");
        printf("1. Por Edad\n2. Por Temperamento\n3. Por Genero\n4. Por Porte\nElija criterio: ");

        opcion = -1;
        scanf("%i", &opcion);

        if (opcion < 1 || opcion > 4)
        {
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    }
    while (opcion < 1 || opcion > 4);

    switch(opcion)
    {
    case 1:
        do
        {
            printf("\nIngrese la edad exacta a buscar (0-30): ");
            criterio = -1;
            scanf("%i", &criterio);
            getchar();

            if (criterio < 0 || criterio > 30)
            {
                printf("Edad invalida. Intente de nuevo.\n");
            }
        }
        while (criterio < 0 || criterio > 30);

        i = 0;
        while (i < validos)
        {
            if (lista[i].edad == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
            i++;
        }
        break;

    case 2:
        do
        {
            printf("\nSeleccione (0-Calmado, 1-Jugueton, 2-Ansioso, 3-Agresivo, 4-Sociable): ");
            criterio = -1;
            scanf("%i", &criterio);
            getchar();
            if (criterio < 0 || criterio > 4)
            {
                printf("Criterio invalido. Intente de nuevo.\n");
            }
        }
        while (criterio < 0 || criterio > 4);

        i = 0;
        while (i < validos)
        {
            if (lista[i].temperamento == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
            i++;
        }
        break;

    case 3:
        do
        {
            printf("\nSeleccione (0-Macho, 1-Hembra): ");
            criterio = -1;
            scanf("%i", &criterio);

            if (criterio < 0 || criterio > 1)
            {
                printf("Criterio invalido. Intente de nuevo.\n");
            }
        }
        while (criterio < 0 || criterio > 1);

        i = 0;
        while (i < validos)
        {
            if (lista[i].genero == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
            i++;
        }
        break;

    case 4:
        do
        {
            printf("\nSeleccione (0-Chico, 1-Mediano, 2-Grande): ");
            criterio = -1;
            scanf("%i", &criterio);

            if (criterio < 0 || criterio > 2)
            {
                printf("Criterio invalido. Intente de nuevo.\n");
            }
        }
        while (criterio < 0 || criterio > 2);

        i = 0;
        while (i < validos)
        {
            if (lista[i].porte == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
            i++;
        }
        break;
    }

    if (encontrados == 0)
    {
        printf("\nNo se encontraron perritos con el criterio seleccionado.\n");
    }
}

void mostrarInfoContacto()
{
    system("cls");
    printf("\n--------------------------------------------+");
    printf("\n|     INFORMACION DE CONTACTO               |");
    printf("\n--------------------------------------------");
    printf("\n| Direccion: Buque Pesquero Dorrego Nro 281 |");
    printf("\n| Telefono: (0223) 480-1220                 |");
    printf("\n| Email: perriAdopciones@mdp.utn.edu.ar     |");
    printf("\n--------------------------------------------\n");
}
