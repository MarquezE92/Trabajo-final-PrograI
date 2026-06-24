#include "adoptantes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Adoptante cargarAdoptanteSimple()
{
    Adoptante aux;
    char buffer[235],bufferTel[212];

    aux.idAdoptante = obtenerIdAdoptante();

    do{
        printf("\nCargue el nombre de pila del adoptante: ");
        fgets(buffer, sizeof(buffer),stdin);
        if((strlen((buffer))>= sizeof(aux.nombre))){
            printf("\nError: El nombre excede la cantidad de caracteres permitidos.");
        }
    }while(strlen((buffer))>= sizeof(aux.nombre));
    strcpy(aux.nombre, buffer);

    do{
        printf("\nCargue el email del adoptante: ");
        fgets(buffer, sizeof(buffer),stdin);
        if((strlen((buffer))>= sizeof(aux.email))){
            printf("\nError: El email excede la cantidad de caracteres permitidos.");
        }
    }while(strlen((buffer))>= sizeof(aux.email));
    strcpy(aux.email, buffer);

    do{
        printf("\nCargue el telefono del adoptante: ");
        fgets(bufferTel, sizeof(bufferTel),stdin);
        if((strlen(bufferTel)>= sizeof(aux.tel)) || strlen(bufferTel) < 7){
            printf("\nError: El telefono no es valido.");
        }
    }while((strlen(bufferTel)>= sizeof(aux.tel)) || strlen(bufferTel) < 7);
    strcpy(aux.tel, bufferTel);

    do{
        printf("\nCargue la direccion del adoptante: ");
        fgets(buffer, sizeof(buffer),stdin);
        if((strlen((buffer))>= sizeof(aux.direccion))){
            printf("\nError: La direccion excede la cantidad de caracteres permitidos.");
        }
    }while(strlen((buffer))>= sizeof(aux.direccion));
    strcpy(aux.direccion, buffer);

    return aux;
}

void cargarAdoptante(char nombreArchivo[]){
    Adoptante aux;
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para cargar al adoptado");
    }else{
        aux = cargarAdoptanteSimple();
        fwrite(&aux, sizeof(Adoptante),1, pf);
        printf("\n Adoptante registrado exitosamente!");
        printf("\n");
        mostrarAdoptante(aux);
        fclose(pf);
    }
}

void mostrarAdoptante(Adoptante adoptante){
    printf("\n--------------------------------\n");
    printf("\tID: %i", adoptante.idAdoptante);
    printf("\n--------------------------------\n");
    printf("\nNombre: %s", adoptante.nombre);
    printf("\ne-mail: %s", adoptante.email);
    printf("\nTel: %s", adoptante.tel);
    printf("\nDirecion: %s", adoptante.direccion);
    printf("\n.................................\n");
}

void mostrarTodosAdoptantes(char nombreArchivo[]){
    Adoptante aux;
    FILE *pf= fopen(nombreArchivo,  "rb");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para mostrar a los adoptantes");
    }else{
        while(fread(&aux, sizeof(Adoptante),1, pf)>0){
            mostrarAdoptante(aux);
        }
        fclose(pf);
    }
}

void mostrarAdoptantePorId(char nombreArchivo[], int id){
    Adoptante aux;
    int encontrado = 0;
    FILE *pf= fopen(nombreArchivo,  "rb");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para mostrar al adoptante");
    }else{
        while(fread(&aux, sizeof(Adoptante),1, pf)>0 && !encontrado){
            if(aux.idAdoptante == id){
                mostrarAdoptante(aux);
                encontrado = 1;
            }
        };
        fclose(pf);
    }
}

int buscarPosicionPorId(char nombreArchivo[], int idAdoptante){
    Adoptante aux;
    int pos=0, encontrado = 0, resultado = -1;
    FILE *pf= fopen(nombreArchivo,  "rb");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para buscar al adoptante");
    }else{
        while(fread(&aux, sizeof(Adoptante),1, pf)>0 && !encontrado){
            if(aux.idAdoptante == idAdoptante){
                resultado = pos;
                encontrado = 1;
            }
            pos++;
        };
        fclose(pf);
    }
    return resultado;
}

void eliminarAdoptante(char nombreArchivo[], int idAdoptante){
    system("cls");
    Adoptante aux;
    int encontrado = 0;

    FILE *archivo = fopen(nombreArchivo, "rb");
    FILE *auxiliar = fopen("aux_adoptantes.dat", "wb");

    if(archivo == NULL || auxiliar == NULL)
    {
        printf("\nError al abrir archivos");
    }
    else
    {
        while(fread(&aux, sizeof(Adoptante), 1, archivo) > 0)
        {
            if(aux.idAdoptante == idAdoptante)
            {
                encontrado = 1;
                printf("\nAdoptante encontrado:");
                mostrarAdoptante(aux);
            }
            else
            {
                fwrite(&aux, sizeof(Adoptante), 1, auxiliar);
            }
        }

        fclose(archivo);
        fclose(auxiliar);

        if(encontrado)
        {
            remove(nombreArchivo);
            rename("aux_adoptantes.dat", nombreArchivo);
            printf("\nSe retiro al adoptante seleccionado del registro \n");
        }
        else
        {
            remove("aux_adoptantes.dat");
            printf("\nNo se encontro el adoptante con ID %d\n", idAdoptante);
        }
    }

}

