#include "adopciones.h"

/// reg adop: busca perri y adoptante en arch, crea reg de adop y lo guarda.
void registrarAdopcion(char archPerritos[], char archAdoptantes[], char archAdopciones[]) {
    int idPerrito, idAdoptante;
    Perrito perri;
    Adoptante adoptante;
    Adopcion nueva;
    int encontroPerrito = 0;
    int encontroAdoptante = 0;
    int exito = 1;
    FILE *pfPerrito = NULL, *pfAdoptante = NULL, *pfAdopcion = NULL;

    printf("\nIngrese ID del perrito a adoptar <3: ");
    scanf("%d", &idPerrito);
    printf("Ingrese ID del adoptante: ");
    scanf("%d", &idAdoptante);

    /// verif que perrito existe y esta disponible
    pfPerrito = fopen(archPerritos, "rb+");
    if (pfPerrito == NULL) {
        printf("\nError al abrir archivo de perritos.\n");
        exito = 0;
    }

    if (exito) {
        while (fread(&perri, sizeof(Perrito), 1, pfPerrito) > 0 && !encontroPerrito) {
            if (perri.idPerrito == idPerrito) {
                if (perri.estado == ADOPTADO) {
                    printf("\nEse perrito ya fue adoptado.\n");
                    exito = 0;
                }
                encontroPerrito = 1;
            }
        }
        if (!encontroPerrito) {
            printf("\nNo se encontro el perrito con ID %d.\n", idPerrito);
            exito = 0;
        }
    }

    /// verif que adoptante existe
    if (exito) {
        pfAdoptante = fopen(archAdoptantes, "rb");
        if (pfAdoptante == NULL) {
            printf("\nError al abrir archivo de adoptantes.\n");
            exito = 0;
        }
    }

    if (exito) {
        while (fread(&adoptante, sizeof(Adoptante), 1, pfAdoptante) > 0 && !encontroAdoptante) {
            if (adoptante.idAdoptante == idAdoptante) {
                encontroAdoptante = 1;
            }
        }
        fclose(pfAdoptante);
        if (!encontroAdoptante) {
            printf("\nNo se encontro el adoptante con ID %d.\n", idAdoptante);
            exito = 0;
        }
    }

    /// crea & guarda adop
    if (exito) {
        nueva.idPerrito   = idPerrito;
        nueva.idAdoptante = idAdoptante;

        int i;
        for (i = 0; i < 6; i++) {
            nueva.observaciones[i].fecha[0]      = '\0';
            nueva.observaciones[i].comentario[0] = '\0';
        }

        fseek(pfPerrito, -(long)sizeof(Perrito), SEEK_CUR);
        perri.estado = ADOPTADO;
        fwrite(&perri, sizeof(Perrito), 1, pfPerrito);

        pfAdopcion = fopen(archAdopciones, "ab");
        if (pfAdopcion == NULL) {
            printf("\nError al guardar la adopcion.\n");
        } else {
            fwrite(&nueva, sizeof(Adopcion), 1, pfAdopcion);
            fclose(pfAdopcion);
            printf("\nAdopcion registrada con exito! %s ahora tiene un hogar <3.\n", perri.nombre);
        }
    }

    if (pfPerrito != NULL) fclose(pfPerrito);
}


/// carga obs: busca adop por idPerrito y agrega observ en el primer lugar vacio
void cargarObservacion(char archAdopciones[], int idPerrito) {
    Adopcion aux;
    int encontrado = 0;
    int posLibre = 0;
    FILE *pfAdopcion = fopen(archAdopciones, "rb+");

    if (pfAdopcion == NULL) {
        printf("\nError al abrir archivo de adopciones.\n");
    } else {
        while (fread(&aux, sizeof(Adopcion), 1, pfAdopcion) > 0 && !encontrado) {
            if (aux.idPerrito == idPerrito) {
                encontrado = 1;
                int i = 0;
                while (i < 6 && !posLibre) {
                    if (aux.observaciones[i].fecha[0] == '\0') {
                        posLibre = 1;
                        getchar();
                        printf("Ingrese fecha: ");
                        gets(aux.observaciones[i].fecha);
                        printf("Ingrese observacion: ");
                        gets(aux.observaciones[i].comentario);

                        fseek(pfAdopcion, -(long)sizeof(Adopcion), SEEK_CUR);
                        fwrite(&aux, sizeof(Adopcion), 1, pfAdopcion);
                        printf("\nObservacion guardada.\n");
                    }
                    i++;
                }
                if (!posLibre) {
                    printf("\nYa se cargaron todas las observaciones para este perrito.\n");
                }
            }
        }
        if (!encontrado) {
            printf("\nNo se encontro adopcion para el perrito ID %d.\n", idPerrito);
        }
        fclose(pfAdopcion);
    }
}


