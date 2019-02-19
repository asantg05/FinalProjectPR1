#include "docente.h"

#ifndef FP_BASE_CREACIONLISTAS_H
#define FP_BASE_CREACIONLISTAS_H

Carta* crearCarta(Lista *lista);
Carta* insertarEnTesta(Lista *lista, Informacion infoCarta);
Carta* colocarCarta();
Informacion inicializarCarta();
void inicializaLista(Lista *lista);
void crearTodasLasCartas(Lista *lista);
void vaciarListaCartas(Lista *lista);
void vaciarBarajas(Persona *jugadores, int nJugadores);
void vaciarCarta(Carta *carta);
int contadorCartas(Lista * lista);
void repartirTerritorio(Lista *lista);
void repartirCartas(Lista *lista , Persona* jugadores,int nJugadores);
void repartirEquipo(Lista *lista);
_Bool listaVacia(Lista *lista);
void actualizarNumeroCartasPlayerN(Lista *lista,Persona* jugadores,int nJugadores);
void inicializarBarajas(Persona* jugadores, int nJugadores);
void insertarEnBaraja(Lista* mazo, Persona* listaJugadores, int nJugadores);
void imprimirIds(Lista* baraja, int nJugadores);
Informacion* obtenerCarta(Lista* lista, int id);
void barajarMazo(Lista* lista);

//-------PRINTS----------
void imprimirInicio(Lista* lista, Persona* listaJugadores , int nJugadores);
void imprimirListaCartas(Lista * lista);
void imprimirBarajas(Lista *baraja, int nJugadores);
void imprimirCarta(Informacion carta);

#endif //FP_BASE_CREACIONLISTAS_H
