#include "adoptantes.h"

Adoptante cargarAdoptanteSimple()
{
    Adoptante aux;

    printf("Cargue el ID del adoptante: ");
    scanf("%d", &aux.idAdoptante);
    fflush(stdin);
    printf("Cargue nombre del adoptante: ");
    gets(aux.nombre);

    printf("Ingrese su email: ");
    gets(aux.email);

    printf("Ingrese su Telefono: ");
    gets(aux.tel);

    printf("Ingrese su Direccion: ");
    gets(aux.direccion);

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
        };
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
