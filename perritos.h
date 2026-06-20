#ifndef PERRITOS_H_INCLUDED
#define PERRITOS_H_INCLUDED

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

extern const char *porte[];
extern const char *genero[];

Perrito cargarPerrito();
void mostrarPerrito(Perrito perri);
void mostrarTodosPerritos(char nombreArchivo[]);
void cargarPerritoArchivo(char nombreArchivo[]);
void filtrarPorPorte(char nombreArchivo[], Porte porteBuscado);
void filtrarPorGenero(char nombreArchivo[], Genero generoBuscado);
void filtrarPorEdad(char nombreArchivo[], int edadBuscada);
void filtrarPorTemperamento(char nombreArchivo[], Temperamento tempBuscado);
void menuGestionPerritos(char nombreArchivo[]);
void modificarPerrito(char nombreArchivo[], int id);
void eliminarPerrito(char nombreArchivo[], int idBuscado);
void cargaMasivaPerritos(char nombreArchivo[]);

#endif
