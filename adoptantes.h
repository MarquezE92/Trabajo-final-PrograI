#ifndef ADOPTANTES_H_INCLUDED
#define ADOPTANTES_H_INCLUDED
#include "menuGeneral.h"

void menuAdoptante();
void menuSeleccionAdoptante();
Adoptante cargarAdoptanteSimple();
void cargarAdoptante(char nombreArchivo[]);
void mostrarAdoptante(Adoptante adoptante);
void mostrarTodosAdoptantes(char nombreArchivo[]);
void mostrarAdoptantePorId(char nombreArchivo[], int id);
int buscarPosicionPorId(char nombreArchivo[], int idAdoptante);
void eliminarAdoptante(char nombreArchivo[], int idAdoptante);
Adoptante modificarAdoptante(Adoptante adoptante);
void modificarRegistroAdoptante(char nombreArchivo[], int posicion);
int obtenerIdAdoptante();
int buscarMenorAdoptante(Adoptante lista[], int inicio, int validos);
void intercambiarAdoptantes(Adoptante lista[], int pos1, int pos2);
void ordenamientoSeleccionAdoptantes(Adoptante lista[], int validos);
int ordenarArchivoAdoptantes(char archAdoptantes[]);

#endif // ADOPTANTES_H_INCLUDED

