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
        printf("\n-----------------------------------------");

        do
        {
            printf("\nElija una opcion: ");

            if(scanf("%d", &opcion) != 1)
            {
                printf("\nDebe ingresar un numero.\n");

                while(getchar() != '\n');

                opcion = -1;
            }

            if(opcion < 0 || opcion > 4)
            {
                printf("\nOpcion invalida.\n");
            }

        }
        while(opcion < 0 || opcion > 4);

        system("cls");

        switch(opcion)
        {
        case 0:

            printf("\nGuau! digo Chau...\n");
            system("pause");
            system("cls");
            break;

        case 1:

            printf("\n--- LISTADO COMPLETO DE PERRITOS ---\n");

            mostrarListadoPerritosRecursivo(lista, validos, 0);

            do
            {
                printf("\nDesea ver el detalle de algun perrito? Ingrese el ID (0 para volver): ");

                if(scanf("%d", &idBuscar) != 1)
                {
                    printf("\nDebe ingresar un numero.\n");

                    while(getchar() != '\n');

                    idBuscar = -1;
                }

            }
            while(idBuscar < 0);

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

                if(!encontrado)
                {
                    printf("\nNo se encontro el ID ingresado.\n");
                }

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
        {
            char confirma;

            do
            {
                printf("\nIngrese el ID del perrito que desea adoptar: ");

                if(scanf("%d", &idBuscar) != 1)
                {
                    printf("\nDebe ingresar un numero.\n");

                    while(getchar() != '\n');

                    idBuscar = -1;
                }

                if(idBuscar <= 0)
                {
                    printf("\nEl ID debe ser mayor a 0.\n");
                }

            }
            while(idBuscar <= 0);

            encontrado = 0;

            for(int i = 0; i < validos; i++)
            {
                if(lista[i].idPerrito == idBuscar)
                {
                    encontrado = 1;

                    if(lista[i].estado == DISPONIBLE)
                    {
                        printf("\nPerrito seleccionado:\n");

                        mostrarUnPerrito(lista[i]);

                        printf("\nConfirma la solicitud? (s/n): ");
                        scanf(" %c", &confirma);

                        if(confirma == 's' || confirma == 'S')
                        {
                            cargarSolicitud(archivoSolicitudes, idBuscar);

                            lista[i].estado = ADOPTADO;

                            printf("\nSolicitud registrada correctamente.\n");
                        }
                        else
                        {
                            printf("\nOperacion cancelada.\n");
                        }
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
        }

        case 4:

            mostrarInfoContacto();

            system("pause");
            system("cls");

            break;

        default:

            printf("\nOpcion invalida.\n");

            system("pause");
            system("cls");
        }

    }
    while(opcion != 0);
}

void cargarSolicitud(char nombreArchivo[], int id)
{
    Solicitud aux;
    Solicitud control;
    int existe = 0;

    FILE *pf = fopen(nombreArchivo, "rb");
    aux = cargarSolicitudSimple(id);

    if(pf)
    {
        while(fread(&control, sizeof(Solicitud), 1, pf) > 0)
        {
            if(control.idPerrito == aux.idPerrito)
            {
                existe = 1;
            }
        }

        fclose(pf);
    }
    if(existe)
    {
        printf("\nYa existe una solicitud para ese perrito.\n");
    }
    else
    {
        pf = fopen(nombreArchivo, "ab");
        if(pf == NULL)
        {
            printf("\nNo se pudo abrir el archivo para cargar la solicitud.\n");
        }
        else
        {
            fwrite(&aux, sizeof(Solicitud), 1, pf);
            fclose(pf);
            printf("\nSolicitud cargada correctamente.\n");
        }
    }
}

Solicitud cargarSolicitudSimple(int id)
{
    Solicitud aux;
    char buffer[100];

    /*do
    {
        printf("Cargue el ID del perrito: ");

        if(scanf("%d", &aux.idPerrito) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            aux.idPerrito = -1;
        }

        if(aux.idPerrito <= 0)
        {
            printf("\nEl ID debe ser mayor a 0.\n");
        }

    }while(aux.idPerrito <= 0);*/

    aux.idPerrito=id;

    while(getchar() != '\n');

    do
    {
        printf("Cargue nombre del solicitante: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if(strlen(buffer) < 2 || strlen(buffer) > 34)
        {
            printf("\nError: El nombre debe tener entre 2 y 34 caracteres.\n");
            }

    }while(strlen(buffer) < 2 || strlen(buffer) > 34);

    strcpy(aux.solicitante, buffer);

    do
    {
        printf("Ingrese su email: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if(strlen(buffer) < 5 || strlen(buffer) > 34)
        {
            printf("\nError: El email debe tener entre 5 y 34 caracteres.\n");
        }

    }while(strlen(buffer) < 5 || strlen(buffer) > 34);

    strcpy(aux.email, buffer);

    do
    {
        printf("Ingrese su telefono: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if(strlen(buffer) < 6 || strlen(buffer) > 19)
        {
            printf("\nError: El telefono debe tener entre 6 y 19 caracteres.\n");
        }

    }while(strlen(buffer) < 6 || strlen(buffer) > 19);

    strcpy(aux.tel, buffer);

    return aux;
}

Perrito cargarPerrito()
{
    Perrito aux;
    int op;
    char buffer[100];

    do
    {
        printf("Cargue el ID del perrito: ");

        if(scanf("%d", &aux.idPerrito) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            aux.idPerrito = -1;
        }

    }while(aux.idPerrito <= 0);

    do
    {
        printf("Cargue la edad del perrito (0-30): ");

        if(scanf("%d", &aux.edad) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            aux.edad = -1;
        }

        if(aux.edad < 0 || aux.edad > 30)
        {
            printf("\nEdad invalida.\n");
        }

    }while(aux.edad < 0 || aux.edad > 30);

    while(getchar() != '\n');

    do
    {
        printf("Cargue el nombre del perrito: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if(strlen(buffer) < 2 || strlen(buffer) > 34)
        {
            printf("\nError: El nombre no es valido.\n");
        }

    }while(strlen(buffer) < 2 || strlen(buffer) > 34);

    strcpy(aux.nombre, buffer);

    do
    {
        printf("Cargue la raza del perrito: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        if(strlen(buffer) < 2 || strlen(buffer) > 34)
        {
            printf("\nError: La raza no es valida.\n");
        }

    }while(strlen(buffer) < 2 || strlen(buffer) > 34);

    strcpy(aux.raza, buffer);

    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);

    sprintf(aux.fechaIngreso,
            "%02d/%02d/%04d",
            fecha->tm_mday,
            fecha->tm_mon + 1,
            fecha->tm_year + 1900);

    do
    {
        printf("Seleccione el porte:\n");
        printf("0-Chico\n1-Mediano\n2-Grande\n");

        if(scanf("%d", &op) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            op = -1;
        }

    }while(op < 0 || op > 2);

    aux.porte = op;

    do
    {
        printf("Seleccione el genero:\n");
        printf("0-Macho\n1-Hembra\n");

        if(scanf("%d", &op) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            op = -1;
        }

    }while(op < 0 || op > 1);

    aux.genero = op;

    do
    {
        printf("Seleccione el temperamento:\n");
        printf("0-Calmado\n");
        printf("1-Jugueton\n");
        printf("2-Ansioso\n");
        printf("3-Agresivo\n");
        printf("4-Sociable\n");

        if(scanf("%d", &op) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            op = -1;
        }

    }while(op < 0 || op > 4);

    aux.temperamento = op;

    aux.estado = DISPONIBLE;

    return aux;
}

void mostrarUnPerrito(Perrito perri)
{
    printf("\n---------------------------------");
    printf("\n     FICHA DEL PERRITO");
    printf("\n---------------------------------");

    printf("\nID            : %d", perri.idPerrito);
    printf("\nNombre        : %s", perri.nombre);
    printf("\nEdad          : %d anos", perri.edad);
    printf("\nRaza          : %s", perri.raza);
    if(perri.genero >= 0 && perri.genero <= 1)
        printf("\nGenero        : %s", generoTexto[perri.genero]);
    else
        printf("\nGenero        : DESCONOCIDO");
    if(perri.porte >= 0 && perri.porte <= 2)
        printf("\nPorte         : %s", porteTexto[perri.porte]);
    else
        printf("\nPorte         : DESCONOCIDO");
    if(perri.temperamento >= 0 && perri.temperamento <= 4)
        printf("\nTemperamento  : %s", temperamentoTexto[perri.temperamento]);
    else
        printf("\nTemperamento  : DESCONOCIDO");
    if(perri.estado >= 0 && perri.estado <= 1)
        printf("\nEstado        : %s", estadoTexto[perri.estado]);
    else
        printf("\nEstado        : DESCONOCIDO");
    printf("\nFecha ingreso : %s", perri.fechaIngreso);
    printf("\n---------------------------------\n");
}

void mostrarListadoPerritosRecursivo(Perrito lista[], int validos, int i)
{
    if(i < validos)
    {
        printf("\n[%d] ID: %d",
               i + 1,
               lista[i].idPerrito);
        printf(" | Nombre: %s",
               lista[i].nombre);
        if(lista[i].genero >= 0 && lista[i].genero <= 1)
        {
            printf(" | %s",
                   generoTexto[lista[i].genero]);
        }
        else
        {
            printf(" | GENERO DESCONOCIDO");
        }

        if(lista[i].porte >= 0 && lista[i].porte <= 2)
        {
            printf(" | %s",
                   porteTexto[lista[i].porte]);
        }
        else
        {
            printf(" | PORTE DESCONOCIDO");
        }

        if(lista[i].estado == DISPONIBLE)
        {
            printf(" | DISPONIBLE");
        }
        else
        {
            printf(" | ADOPTADO");
        }

        printf("\n");

        mostrarListadoPerritosRecursivo(lista, validos, i + 1);
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
        printf("1. Por Edad\n");
        printf("2. Por Temperamento\n");
        printf("3. Por Genero\n");
        printf("4. Por Porte\n");
        printf("Elija criterio: ");

        if(scanf("%d", &opcion) != 1)
        {
            printf("\nDebe ingresar un numero.\n");

            while(getchar() != '\n');

            opcion = -1;
        }

        if(opcion < 1 || opcion > 4)
        {
            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion < 1 || opcion > 4);

    switch(opcion)
    {
    case 1:

        do
        {
            printf("\nIngrese la edad exacta a buscar (0-30): ");

            if(scanf("%d", &criterio) != 1)
            {
                printf("\nDebe ingresar un numero.\n");

                while(getchar() != '\n');

                criterio = -1;
            }

            if(criterio < 0 || criterio > 30)
            {
                printf("\nEdad invalida.\n");
            }

        }
        while(criterio < 0 || criterio > 30);

        for(i = 0; i < validos; i++)
        {
            if(lista[i].edad == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
        }

        break;

    case 2:
        do
        {
            printf("\nSeleccione Temperamento:\n");
            printf("0-Calmado\n");
            printf("1-Jugueton\n");
            printf("2-Ansioso\n");
            printf("3-Agresivo\n");
            printf("4-Sociable\n");
            printf("Opcion: ");

            if(scanf("%d", &criterio) != 1)
            {
                printf("\nDebe ingresar un numero.\n");

                while(getchar() != '\n');

                criterio = -1;
            }

            if(criterio < 0 || criterio > 4)
            {
                printf("\nOpcion invalida.\n");
            }

        }
        while(criterio < 0 || criterio > 4);

        for(i = 0; i < validos; i++)
        {
            if(lista[i].temperamento == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
        }

        break;

    case 3:
        do
        {
            printf("\nSeleccione Genero:\n");
            printf("0-Macho\n");
            printf("1-Hembra\n");
            printf("Opcion: ");

            if(scanf("%d", &criterio) != 1)
            {
                printf("\nDebe ingresar un numero.\n");

                while(getchar() != '\n');

                criterio = -1;
            }

            if(criterio < 0 || criterio > 1)
            {
                printf("\nOpcion invalida.\n");
            }

        }
        while(criterio < 0 || criterio > 1);

        for(i = 0; i < validos; i++)
        {
            if(lista[i].genero == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
        }

        break;

    case 4:
        do
        {
            printf("\nSeleccione Porte:\n");
            printf("0-Chico\n");
            printf("1-Mediano\n");
            printf("2-Grande\n");
            printf("Opcion: ");

            if(scanf("%d", &criterio) != 1)
            {
                printf("\nDebe ingresar un numero.\n");

                while(getchar() != '\n');

                criterio = -1;
            }

            if(criterio < 0 || criterio > 2)
            {
                printf("\nOpcion invalida.\n");
            }

        }
        while(criterio < 0 || criterio > 2);

        for(i = 0; i < validos; i++)
        {
            if(lista[i].porte == criterio)
            {
                mostrarUnPerrito(lista[i]);
                encontrados++;
            }
        }
        break;
    }
    if(encontrados == 0)
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
