#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *porteTexto[] =
{
    "CHICO",
    "MEDIANO",
    "GRANDE"
};

const char *generoTexto[] =
{
    "MACHO",
    "HEMBRA"
};

const char *estadoTexto[] =
{
    "DISPONIBLE",
    "ADOPTADO"
};

const char *temperamentoTexto[] =
{
    "CALMADO",
    "JUGUETON",
    "ANSIOSO",
    "AGRESIVO",
    "SOCIABLE"
};

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

Solicitud cargarSolicitudSimple();

int main()
{
    system("color 0B");

    //Perrito perri = cargarPerrito();
    ///mostrarPerrito(perri);

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
    //Perrito refugio[];/// arreglo para las funciones faltan los validos que daria la funcion de carga

    return 0;
}

///funciones


