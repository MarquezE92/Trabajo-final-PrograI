#ifndef PERRITOS_H_INCLUDED
#define PERRITOS_H_INCLUDED

#include "menuGeneral.h"

int mostrarMenuPrincipal();
void mostrarMenuAdmin();
Perrito cargarPerrito();
void mostrarUnPerrito(Perrito perri);
void mostrarListadoPerritosRecursivo(Perrito lista[], int validos, int i);
void filtrarPerritos(Perrito lista[], int validos);
void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[]);
void cargarSolicitud(char nombreArchivo[]);
Solicitud cargarSolicitudSimple();

#endif
