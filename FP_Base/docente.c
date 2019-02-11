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

void risika(){

    Persona *jugadores;
    int nJugadores;
    int n0, a=0;

    nJugadores= cantidadJugadores();
    jugadores = creacionPersonas(nJugadores); //We save in dinamic vector the list of players before initializing

    Lista mazo; //In this list, we will do all the changes
    inicializaLista(&mazo);
    crearTodasLasCartas(&mazo); //Let's create the 26 cards

    repartirCartas(&mazo , jugadores, nJugadores);
    repartirTerritorio(&mazo);
    repartirEquipo(&mazo);

    imprimirListaCartas(&mazo);
    imprimirInicio(&mazo,jugadores,nJugadores);
}

void repartirEquipo(Lista *lista){
    Carta *it = lista->first;

    while(it!=NULL){
        if(it->inf.numeroCarta<=11){
            it->inf.equipo=CAFE;
        }
        else if(it->inf.numeroCarta>=12 && it->inf.numeroCarta<=19){
            it->inf.equipo=BIRRA;
        } else{
            it->inf.equipo=VINO;
        }

        it=it->next;
    }
}

void repartirTerritorio(Lista *lista){
    Carta *it = lista->first;
    int k=0;

    while(it!=NULL){
        it->inf.numeroCarta=k;
        it=it->next;
        k++;
    }
}

void repartirCartas(Lista *lista , Persona* jugadores, int nJugadores){
    Carta *it = lista->first;
    int k=0;

    while(it!=NULL){
        it->inf.propietario.id=jugadores[k%nJugadores].id;
        it=it->next;
        k++;
    }
}

void actualizarNumeroCartasPlayerN(Lista *lista, Persona* jugadores, int nJugadores){
    Carta * it = lista->first;

    while(it != NULL){

        if(it->inf.propietario.id==0){
            jugadores[0].numCartas++;
        }
        if(it->inf.propietario.id==1){
            jugadores[1].numCartas++;
        }
        if(it->inf.propietario.id==2){
            jugadores[2].numCartas++;
        }
        if(it->inf.propietario.id==3){
            jugadores[3].numCartas++;
        }
        if(it->inf.propietario.id==4){
            jugadores[4].numCartas++;
        }
        if(it->inf.propietario.id==5){
            jugadores[5].numCartas++;
        }

        it=it->next;
    }
}

Persona* creacionPersonas(int dimensionVector){
    int id=0, i=0, primerJugador, j=0;

    Persona *jugadoresInicio;
    Persona *jugadoresOrdenados;

    jugadoresInicio=malloc(sizeof(Persona)*dimensionVector);
    jugadoresOrdenados=malloc(sizeof(Persona)*dimensionVector);

    jugadoresInicio[dimensionVector];
    jugadoresOrdenados[dimensionVector];

    for(i=0;i<dimensionVector;i++){ //Assigning id to Players
        jugadoresInicio[i].id=id;
        id++;
    }

    //Let's see who goes first
    primerJugador = empiezaPrimero(dimensionVector); //0,1,2,3,4,5

    jugadoresOrdenados[0].id=primerJugador;   //2

    for(j=1;j<dimensionVector;j++){
        jugadoresOrdenados[j].id=(jugadoresOrdenados[0].id+j)%(dimensionVector); //0,1,2,3,4,5 --> jugadoresOrdenados: 2,3,4,5,0,1
    }

    //We assign the initial number of armies to the players
    for(i=0;i<dimensionVector;i++){
        jugadoresOrdenados[i].numArmadas=numeroArmadasIniciales(dimensionVector);
    }

    //We initialize the number of cards the player have
    for(i=0;i<dimensionVector;i++){
        jugadoresOrdenados[i].numCartas=0;
    }

    //We assign random names to the players
    strcpy(jugadoresOrdenados[0].nombre , "Andres");
    strcpy(jugadoresOrdenados[1].nombre , "Adrian");
    strcpy(jugadoresOrdenados[2].nombre , "Ivan");
    strcpy(jugadoresOrdenados[3].nombre , "Alvaro");
    strcpy(jugadoresOrdenados[4].nombre , "Stefano");
    strcpy(jugadoresOrdenados[5].nombre , "Fabio");

    //We assign random colors to the players: ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO
    jugadoresOrdenados[0].color=ROJO;
    jugadoresOrdenados[1].color=VERDE;
    jugadoresOrdenados[2].color=AMARILLO;
    jugadoresOrdenados[3].color=VIOLETA;
    jugadoresOrdenados[4].color=AZUL;
    jugadoresOrdenados[5].color=NEGRO;

    printf("Vector Ordenado: \n");
    imprimirVector(jugadoresOrdenados,dimensionVector);

    return jugadoresOrdenados;
}

