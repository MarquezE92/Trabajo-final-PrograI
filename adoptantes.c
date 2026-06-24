#include "adoptantes.h"

#include <stdio.h>
#include <unistd.h>
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
    }while(strlen((bufferTel))>= sizeof(aux.tel));
    strcpy(aux.tel, buffer);

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
    char letra='s';
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para cargar al adoptado");
    }else{
        aux = cargarAdoptanteSimple();
        fwrite(&aux, sizeof(Adoptante),1, pf);
        fclose(pf);
    }
}

void mostrarAdoptante(Adoptante adoptante){
    printf("\n--------------------------------\n");
    printf("\n ID: %i", adoptante.idAdoptante);
    printf("\nNombre: %s", adoptante.nombre);
    printf("\n e-mail: %s", adoptante.email);
    printf("\nTel: %s", adoptante.tel);
    printf("\n Direcion: %s", adoptante.direccion);
    printf("\n--------------------------------\n");
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
}

void eliminarAdoptante(char nombreArchivo[], int idAdoptante){
    Adoptante aux;
    int posicionAeliminar = buscarPosicionPorId(nombreArchivo, idAdoptante);

    FILE *pf= fopen(nombreArchivo,  "r+b");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para eliminar al adoptante");
    }else{
        fseek(pf, sizeof(Adoptante) * (posicionAeliminar + 1), SEEK_SET);
        while(fread(&aux, sizeof(Adoptante),1, pf)>0){
            fseek(pf, (-2)*sizeof(Adoptante), SEEK_CUR);
            fwrite(&aux, sizeof(Adoptante), 1, pf);
            fseek(pf, sizeof(Adoptante), SEEK_CUR);
        }
        fseek(pf, 0, SEEK_END);
        long tam_actual = ftell(pf);
        int fd = fileno(pf);
        ftruncate(fd, tam_actual - sizeof(Adoptante));
        fclose(pf);
    }
}

Adoptante modificarAdoptante(Adoptante adoptante){
    char opcion = 'n';
    char buffer[235], bufferTel[212];

    printf("\nDesea modificar el nombre de pila del adoptante? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do{
            printf("\nNuevo nombre: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.nombre)) || (strlen(buffer) < 3)){
                printf("\nError: El nombre excede la cantidad de caracteres permitidos.");
            }
        }while(strlen((buffer))>= sizeof(adoptante.nombre));
        strcpy(adoptante.nombre, buffer);


    }
    printf("\nDesea modificar el email del adoptante? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do{
            printf("\nNuevo email: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.email)) || (strlen(buffer) < 7)){
                printf("\nError: El email excede la cantidad de caracteres permitidos.");
            }
        }while(strlen((buffer))>= sizeof(adoptante.email));
        strcpy(adoptante.email, buffer);


    }

    printf("\nDesea modificar el telefono del adoptante? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do{
            printf("\nNuevo telefono: ");
            fgets(bufferTel, sizeof(bufferTel),stdin);
            if((strlen(bufferTel)>= sizeof(adoptante.tel)) || strlen(bufferTel) < 7){
                printf("\nError: El telefono no es valido.");
            }
        }while(strlen((bufferTel))>= sizeof(adoptante.tel));
        strcpy(adoptante.tel, bufferTel);


    }

    printf("\nDesea modificar la direccion del adoptante? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S')
    {
        do{
            printf("\nNueva direccion: ");
            fgets(buffer, sizeof(buffer),stdin);
            if((strlen(buffer)>= sizeof(adoptante.direccion)) || (strlen(buffer) < 3)){
                printf("\nError: Esta direccion no es valida.");
            }
        }while(strlen((buffer))>= sizeof(adoptante.direccion));
        strcpy(adoptante.direccion, buffer);


    }
    return adoptante;
}

void modificarRegistroAdoptante(char nombreArchivo[], int posicion){
    FILE *fp = fopen(nombreArchivo, "r+b");
    Adoptante aux;
    if(fp == NULL){
        printf("\n No se puedo abrir el archivo para modificar un registro");
    }else{
        fseek(fp, posicion * sizeof(Adoptante), SEEK_SET);
        if(fread(&aux, sizeof(Adoptante), 1, fp) != 1){
            printf("\n No se encontro el adoptante que se queria modificar");
        }else{
        aux = modificarAdoptante(aux);
        fseek(fp, posicion * sizeof(Adoptante), SEEK_SET);
        fwrite(&aux, sizeof(Adoptante), 1, fp);
        }
        fclose(fp);
    }
}

int obtenerIdAdoptante(){
    int id;
    Adoptante aux;
    FILE *fp = fopen(ARCHIVO_ADOPTANTES, "rb");
    if(fp == NULL){
        printf("\nNo se pudo acceder al archivo de Adoptantes para obetener el ID");
    }else{
        if(fread(&aux, sizeof(Adoptante), 1, fp) != 1){
            id = 1;
        }else{
        fseek(fp, -sizeof(Adoptante), SEEK_END);
        fread(&aux, sizeof(Adoptante), 1, fp);
        id = aux.idAdoptante + 1;
        }

        fclose(fp);
    }
    return id;
}

void menuAdoptante(){

}
