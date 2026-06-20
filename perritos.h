#ifndef PERRITOS_H_INCLUDED
#define PERRITOS_H_INCLUDED

Perrito cargarPerrito();
void mostrarUnPerrito(Perrito perri);
void mostrarListadoPerritosRecursivo(Perrito lista[], int valido, int i);
void filtrarPerritos(Perrito lista[], int validos);
void mostrarMenuAdoptante(Perrito lista[], int validos, char archivoSolicitudes[]);

#endif // PERRITOS_H_INCLUDED
