#ifndef PERRITOS_H_INCLUDED
#define PERRITOS_H_INCLUDED
#include "menuGeneral.h"

Perrito cargarPerrito();
void mostrarUnPerrito(Perrito perri);
void mostrarListadoPerritosRecursivo(Perrito lista[], int valido, int i);
void filtrarPerritos(Perrito lista[], int validos);
void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[]);
Solicitud cargarSolicitudSimple();
void cargarSolicitud(char nombreArchivo[]);
void mostrarInfoContacto();

#endif // PERRITOS_H_INCLUDED
