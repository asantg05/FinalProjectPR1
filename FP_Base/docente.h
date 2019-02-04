#ifndef FP_BASE_DOCENTE_H
#define FP_BASE_DOCENTE_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_TERRITORI 26 //Number of territories
#define N_MAX_JUGADORES 6
#define N_MIN_JUGADORES 3
#define N_MAX_CARTAS 26
#define N_MAX_CAFES 12
#define N_MAX_BIRRAS 8
#define N_MAX_VINOS 6
#define DIM_NAME 24
#define DIM_3_PLAYERS 35
#define DIM_4_PLAYERS 30
#define DIM_5_PLAYERS 25
#define DIM_6_PLAYERS 20

typedef enum {CAFE,BIRRA,VINO}Equipo; //0,1,2
typedef enum {ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO}Color; //0,1,2,3,4,5

typedef struct{
    int id;
    char nombre[DIM_NAME+1];
}Persona;

//Information that is gonna be saved in the List
typedef struct {
    int numArmadas;
    int numeroCarta;
    Persona persona;
    Equipo equipo;
} Informacion;

//Carta is the territory
typedef struct carta {
    Informacion inf;
    struct carta *next; //Pointer to the next element
} Carta;

//Structure of the list. We only have a head of the list because is linear.
typedef struct {
    Carta* head;
} Lista;

//----FUNCTIONS----

Carta* crearCarta(Lista *lista);
Carta* insertarCarta(Lista * lista, Informacion infoCarta);
Carta* colocarCarta();
void crearVariasCartas(Lista *lista);
Informacion inicializarCarta();
void inicializaPersona();

int numeroArmadasIniciales();
int cantidadJugadores();
int empiezaPrimero();

void inicializaLista(Lista *lista);
void generateSeed();
int generateRandom(int min, int max);
_Bool isAdjacent(int idFirst, int idSecond);

#endif
