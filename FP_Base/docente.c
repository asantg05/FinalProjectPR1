#include "docente.h"
#include "creacionListas.h"
#include "territorios.h"
#include "juego.h"

void risika(){

    Persona *jugadores; //Players of the game
    Territorio *territorios; //Territories of the game
    Lista mazo; //In this list, we will do all the changes
    int nJugadores, i;

    /*¡¡IMPORTANT!! --> In this part, my PC is not able to charge correctly the randomly amount of players
     * and the first player of the game (In the Fabio's PC worked perfectly). So we finally decided that the best
     * option would be that I could continue programming stablishing a certain number for each fields. For example: 6 players
     * and the player with the Id=1 starts the game*/
    nJugadores= 4;//cantidadJugadores();//3,4,5,6
    jugadores = creacionPersonas(nJugadores); //We save in dinamic vector the list of players before initializing

    inicializaLista(&mazo);//initializing mazzo
    inicializarBarajas(jugadores,nJugadores); //Initializing list of each player

    //-----INITIAL PHASE------//
    crearTodasLasCartas(&mazo); //Let's create the 26 cards (creacionListas.c)
    repartirTerritorio(&mazo);//Charging the territories of each card (creacionListas.c)
    repartirCartas(&mazo , jugadores, nJugadores);//Charging owners of each card (creacionListas.c)
    repartirEquipo(&mazo);//BIRRA, CAFE, VINO (creacionListas.c)
    barajarMazo(&mazo);//Changing positions of the cards in the mazo (creacionListas.c)
    actualizarNumeroCartasPlayerN(&mazo,jugadores,nJugadores);//Knowledge of the number of cards of each player (creacionListas.c)
    insertarEnBaraja(&mazo,jugadores,nJugadores);//Charging the cards of each player (creacionListas.c)
    territorios=listaTerritorios();//Let's create the list of Territories (territorios.c)
    asignarTerritorios(territorios,jugadores,nJugadores);//Assigning the Territories to players (territorios.c)
    vaciarBarajas(jugadores,nJugadores);//When we have distributed all the cards for knowing the territories, we return the cards to mazo

    //-----REINFORCEMENT------//
    preparacionArmadas(territorios, jugadores, nJugadores);//It happens before the game begins (juego.c)
    //turno(territorios,jugadores,nJugadores);

    //-----IMPRESIONES--------//

    //imprimirInicio(&mazo,jugadores,nJugadores);
    //imprimirTerritorios(territorios);
    //imprimirArmadas(jugadores,nJugadores);

}

void turno(Territorio *territorios, Persona *listaJugadores, int nJugadores){
    int contadorJugador=0;

    do{
        reforzamiento(territorios,listaJugadores,nJugadores,contadorJugador);//First phase of the turn
        //batalla
        //colocacion
        contadorJugador++;
    }while (contadorJugador<nJugadores);

}

void batalla(Territorio *territorios, Persona *listaJugadores, int nJugadores, int contadorJugador){
    _Bool atacar=false;

    do{

    }while(!atacar);
}

/**
 * We will use this method for presenting the players
 * @param lista
 * @param listaJugadores
 * @param nJugadores
 */
void imprimirInicio(Lista* lista, Persona* listaJugadores ,int nJugadores){
    int i,j=0, k=0;

    //printf("\n----------");
    printf("\nNumber of Players:%d ",nJugadores);
    printf("\n");

    for(i=0;i<nJugadores;i++){
        printf("Name of Player (ID=%d): %s\t" , listaJugadores[i].id ,listaJugadores[i].nombre);
        printf(" Army Color: %s\t" , listaJugadores[i].color);
        printf(" Number of Cards:%d \t" , listaJugadores[i].numCartas);
        printf(" List of Cards: ");
        imprimirIdsCartas(&listaJugadores[i].listaCartas, nJugadores);
        printf("\n");
        /*EXAMPLE: Name of Player: Francesca Army Color: ROSSO Numero carte: 1 List of Cards: 13,5,6,4*/
    }

}

