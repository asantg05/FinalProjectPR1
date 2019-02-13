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

typedef enum {CAFE,BIRRA,VINO}Equipo; //0,1,2
typedef enum {ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO}Color; //0,1,2,3,4,5

typedef struct{
    int id;
    int prop;
    int numArmadas;
    char nombre[DIM_NAME+1];
}Territorio;

typedef struct{
    int id;
    int numCartas;
    int numArmadas;
    //int *listaCartas;
    int listaCartas[DIM_NUM_CARTAS];
    char nombre[DIM_NAME+1];
    Color color;
}Persona;

//Information that is gonna be saved in the List
typedef struct {
    int numeroCarta;    //Territory
    Persona propietario; //--> ID
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

//----FUNCTIONS----

void risika();
Carta* crearCarta(Lista *lista);
Carta* insertarCarta(Lista * lista, Informacion infoCarta);
Carta* colocarCarta();
Informacion inicializarCarta();
void inicializaLista(Lista *lista);
void crearTodasLasCartas(Lista *lista);
Persona* creacionPersonas(int dimensionVector);
void vaciarListaCartas(Lista *lista);
void vaciarCarta(Carta *carta);
Territorio* listaTerritorios();
void actualizarTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores);

void repartirTerritorio(Lista *lista);
void repartirCartas(Lista *lista , Persona* jugadores,int nJugadores);
void repartirEquipo(Lista *lista);
void addCartas(Lista *lista, Persona *jugadores, int nJugadores);

int numeroArmadasIniciales(int nJugadores);
int cantidadJugadores();
int empiezaPrimero(int nJugadores);
int contadorCartas(Lista * lista);
char* escribirNombre(int nJugadores);
void crearArrayAleatorios(int *vectorAleatorios, int nJugadores, int num);
void actualizarNumeroCartasPlayerN(Lista *lista,Persona* jugadores,int nJugadores);

_Bool listaVacia(Lista *lista);
void generateSeed();
int generateRandom(int min, int max);
_Bool isAdjacent(int idFirst, int idSecond);

//-------PRINTS----------
void imprimirInicio(Lista* lista, Persona* listaJugadores , int nJugadores);
void imprimirListaCartas(Lista * lista);
void imprimirCarta(Informacion carta);
void imprimirVector(Persona a[], int tam);
void imprimirTerritorios(Territorio a[]);
char* imprimirColor(Persona jugador);


#endif
