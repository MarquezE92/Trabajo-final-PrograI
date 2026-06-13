#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    CHICO,
    MEDIANO,
    GRANDE
} Porte;

typedef enum
{
    DISPONIBLE,
    ADOPTADO
} Estado;

typedef enum
{
    CALMADO,
    JUGUETON,
    ANSIOSO,
    AGRESIVO,
    SOCIABLE
} Temperamento;

typedef enum
{
    MACHO,
    HEMBRA
} Genero;

typedef struct
{
    int idPerrito;
    char solicitante[35];
    char email[35];
    char tel[12];
} Solicitud;

typedef struct
{
    int idPerrito;
    char nombre[35];
    int edad;
    char raza[35];
    Porte porte;
    Estado estado;
    Temperamento temperamento;
    Genero genero;
    char fechaIngreso[10];
} Perrito;

typedef struct
{
    char fecha[10];
    char comentario[125]
} Observacion;

typedef struct
{
    int idPerrito;
    int idAdoptante;
    Observacion observaciones[6]; //??
} Adopcion;

typedef struct
{
    int idAdoptante;
    char nombre[35];
    char email[35];
    char tel[12];
    char direccion[35]
} Adoptante;

///prototipados
int mostrarMenuPrincipal();
void mostrarMenuAdmin();
void mostrarMenuAdoptante();

int main()
{
    system("color 0B");
    int opcion = mostrarMenuPrincipal();


    switch(opcion){
        case 0:
            printf("\n Nos vemos!!!");
            break;
        case 1:
            mostrarMenuAdmin();
            break;
        case 2:
            mostrarMenuAdoptante();
            break;
        case 3:
            printf("\nNo nos mienta\n");
            printf("\n");
            mostrarMenuPrincipal();
            break;
    }

    return 0;
}

///funciones
int mostrarMenuPrincipal(){
    int opcion;

    do{
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Soy Admin                    |");
        printf("\n| \t 2.- Quiero adoptar               |");
        printf("\n| \t 3.- Soy un perrito               |");
        printf("\n| \t 0.- Me arrepenti y me quiero ir  |");
        printf("\n+-----------------------------------------+");
        printf("\n Elige la opcion correcta: ");
        scanf("%i", &opcion);

        if(opcion > 3 && opcion < 0){
           printf("\n %i No es una opcion valida", opcion);
        }
    }while(opcion > 3 && opcion < 0);
    system("cls");
    return opcion;

}

void mostrarMenuAdmin(){
    printf("\n Muestro el menu del admin");
}

void mostrarMenuAdoptante(){
    printf("\n Muestro el menu del adoptante");
}

void cargarSolicitud(char nombreArchivo[]){
    Solicitud aux;
    FILE *pf= fopen(nombreArchivo,  "ab");
    if(pf == NULL){
        printf("\nNo se pudo abrir el archivo para cargar la solicitud");
    }else{
        aux = cargarSolicitudSimple();
        fwrite(&aux, sizeof(Solicitud),1, pf);
        fclose(pf);
    }
}

Solicitud cargarSolicitudSimple(){
    Solicitud aux;

    return aux;
}
