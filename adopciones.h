#ifndef ADOPCIONES_H_INCLUDED
#define ADOPCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menuGeneral.h"
#include "pila.h"

#define MAX_PILA 50

typedef struct
{
    Adopcion elementos[MAX_PILA];
    int tope;
} PilaAdopciones;

extern PilaAdopciones historial;

/* PROTOTIPOS ADOPCIONES */

void registrarAdopcion(char archPerritos[], char archAdoptantes[], char archAdopciones[]);
void cargarObservacion(char archAdopciones[], int idPerrito);
void mostrarAdopciones(char archAdopciones[]);
void pasarAHistorico(char archAdopciones[], char archHistorico[], int idPerrito);
void menuGestionarAdopciones();
void menuSeleccionAdopciones();
void insertarAdopcion(Adopcion lista[], int pos);
void ordenamientoInsercionAdopciones(Adopcion lista[], int validos);
void ordenarArchivoAdopciones(char archAdopciones[]);


/* PROTOTIPOS PILA */

void inicializarPila(PilaAdopciones *pila);
int pilaLlena(PilaAdopciones *pila);
int pilaVacia(PilaAdopciones *pila);
void apilarAdopcion(PilaAdopciones *pila, Adopcion a);
Adopcion desapilarAdopcion(PilaAdopciones *pila);
void mostrarPila(PilaAdopciones *pila);

#endif