/// show adop (adop activas con observ cargadas)
void mostrarAdopciones(char archAdopciones[]) {
    Adopcion aux;
    int cont = 0;
    FILE *pfAdopcion = fopen(archAdopciones, "rb");

    if (pfAdopcion == NULL) {
        printf("\nNo hay adopciones registradas aun.\n");
    } else {
        printf("\n========== ADOPCIONES ACTIVAS ==========\n");
        while (fread(&aux, sizeof(Adopcion), 1, pfAdopcion) > 0) {
            cont++;
            printf("\n  Perrito ID : %d", aux.idPerrito);
            printf("\n  Adoptante ID: %d", aux.idAdoptante);
            printf("\n  Observaciones:");
            int i;
            for (i = 0; i < 6; i++) {
                if (aux.observaciones[i].fecha[0] != '\0') {
                    printf("\n    [%s] %s", aux.observaciones[i].fecha,
                                            aux.observaciones[i].comentario);
                }
            }
            printf("\n----------------------------------------\n");
        }
        if (cont == 0) printf("  No hay adopciones activas.\n");
        fclose(pfAdopcion);
    }
}


/// de arch a historiarch. reescribe arch sacando el dato pasado
void pasarAHistorico(char archAdopciones[], char archHistorico[], int idPerrito) {
    Adopcion aux;
    int encontrado = 0;
    FILE *pfOrigen  = fopen(archAdopciones, "rb");
    FILE *pfTemp    = fopen("temp_adopciones.dat", "wb");
    FILE *pfHistorico = fopen(archHistorico, "ab");

    if (!pfOrigen || !pfTemp || !pfHistorico) {
        printf("\nError al abrir archivos para mover al historico.\n");
        if (pfOrigen)    fclose(pfOrigen);
        if (pfTemp)      fclose(pfTemp);
        if (pfHistorico) fclose(pfHistorico);
    } else {
        // copiar al temp (sin el registro a mover) y al historico (el registro)
        while (fread(&aux, sizeof(Adopcion), 1, pfOrigen) > 0) {
            if (aux.idPerrito == idPerrito && !encontrado) {
                fwrite(&aux, sizeof(Adopcion), 1, pfHistorico);
                encontrado = 1;
            } else {
                fwrite(&aux, sizeof(Adopcion), 1, pfTemp);
            }
        }
        fclose(pfOrigen);
        fclose(pfTemp);
        fclose(pfHistorico);

        // reescribir adopciones.dat desde el temporal
        pfOrigen = fopen(archAdopciones, "wb");
        pfTemp   = fopen("temp_adopciones.dat", "rb");

        if (pfOrigen && pfTemp) {
            while (fread(&aux, sizeof(Adopcion), 1, pfTemp) > 0) {
                fwrite(&aux, sizeof(Adopcion), 1, pfOrigen);
            }
        }
        if (pfOrigen) fclose(pfOrigen);
        if (pfTemp)   fclose(pfTemp);

        if (encontrado)
            printf("\nAdopcion del perrito ID %d movida al historico.\n", idPerrito);
        else
            printf("\nNo se encontro adopcion con ID de perrito %d.\n", idPerrito);
    }
}


/// inic pilita
void inicializarPila(PilaAdopciones *pila) {
    pila->tope = -1;
}

/// full pilita
int pilaLlena(PilaAdopciones *pila) {
    return pila->tope == MAX_PILA - 1;
}

/// empty pilita
int pilaVacia(PilaAdopciones *pila) {
    return pila->tope == -1;
}

/// apilita
void apilarAdopcion(PilaAdopciones *pila, Adopcion a) {
    if (pilaLlena(pila)) {
        printf("\nEl historial esta lleno.\n");
    } else {
        pila->tope++;
        pila->elementos[pila->tope] = a;
    }
}

/// desapilita
Adopcion desapilarAdopcion(PilaAdopciones *pila) {
    Adopcion vacia = {0};
    if (!pilaVacia(pila)) {
        vacia = pila->elementos[pila->tope--];
    } else {
        printf("\nEl historial esta vacio.\n");
    }
    return vacia;
}

/// mostrar pilita
void mostrarPila(PilaAdopciones *pila) {
    if (pilaVacia(pila)) {
        printf("\nNo hay historial de adopciones.\n");
    } else {
        printf("\n===== HISTORIAL =====\n");
        int i;
        for (i = pila->tope; i >= 0; i--) {
            printf("\n  Perrito ID: %d  |  Adoptante ID: %d",
                   pila->elementos[i].idPerrito,
                   pila->elementos[i].idAdoptante);
        }
        printf("\n============================================\n");
    }
}