void imprimirVector(Persona a[] , int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("Player %d: %s----\tArmadas=%d" , a[i].id, a[i].nombre, a[i].numArmadas);
        printf("\n");
    }
}

void inicializaLista(Lista *lista){
    lista->first=NULL;
}

/**
 * It creates all the cards, 26 cards
 * @param lista
 */
void crearTodasLasCartas(Lista *lista){
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
    infoCarta = inicializarCarta();

    return insertarCarta(lista,infoCarta);
}

void imprimirCarta(Informacion carta){
    printf("\nTerritory: %d Owner: %d Team: %d Armies: %d" ,carta.numeroCarta , carta.propietario.id, carta.equipo,
           carta.numArmadas);
}

Informacion inicializarCarta(){
    Informacion iCarta;

    //Let's initialize all the variables of iCarta
    iCarta.propietario.id=0;
    iCarta.equipo=0;
    iCarta.numArmadas=0;
    iCarta.numeroCarta=0;

    return iCarta;
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
    cartaNueva->next=lista->first;//la testa della lista diventa il next del nuovoElemento
    lista->first= cartaNueva;//la testa della lista diventa il next del nuovoElemento

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

void imprimirListaCartas(Lista * lista){
    Carta *it = NULL;
    if(listaVacia(lista)==true){
        printf("\nNo elements in the list");
    }
    it=lista->first;
    while(it!=NULL) {
        imprimirCarta(it->inf);
        it = it->next;
    }
}

void vaciarListaCartas(Lista *lista){
    Carta *aux=NULL;
    Carta *it= lista->first;

    //Checking if the list is empty
    if(listaVacia(lista)==true){
        printf("\nThe list is empty");
        return;
    }

    while(it->next!=NULL){
        aux=it->next;
        vaciarCarta(it);
        it=aux;
    }
    lista->first=NULL;//se non setti la testa a NULL, non si cancella la lista,

    printf("\nList of Cards empty");
}

void vaciarCarta(Carta *carta){
    free(carta);
    carta=NULL;
}

void imprimirInicio(Lista* lista, Persona* listaJugadores ,int nJugadores){
    int i;
    actualizarNumeroCartasPlayerN(lista,listaJugadores,nJugadores);    //this function, let us know how many cards the players have

    printf("\nNumber of Players:%d ",nJugadores);
    printf("\n");

    for(i=0;i<nJugadores;i++){
        printf("Name of Player: %s\t" , listaJugadores[i].nombre);
        printf(" Army Color: %s\t" , imprimirColor(listaJugadores[i]));
        printf(" Number of Cards:%d \t" , listaJugadores[i].numCartas);
        printf(" List of Cards: ");
        printf("\n");
        /*EXAMPLE: Name of Player: Francesca Army Color: ROSSO Numero carte: 1 List of Cards: 13*/
    }

}

char* escribirNombre(){

    char nombre[DIM_NAME];
    int i=1, jugadores;
    jugadores=cantidadJugadores();

    //Creating names in an list for using it later
    char listaNombres[N_MAX_JUGADORES][DIM_NAME]={
            "Andres",
            "Alvaro",
            "Ivan",
            "Adrian",
            "Fabio",
            "Stefano"
    };

    //Assigning a name to the person in the card
    strcpy(nombre , listaNombres[generateRandom(0,N_MAX_JUGADORES-1)]);

    return nombre;
}

char* imprimirColor(Persona jugador){
    char* color="";

    if(jugador.color==0){
        strcpy(color,"ROJO");
    }
    if(jugador.color==1){
        strcpy(color,"VERDE");
    }
    if(jugador.color==2){
        strcpy(color,"AMARILLO");
    }
    if(jugador.color==3){
        strcpy(color,"VIOLETA");
    }
    if(jugador.color==4){
        strcpy(color,"AZUL");
    }
    if(jugador.color==5){
        strcpy(color,"NEGRO");
    }

    return color;
}

int contadorCartas(Lista * lista){
    int counter = 0;
    Carta * it = lista->first;
    while(it != NULL){
        counter++;
        it=it->next;
    }
    return counter;
}

int numeroArmadasIniciales(int nJugadores){
    int armadas;

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
int empiezaPrimero(int nJugadores){
    return generateRandom(0,nJugadores);
}

/**
 * With this function, we know how many players are playing
 * @return random number of players (int)
 */
int cantidadJugadores(){
    return generateRandom(3,6);
}

_Bool listaVacia(Lista *lista){
    if(lista->first==NULL)//se la lista è vuota
        return true;
    else
        return false;
}

_Bool isAdjacent(int idFirst, int idSecond){
    return t[idFirst][idSecond];
}

int generateRandom(int min, int max){
    return min + rand()%(max-min+1);
}

void generateSeed(){
    srand(time(NULL));
}

