#ifndef FP_BASE_DOCENTE_H
#define FP_BASE_DOCENTE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_TERRITORI 26 //Number of territories
#define N_MAX_JUGADORES 6
#define N_MIN_JUGADORES 3
#define N_MAX_CARTAS 26
#define N_MAX_TERRITORIOS 26
#define N_MAX_CAFES 12
#define N_MAX_BIRRAS 8
#define N_MAX_VINOS 6
#define DIM_NAME 25
#define DIM_3_PLAYERS 35
#define DIM_4_PLAYERS 30
#define DIM_5_PLAYERS 25
#define DIM_6_PLAYERS 20
#define DIM_NUM_CARTAS 26
#define DIM_COLOR 10
#define MAX_ID 25


typedef enum {CAFE,BIRRA,VINO}Equipo; //0,1,2
typedef enum {ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO}Color; //0,1,2,3,4,5

//Information that is gonna be saved in the List
typedef struct {
    int numeroCarta;    //Territory
    int propietario; //--> ID
    Equipo equipo;
} Informacion;

//Carta is the territory
struct carta{
    Informacion inf;
    struct carta *next; //Pointer to the next element
    struct carta *prev;
};

typedef struct carta Carta;

//Structure of the list. We only have a first of the list because is linear.
typedef struct {
    Carta* first;
    Carta* last;
} Lista;

typedef struct{
    int id;
    int numCartas;
    int numArmadas;
    int numTerritorios;
    char nombre[DIM_NAME+1];
    char color[DIM_COLOR];
    Lista listaCartas;
}Persona;

typedef struct{
    int id;
    int prop;
    int numArmadas;
    char nombre[DIM_NAME+1];
    char nombreTerritorio[DIM_NAME+1];
}Territorio;

//----FUNCTIONS----
void risika();

//Persona Methods
Persona* creacionPersonas(int dimensionVector);

//Territorio Methods
void turno(Territorio *territorios, Persona *listaJugadores, int nJugadores);
void batalla(Territorio *territorios, Persona *listaJugadores, int nJugadores,int contadorJugador);

//Other methods
int numeroArmadasIniciales(int nJugadores);
int cantidadJugadores();
int empiezaPrimero(int nJugadores);
void generateSeed();
int generateRandom(int min, int max);
_Bool isAdjacent(int idFirst, int idSecond);

//-------PRINTS----------
void imprimirInicio(Lista* lista, Persona* listaJugadores , int nJugadores);
void imprimirListaCartas(Lista * lista);
void imprimirBarajas(Lista *baraja, int nJugadores);
void imprimirCarta(Informacion carta);
void imprimirVector(Persona a[], int tam);
void imprimirTerritorios(Territorio a[]);
void imprimirArmadas(Persona* listaJugadores, int nJugadores);

#endif
