#ifndef ADOPTANTES_H_INCLUDED
#define ADOPTANTES_H_INCLUDED

#include "menuGeneral.h"

Adoptante cargarAdoptanteSimple();

void cargarAdoptante(char nombreArchivo[]);

void mostrarAdoptante(Adoptante adoptante);

void mostrarTodosAdoptantes(char nombreArchivo[]);

void mostrarAdoptantePorId(char nombreArchivo[], int id);

int buscarPosicionPorId(char nombreArchivo[], int idAdoptante);

void eliminarAdoptante(char nombreArchivo[], int idAdoptante);

Adoptante modificarAdoptante(Adoptante adoptante);

void modificarRegistroAdoptante(char nombreArchivo[], int posicion);

#endif // ADOPTANTES_H_INCLUDED
