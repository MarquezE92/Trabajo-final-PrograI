#ifndef MENUGENERAL_H_INCLUDED
#define MENUGENERAL_H_INCLUDED

#define ARCHIVO_PERRITOS "perritos.bin"
#define ARCHIVO_ADOPTANTES "adoptantes.bin"
#define ARCHIVO_SOLICITUDES "solicitudes.bin"
#define ARCHIVO_ADOPCIONES "adopciones.bin"

extern const char *porteTexto[];
extern const char *generoTexto[];
extern const char *estadoTexto[];
extern const char *temperamentoTexto[];

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
    char nombre[35];
    int edad;
    char raza[35];
    Porte porte;
    Estado estado;
    Temperamento temperamento;
    Genero genero;
    char fechaIngreso[11];
} Perrito;

typedef struct
{
    int idPerrito;
    char solicitante[35];
    char email[35];
    char tel[12];
} Solicitud;

typedef struct
{
    char fecha[11];
    char comentario[125];
} Observacion;

typedef struct
{
    int idAdoptante;
    char nombre[35];
    char email[35];
    char tel[12];
    char direccion[35];
} Adoptante;

typedef struct
{
    int idPerrito;
    int idAdoptante;
    Observacion observaciones[6];
} Adopcion;

void menuPrincipal(const char archivoPerritos[], const char archivoAdoptantes[],const char archivoSolicitudes[],const char archivoAdopciones[]);
int archivoAArreglo(char nombreArchivo[], Perrito lista[]);

#endif