Adoptante modificarAdoptante(Adoptante adoptante){
    char opcion = 'n';
    char buffer[235], bufferTel[212];

    do{
        printf("\nDesea modificar el nombre de pila del adoptante? (s/n): ");
       if(scanf(" %c", &opcion) !=1 || (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' ))
        {
                printf("\nDebe ingresar una opcion valida (S o N)\n");
                while (getchar() != '\n');
                opcion = 'w';
        }

    }while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' );


    if (opcion == 's' || opcion == 'S')
    {
        while (getchar() != '\n');
        do{
            printf("\nNuevo nombre: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.nombre)) || (strlen(buffer) < 3)){
                printf("\nError: El nombre no es valido.");
            }
        }while((strlen(buffer)>= sizeof(adoptante.nombre)) || (strlen(buffer) < 3));
        strcpy(adoptante.nombre, buffer);


    }

    do{
        printf("\nDesea modificar el email del adoptante? (s/n): ");
       if(scanf(" %c", &opcion) !=1 || (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' ))
        {
                printf("\nDebe ingresar una opcion valida (S o N)\n");
                while (getchar() != '\n');
                opcion = 'w';
        }

    }while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' );


    if (opcion == 's' || opcion == 'S')
    {
        while (getchar() != '\n');
        do{
            printf("\nNuevo email: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.email)) || (strlen(buffer) < 7)){
                printf("\nError: El email no es valido.");
            }
        }while((strlen(buffer)>= sizeof(adoptante.email)) || (strlen(buffer) < 7));
        strcpy(adoptante.email, buffer);

    }

    do{
        printf("\nDesea modificar el telefono del adoptante? (s/n): ");
       if(scanf(" %c", &opcion) !=1 || (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' ))
        {
                printf("\nDebe ingresar una opcion valida (S o N)\n");
                while (getchar() != '\n');
                opcion = 'w';
        }

    }while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' );


    if (opcion == 's' || opcion == 'S')
    {
        while (getchar() != '\n');
        do{
            printf("\nNuevo telefono: ");
            fgets(bufferTel, sizeof(bufferTel),stdin);
            if((strlen(bufferTel)>= sizeof(adoptante.tel)) || strlen(bufferTel) < 7){
                printf("\nError: El telefono no es valido.");
            }
        }while((strlen(bufferTel)>= sizeof(adoptante.tel)) || strlen(bufferTel) < 7);
        strcpy(adoptante.tel, bufferTel);
    }

    do{
       printf("\nDesea modificar la direccion del adoptante? (s/n): ");
       if(scanf(" %c", &opcion) !=1 || (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' ))
        {
                printf("\nDebe ingresar una opcion valida (S o N)\n");
                while (getchar() != '\n');
                opcion = 'w';
        }

    }while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' );

    if (opcion == 's' || opcion == 'S')
    {
        while (getchar() != '\n');
        do{
            printf("\nNueva direccion: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.direccion)) || (strlen(buffer) < 3)){
                printf("\nError: Esta direccion no es valida.");
            }
        }while((strlen(buffer)>= sizeof(adoptante.direccion)) || (strlen(buffer) < 3));
        strcpy(adoptante.direccion, buffer);


    }
    return adoptante;
}

void modificarRegistroAdoptante(char nombreArchivo[], int posicion){
    FILE *fp = fopen(nombreArchivo, "r+b");
    Adoptante aux;
    if(fp == NULL){
        printf("\n No se puedo abrir el archivo para modificar un registro\n");
    }else{
        fseek(fp, posicion * sizeof(Adoptante), SEEK_SET);
        if(fread(&aux, sizeof(Adoptante), 1, fp) != 1){
            printf("\n No se encontro el adoptante que se queria modificar\n");
        }else{
        aux = modificarAdoptante(aux);
        fseek(fp, posicion * sizeof(Adoptante), SEEK_SET);
        fwrite(&aux, sizeof(Adoptante), 1, fp);
        system("cls");
        mostrarAdoptante(aux);
        }
        fclose(fp);
    }
}

int obtenerIdAdoptante()
{
    int mayorId = 0;
    Adoptante aux;

    FILE *fp = fopen(ARCHIVO_ADOPTANTES, "rb");

    if(fp)
    {
        while(fread(&aux, sizeof(Adoptante), 1, fp) > 0)
        {
            if(aux.idAdoptante > mayorId)
            {
                mayorId = aux.idAdoptante;
            }
        }

        fclose(fp);
    }

    return ++mayorId;
}

void menuAdoptante(){
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Cargar Adoptante             |");
        printf("\n| \t 2.- Mostrar Adoptantes           |");
        printf("\n| \t 0.- Salir                        |");
        printf("\n+-----------------------------------------+");

        printf("\nElige la opcion correcta: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1:
            getchar();
            cargarAdoptante(ARCHIVO_ADOPTANTES);
            break;

        case 2:
            if(ordenarArchivoAdoptantes(ARCHIVO_ADOPTANTES) > 0){
               mostrarTodosAdoptantes(ARCHIVO_ADOPTANTES);
               menuSeleccionAdoptante();
            }else{
                printf("\nAun no tienes adoptantes registrados\n");
            }
            break;

        case 0:
            printf("\nGuau! digo, Chau...\n");
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

void menuSeleccionAdoptante(){
    char opcion = 's';
    int idAdoptante, seleccion;

    do{
       printf("\nDeseas seleccionar un adoptante? s/n: ");
       if(scanf(" %c", &opcion) !=1 || (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' ))
        {
                printf("\nDebe ingresar una opcion valida (S o N)\n");
                while (getchar() != '\n');
                opcion = 'w';
        }

    }while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N' );

    if(opcion == 's'){

        printf("\nIngrese el ID del adoptante que desea seleccionar: ");
        scanf("%i", &idAdoptante);
        system("cls");
        int posicion = buscarPosicionPorId(ARCHIVO_ADOPTANTES, idAdoptante);
        if(posicion < 0){
            printf("\nNo pudo encontrarse un Adoptante con ese ID\n");
        } else{
            printf("Usted ha seleccionado a: \n\n");
            mostrarAdoptantePorId(ARCHIVO_ADOPTANTES, idAdoptante);
            do{
                printf("+-------------------------------------------------------------\n");
                printf("| .-Si desea modificar el perfil del adoptante, presione 1   |\n");
                printf("| .-Si desea eliminar el perfil del adoptante, presione 2    |\n");
                printf("| .-Para salir, presione 0                                   |\n");
                printf("+-------------------------------------------------------------\n");
                scanf("%i", &seleccion);
                if(seleccion >2 || seleccion<0){
                    printf("\n Esa no es una opcion valida, recuerde:\n");
                }
            }while(seleccion >2 || seleccion<0);

            switch(seleccion)
            {
            case 1:
                modificarRegistroAdoptante(ARCHIVO_ADOPTANTES, posicion);
                break;

            case 2:
                eliminarAdoptante(ARCHIVO_ADOPTANTES, idAdoptante);
                break;

            case 0:
                printf("\nGuau! digo, Chau...\n");
                ///volver
                break;

            default:
                printf("\nNo sabemos que hizo, deberia ser imposible que lea esto\n");
                system("pause");
                system("cls");
                getchar();
            }
        }

    }
}

int buscarMenorAdoptante(Adoptante lista[], int inicio, int validos)
{
    int posMenor = inicio;
    int i;

    for(i = inicio + 1; i < validos; i++)
    {
        if(strcmp(lista[i].nombre, lista[posMenor].nombre) < 0)
        {
            posMenor = i;
        }
    }

    return posMenor;
}

void intercambiarAdoptantes(Adoptante lista[], int pos1, int pos2)
{
    Adoptante aux;

    aux = lista[pos1];
    lista[pos1] = lista[pos2];
    lista[pos2] = aux;
}

void ordenamientoSeleccionAdoptantes(Adoptante lista[], int validos)
{
    int i;
    int posMenor;

    for(i = 0; i < validos - 1; i++)
    {
        posMenor = buscarMenorAdoptante(lista, i, validos);

        intercambiarAdoptantes(lista, i, posMenor);
    }
}

int ordenarArchivoAdoptantes(char archAdoptantes[])
{
    Adoptante lista[100];
    int validos = 0, existeArchivo = 1;

    FILE *pf = fopen(archAdoptantes, "rb");

    if(pf)
    {
        while(fread(&lista[validos], sizeof(Adoptante), 1, pf) > 0)
        {
            validos++;
        }

        fclose(pf);

        ordenamientoSeleccionAdoptantes(lista, validos);

        pf = fopen(archAdoptantes, "wb");

        if(pf)
        {
            fwrite(lista, sizeof(Adoptante), validos, pf);

            fclose(pf);

            printf("\nArchivo ordenado por nombre.\n");
        }
    }else{
        existeArchivo = -1;
    }
    return existeArchivo;
}
