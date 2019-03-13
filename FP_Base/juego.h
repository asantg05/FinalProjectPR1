//
// Created by ANDRES on 13/03/2019.
//

#ifndef FP_BASE_JUEGO_H
#define FP_BASE_JUEGO_H

void preparacionArmadas(Territorio *territorios, Persona *listaJugadores, int nJugadores);
void reforzamiento(Territorio *territorios, Persona *listaJugadores, int nJugadores,int contadorJugador);
int insertarTerritorio(Territorio *territorios, Persona *listaJugadores, int nJugadores, int contadorJugador);

int numeroRondas(int nJugadores);
int armadasExtra(Persona *listaJugadores, int contadorJugador);

_Bool inputNoValido(int territorioElegido);
_Bool miTerritorio(int territorioElegido, int idJugador, Territorio* territorios , Persona* listaJugadores, int nJugadores);

#endif //FP_BASE_JUEGO_H
