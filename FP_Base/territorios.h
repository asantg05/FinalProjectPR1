#include "docente.h"

#ifndef FP_BASE_TERRITORIOS_H
#define FP_BASE_TERRITORIOS_H

Territorio* listaTerritorios();
void asignarTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores);
void asignarNombreTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores);

void imprimirTerritorios(Territorio a[]);


#endif //FP_BASE_TERRITORIOS_H
