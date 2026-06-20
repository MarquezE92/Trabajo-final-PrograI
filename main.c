#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perritos.h"

//const char *porte[] = {
//    "CHICO",
//    "MEDIANO",
//    "GRANDE"
//};

//const char *genero[] = {
//    "MACHO",
//    "HEMBRA"
//};

//typedef enum
//{
//    CHICO,
//    MEDIANO,
//    GRANDE
//} Porte;

//typedef enum
//{
//    DISPONIBLE,
//    ADOPTADO
//} Estado;
//
//typedef enum
//{
//    CALMADO,
//    JUGUETON,
//    ANSIOSO,
//    AGRESIVO,
//    SOCIABLE
//} Temperamento;
//
//typedef enum
//{
//    MACHO,
//    HEMBRA
//} Genero;

typedef struct
{
    int idPerrito;
    char solicitante[35];
    char email[35];
    char tel[12];
} Solicitud;

//typedef struct
//{
//    int idPerrito;
//    char nombre[35];
//    int edad;
//    char raza[35];
//    Porte porte;
//    Estado estado;
//    Temperamento temperamento;
//    Genero genero;
//    char fechaIngreso[10];
//} Perrito;

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
//Perrito cargarPerrito();
//void mostrarPerrito(Perrito perri);

int main()
{
    system("color 0B");

 //cargarPerritoArchivo("perrito.bin");
 //cargarPerritoArchivo("perrito.bin");
 mostrarTodosPerritos("perrito.bin");
 //cargaMasivaPerritos("perrito.bin");
//filtrarPorTemperamento("perrito.bin", 1);
menuGestionPerritos("perrito.bin");


    /*int opcion = mostrarMenuPrincipal();


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
    }*/

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

//Perrito cargarPerrito()
//{
//    Perrito aux;
//    int op;
//    printf("Cargue el ID del perrito: ");
//    scanf("%d", &aux.idPerrito);
//    printf("Cargue la edad del perrito: ");
//    scanf("%d", &aux.edad);
//    getchar();
//    printf("Cargue el nombre del perrito: ");
//    gets(aux.nombre);
//    printf("Cargue la raza del perrito: ");
//    gets(aux.raza);
//    printf("Cargue fecha actual perrito: ");
//    gets(aux.fechaIngreso);
//    do{
//        printf("Seleccione el porte (0-Chico, 1-Mediano, 2-Grande): ");
//        scanf("%d", &op);
//        if(op <0 || op>2){
//            printf("\nNo es una opcion valida,vuelva a intentarlo");
//        }
//    }while(op <0 || op>2);
//    aux.porte = op;
//
//    do{
//        printf("Seleccione el genero (0-Macho, 1-Hembra): ");
//        scanf("%d", &op);
//        if(op <0 || op>1){
//            printf("\nNo es una opcion valida,vuelva a intentarlo");
//        }
//    }while(op <0 || op>1);
//    aux.genero = op;
//
//    do{
//       printf("Seleccione el temperamento (0-Calmado, 1-Jugueton, 2-Ansioso, 3-Agresivo, 4-Sociable): ");
//       scanf("%d", &op);
//       if(op <0 || op>4){
//            printf("\nNo es una opcion valida,vuelva a intentarlo");
//       }
//    }while(op <0 || op>4);
//    aux.temperamento = op;
//
//    aux.estado = DISPONIBLE;
//
//    return aux;
//}
//
//void mostrarPerrito(Perrito perri){
//        printf("\n ID: %i", perri.idPerrito);
//        printf("\nNombre: %s", perri.nombre);
//        printf("\n Edad: %i", perri.edad);
//        printf("\n %s", perri.genero);
//        printf("\n Raza: %s", perri.raza);
//        printf("\nPorte: %s", porte[perri.porte]);
//}
