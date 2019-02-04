#include "docente.h"


/**
 * This function checks if two territories are adjacent (reachable from each other).
 * @param idFirst  the id of the first territory
 * @param idSecond the id of the second territory
 * @return it returns true if they are adjacent, false otherwise
 */

//This global constant variable contains the adjacencies of the territories (true if a territory is adjacent with another).
const _Bool t[N_TERRITORI][N_TERRITORI] = {
        { false, false,  true, false, false, false, false, false, false, false, false, false,  true, false, false, false, false,  true, false, false, false, false, false, false, false, false},
        { false, false,  true,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {  true,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false,  true, false, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false, false},
        { false, false, false,  true, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false,  true, false, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false,  true,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false,  true,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false,  true, false, false, false,  true, false, false, false, false, false,  true, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false},
        { false, false, false, false, false, false, false, false,  true,  true, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
        {  true, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true, false, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true, false,  true, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false,  true,  true, false,  true, false, false, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false, false,  true, false, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false,  true, false, false, false, false,  true, false, false, false, false, false, false, false, false, false, false, false, false},
        {  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false, false,  true, false, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true, false,  true, false, false, false, false},
        { false, false, false,  true, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true,  true,  true, false, false, false},
        { false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false, false, false, false, false,  true, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true,  true, false, false, false, false, false, false},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false, false, false,  true, false,  true},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true, false},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true},
        { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,  true, false,  true, false}
};

/**
 * Initializing the list of Cards
 * @param lista
 */
void inicializaLista(Lista *lista){
    lista->head=NULL;
}

/**
 * It allows to create more than one card
 * @param lista
 */
void crearVariasCartas(Lista *lista){
    int i;

    for(i=0;i<N_MAX_CARTAS;i++){
        crearCarta(lista);
    }
}

/**
 * Function that creates a card that is saved in the list
 * @param lista List where the card is
 * @return contact saved
 */
Carta* crearCarta(Lista *lista){

    Informacion infoCarta;


    return insertarCarta(lista,infoCarta);
}

Informacion inicializarCarta(){
    Informacion iCarta;

    inicializaPersona();

    iCarta.equipo=0;

}

void inicializaPersona(){

    Informacion iCarta;
    int numeroPersonas;

    //Creating names in an list for using it later
    char listaNombres[N_MAX_JUGADORES][DIM_NAME]={
            "Andres",
            "Alvaro",
            "Ivan",
            "Matteo",
            "Fabio",
            "Stefano"
    };

    numeroPersonas= cantidadJugadores();
    Persona persona;   //Vector Declaration

    //Assigning a name to the person in the card
    strcpy(persona.nombre, listaNombres[generateRandom(0,N_MAX_JUGADORES-1)]); //Assigning names to vectorJugadores
    strcpy(iCarta.persona.nombre , persona.nombre);

    persona.id=0;//We put it first to 0, and then we'll see.
    iCarta.persona.id = persona.id;
}

int numeroArmadasIniciales(){
    int nJugadores,armadas;
    nJugadores=cantidadJugadores();

    if(nJugadores==3){
        armadas=DIM_3_PLAYERS; //35
    }
    else if(nJugadores==4){
        armadas=DIM_4_PLAYERS; //30
    }
    else if(nJugadores==5){
        armadas=DIM_5_PLAYERS; //25
    }
    else{
        armadas= DIM_6_PLAYERS; //20
    }

    return armadas;
}

/**
 * Used for knowing which player begins the game
 * @return int
 */
int empiezaPrimero(){
    int nJugadores=cantidadJugadores();

    return generateRandom(0,nJugadores);
}

/**
 * With this function, we know how many players are playing
 * @return random number of players (int)
 */
int cantidadJugadores(){
    return generateRandom(N_MIN_JUGADORES,N_MAX_JUGADORES);
}

/**
 * Function that let us to put a Card at the beginning of the list of cards
 * @param List of Cards
 * @param Information that is gonna be saved
 * @return The new card of the list
 */
Carta* insertarCarta(Lista * lista, Informacion infoCarta){

    Carta* cartaNueva= NULL;
    cartaNueva = colocarCarta();

    cartaNueva->inf=infoCarta;//l'elemento da inserire prende il contatto passato come paramentro
    cartaNueva->next=lista->head;//la testa della lista diventa il next del nuovoElemento
    lista->head= cartaNueva;//la testa della lista diventa il next del nuovoElemento

    return cartaNueva;
}

/**
 * This function is used for booking a space in the memory
 * @return the space in memory
 */
Carta* colocarCarta(){
    Carta *espacio = NULL;
    espacio = (Carta *)malloc(sizeof(Carta));

    if(espacio==NULL)
        exit(-1);

    return espacio;
}

void generateSeed(){
    srand(time(NULL));
}

int generateRandom(int min, int max){
    return min + rand()%(max-min+1);
}

_Bool isAdjacent(int idFirst, int idSecond){
    return t[idFirst][idSecond];
}

