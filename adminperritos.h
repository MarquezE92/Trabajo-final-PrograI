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

void menuPerritosGeneral(char nombreArchivo[]);
void menuEdicionPerritos(char nombreArchivo[]);
void menuFiltro(char nombreArchivo[]);
Perrito cargarPerrito();
void mostrarPerrito(Perrito perri);
void mostrarTodosPerritos(char nombreArchivo[]);
void cargarPerritoArchivo(char nombreArchivo[]);
void filtrarPorPorte(char nombreArchivo[],Porte porteBuscado,int **vecIDs,int *validos);
void filtrarPorGenero(char nombreArchivo[],Genero generoBuscado,int **vecIDs,  int *validos);
void filtrarPorEdad(char nombreArchivo[],int edadBuscada, int **vecIDs, int *validos);
void filtrarPorTemperamento(char nombreArchivo[],Temperamento tempBuscado,int **vecIDs,int *validos);
void menuGestionPerritos(char nombreArchivo[], int vecIDs[], int validos);
void modificarPerrito(char nombreArchivo[], int id);
void eliminarPerrito(char nombreArchivo[], int idBuscado);
void cargaMasivaPerritos(char nombreArchivo[]);
void agregarID(int **vec, int *validos, int id);
int validarID(int vec[], int validos, int idBuscado);
void cargarTodosLosIDs(char nombreArchivo[],int **vecIDs,int *validos);

#endif