/**
 * This method is used for counting the armies of each player in the game
 * @param listaJugadores
 * @param nJugadores
 */
void imprimirArmadas(Persona* listaJugadores, int nJugadores){
    int i=0;

    printf("\n");
    for(i=0;i<nJugadores;i++){
        printf("Jugador[%d] Armadas:%d Territories:%d\n" , listaJugadores[i].id ,listaJugadores[i].numArmadas,
               listaJugadores[i].numTerritorios);
    }

}

/**
 * This method create the players of the dinamic vector "jugadores" in risika() method
 * @param dimensionVector
 * @return
 */
Persona* creacionPersonas(int dimensionVector){
    int id=0, i=0, primerJugador, j=0;

    Persona *jugadoresInicio;
    Persona *jugadoresOrdenados;

    jugadoresInicio=malloc(sizeof(Persona)*dimensionVector);
    jugadoresOrdenados=malloc(sizeof(Persona)*dimensionVector);

    jugadoresInicio[dimensionVector];
    jugadoresOrdenados[dimensionVector];

    for(i=0;i<dimensionVector;i++){ //Assigning id to Players since 0
        jugadoresInicio[i].id=id;
        id++;
    }

    for(i=0;i<dimensionVector;i++){ //Assigning id to Players since 0
        jugadoresOrdenados[i].id=0;
    }

    /*It means that the one who starts the game, it's the element 1 of the dinamic vector "jugadores" and not
     * the id of the player*/
    primerJugador = empiezaPrimero(dimensionVector); //0,1,2,3,4,5

    jugadoresOrdenados[0].id=primerJugador;   //2

    for(j=0;j<dimensionVector;j++){
        jugadoresOrdenados[j].id=(jugadoresOrdenados[0].id+j)%(dimensionVector); //0,1,2,3,4,5 --> jugadoresOrdenados: 2,3,4,5,0,1
    }

    for(i=0;i<dimensionVector;i++){
        jugadoresOrdenados[i].numArmadas=numeroArmadasIniciales(dimensionVector);//We assign the initial number of ARMIES to the players
        jugadoresOrdenados[i].numCartas=0;//We initialize the NUMBER of CARDS the player have
    }

    //We assign random NAMES to the players
    strcpy(jugadoresOrdenados[0].nombre , "Andres");
    strcpy(jugadoresOrdenados[1].nombre , "Manuel");
    strcpy(jugadoresOrdenados[2].nombre , "Ivan");
    strcpy(jugadoresOrdenados[3].nombre , "Adrian");
    strcpy(jugadoresOrdenados[4].nombre , "Alvaro");
    strcpy(jugadoresOrdenados[5].nombre , "Fabio");

    //We assign random COLORS to the players: ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO
    strcpy(jugadoresOrdenados[0].color, "ROSSO");
    strcpy(jugadoresOrdenados[1].color, "VERDE");
    strcpy(jugadoresOrdenados[2].color, "GIALLO");
    strcpy(jugadoresOrdenados[3].color, "VIOLA");
    strcpy(jugadoresOrdenados[4].color, "BLU");
    strcpy(jugadoresOrdenados[5].color, "NERO");

    //Let's initialize the number of territories of each player
    for(i=0;i<dimensionVector;i++){
        jugadoresOrdenados[i].numTerritorios=0;
    }

    return jugadoresOrdenados;
}

/**
 * This method let us know the initial armies of the players at the beginning of the game
 * @param nJugadores
 * @return
 */
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
    return generateRandom(N_MIN_JUGADORES,N_MAX_JUGADORES);
}



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

_Bool isAdjacent(int idFirst, int idSecond){
    return t[idFirst][idSecond];
}

int generateRandom(int min, int max){
    return min + rand()%(max-min+1);
}

void generateSeed(){
    srand(time(NULL));
}

