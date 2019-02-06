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
#define N_MAX_CAFES 12
#define N_MAX_BIRRAS 8
#define N_MAX_VINOS 6
#define DIM_NAME 24
#define DIM_3_PLAYERS 35
#define DIM_4_PLAYERS 30
#define DIM_5_PLAYERS 25
#define DIM_6_PLAYERS 20
#define DIM_NUM_CARTAS 26

typedef enum {CAFE,BIRRA,VINO}Equipo; //0,1,2
typedef enum {ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO}Color; //0,1,2,3,4,5

typedef struct{
    int id;
    int numCartas;
    int listaCartas[DIM_NUM_CARTAS+1];
    char nombre[DIM_NAME+1];
}Persona;

//Information that is gonna be saved in the List
typedef struct {
    int numeroCarta;    //Territory
    int numArmadas;
    Persona persona; //--> ID
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
void crearTodasLasCartas(Lista *lista);
Informacion inicializarCarta();
void creacionPersonas();

void modificaPersona(Informacion iCarta);

int numeroArmadasIniciales();
int cantidadJugadores();
int empiezaPrimero(int nJugadores);
int contadorCartas(Lista * lista);

void inicializaLista(Lista *lista);

_Bool listaVacia(Lista *lista);
char *escribirNombre();
void generateSeed();
int generateRandom(int min, int max);
_Bool isAdjacent(int idFirst, int idSecond);


//-------PRINTS----------
void imprimirInicio(Informacion inicio);
void imprimirListaCartas(Lista * lista);
void imprimirCarta(Informacion carta);
void imprimirVector(Persona a[], int tam);

#endif
