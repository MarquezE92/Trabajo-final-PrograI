#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perritos.h"



const char ARCHIVO_PERRITOS[] = "perrito.bin";

//const char ARCHIVO_ADOPTANTES[] = "adoptantes.bin";

typedef struct
{
    int idPerrito;
    char solicitante[35];
    char email[35];
    char tel[12];
} Solicitud;



typedef struct
{
    char fecha[10];
    char comentario[125];
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
    char direccion[35];
} Adoptante;


///prototipados
int mostrarMenuPrincipal();
void mostrarMenuAdmin();
void mostrarMenuAdoptante();
void cargarSolicitud(char nombreArchivo[]);
Solicitud cargarSolicitudSimple();


int main()
{
    system("color 0B");

menuPerritosGeneral(ARCHIVO_PERRITOS);




    return 0;
}

///funciones
int mostrarMenuPrincipal()
{
    int opcion;

    do
    {
        printf("+-----------------------------------------+");
        printf("\n| \t 1.- Soy Admin                    |");
        printf("\n| \t 2.- Quiero adoptar               |");
        printf("\n| \t 3.- Soy un perrito               |");
        printf("\n| \t 0.- Me arrepenti y me quiero ir  |");
        printf("\n+-----------------------------------------+");
        printf("\n Elige la opcion correcta: ");
        scanf("%i", &opcion);

        if(opcion > 3 && opcion < 0)
        {
            printf("\n %i No es una opcion valida", opcion);
        }
    }
    while(opcion > 3 && opcion < 0);
    system("cls");
    return opcion;

}

void mostrarMenuAdmin()
{
    printf("\n Muestro el menu del admin");
}

void mostrarMenuAdoptante()
{
    printf("\n Muestro el menu del adoptante");
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

    printf("Cargue el ID del perrito: ");
    scanf("%d", &aux.idPerrito);
    fflush(stdin);
    printf("Cargue nombre del solicitante: ");
    gets(aux.solicitante);

    printf("Ingrese su email: ");
    gets(aux.email);

    printf("Ingrese su Telefono: ");
    gets(aux.tel);

    return aux;
}
