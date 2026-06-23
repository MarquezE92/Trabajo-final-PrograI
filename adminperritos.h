#ifndef ADMINPERRITOS_H_INCLUDED
#define ADMINPERRITOS_H_INCLUDED

#include "menuGeneral.h"

void menuPerritosGeneral(char nombreArchivo[]);
void menuEdicionPerritos(char nombreArchivo[]);
void menuFiltro(char nombreArchivo[]);
Perrito cargarPerri();
void mostrarPerrito(Perrito perri);
void mostrarTodosPerritos(char nombreArchivo[]);
void cargarPerritoArchivo(char nombreArchivo[]);
void filtrarPorPorte(char nombreArchivo[], Porte porteBuscado, int **vecIDs, int *validos);
void filtrarPorGenero(char nombreArchivo[], Genero generoBuscado, int **vecIDs, int *validos);
void filtrarPorEdad(char nombreArchivo[], int edadBuscada, int **vecIDs, int *validos);
void filtrarPorTemperamento(char nombreArchivo[], Temperamento tempBuscado, int **vecIDs, int *validos);
void menuGestionPerritos(char nombreArchivo[], int vecIDs[], int validos);
void modificarPerrito(char nombreArchivo[], int id);
void eliminarPerrito(char nombreArchivo[], int idBuscado);
void cargaMasivaPerritos(char nombreArchivo[]);
void agregarID(int **vec, int *validos, int id);
int validarID(int vec[], int validos, int idBuscado);
void cargarTodosLosIDs(char nombreArchivo[], int **vecIDs, int *validos);
int obtenerIdPerrito(char nombreArchivo[]);

#endif
