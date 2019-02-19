#include "docente.h"
#include "creacionListas.h"
#include "territorios.h"

void risika(){

    Persona *jugadores; //Players of the game
    Territorio *territorios; //Territories of the game
    Lista mazo; //In this list, we will do all the changes
    int nJugadores, i;

    nJugadores= cantidadJugadores();//3,4,5,6
    jugadores = creacionPersonas(nJugadores); //We save in dinamic vector the list of players before initializing

    inicializaLista(&mazo);//initializing mazzo
    inicializarBarajas(jugadores,nJugadores); //Initializing list of each player

    //-----INITIAL PHASE------
    crearTodasLasCartas(&mazo); //Let's create the 26 cards (creacionListas.c)
    repartirTerritorio(&mazo);//Charging the territories of each card (creacionListas.c)
    repartirCartas(&mazo , jugadores, nJugadores);//Charging owners of each card (creacionListas.c)
    repartirEquipo(&mazo);//BIRRA, CAFE, VINO (creacionListas.c)
    barajarMazo(&mazo);//Changing positions of the cards in the mazo (creacionListas.c)
    actualizarNumeroCartasPlayerN(&mazo,jugadores,nJugadores);//Knowledge of the number of cards of each player (creacionListas.c)
    insertarEnBaraja(&mazo,jugadores,nJugadores);//Charging the cards of each player (creacionListas.c)
    territorios=listaTerritorios();//Let's create the list of Territories (territorios.c)
    asignarTerritorios(territorios,jugadores,nJugadores);//Assigning the Territories to players (territorios.c)
    //vaciarBarajas(jugadores,nJugadores);
    //repartirArmadas(territorios,jugadores,nJugadores);

    //imprimirInicio(&mazo,jugadores,nJugadores);
    //-----REINFORCEMENT------


    //IMPRESIONES
    imprimirListaCartas(&mazo);
    /*for(i=0;i<nJugadores;i++){
        printf("\n-----Jugador %d------" , jugadores[i].id);
        imprimirListaCartas(&jugadores[i].listaCartas);
    }*/
    imprimirInicio(&mazo,jugadores,nJugadores);
    imprimirTerritorios(territorios);
    //imprimirArmadas(jugadores,nJugadores);

}

void repartirArmadas(Territorio* territorios , Persona* listaJugadores, int nJugadores){
    int i=0,j=0, armadasARepartir=3, contadorJugador=0, territorioElegido=0, insertarArmadas=0;
    int listaTerritorios[N_MAX_TERRITORIOS];
    _Bool esMiTerritorio=false;

    for(i=0;i<N_MAX_TERRITORIOS;i++){//In this part, we assign 1 army to each territory and...
        for(j=0;j<nJugadores;j++){//discount one army of each player (20 armies - 5 territories = 15 armies)
            if(territorios[i].prop==listaJugadores[j].id){
                listaJugadores[j].numArmadas--;
                territorios[i].numArmadas++;
            }
        }
    }

    do{
        printf("\n------------\n");
        //Let's show each player of the game
        printf("Player[%d]: %s" , listaJugadores[contadorJugador].id, listaJugadores[contadorJugador].nombre);
        printf("\nCurrently, you have %d armies, CHOOSE the territory for adding 1-3 armies" , armadasARepartir);
        //we show first, the number of armies and thenm which territory you want to choose
        do{
            printf("\nYour territories are: ");//Here, we show the territories of each player
            for(i=0;i<N_MAX_TERRITORIOS;i++){
                if(territorios[i].prop==listaJugadores[contadorJugador].id){
                    printf("%d," , territorios[i].id); //0,6,12
                }
            }

            printf("\nInsert Territory: "); //Insert the territory
            scanf("%d" , &territorioElegido);

            if(inputNoValido(territorioElegido)){//If it's an incorrect input, go back to scanf()
                printf("\nWrite a territory of your property!");
            }else {
                esMiTerritorio = miTerritorio(territorioElegido, contadorJugador, territorios, listaJugadores, nJugadores);
                if (esMiTerritorio == false) {//If it isn't his territory, go back to the scanf()
                    printf("\nWrite a territory of your property!");
                }
            }

            armadasARepartir=3;

            while((insertarArmadas<3) && (armadasARepartir<=3)){//1,2,3
                printf("\nTerritory[%d], insert armies:",territorios[territorioElegido].id); //CHINA=2
                scanf("%d" , &insertarArmadas); //1,2,3  //4

                territorios[territorioElegido].numArmadas+=insertarArmadas;//1+4
                armadasARepartir-=insertarArmadas;//3-4 = -1
                listaJugadores[contadorJugador].numArmadas-=insertarArmadas;//19-4
            }
            //armadasARepartir=0,1,2;

        }while(esMiTerritorio==false && !inputNoValido(territorioElegido) && armadasARepartir<4);

        contadorJugador++;
    }while(contadorJugador<nJugadores);

}

_Bool miTerritorio(int territorioElegido, int idJugador, Territorio* territorios , Persona* listaJugadores, int nJugadores){

    if(territorios[territorioElegido].prop==listaJugadores[idJugador].id){
        return true;
    }else{
        return false;
    }

}

_Bool inputNoValido(int territorioElegido){

    if(territorioElegido>N_MAX_TERRITORIOS && territorioElegido<0){
        return true;
    }
    return false;
}

void imprimirInicio(Lista* lista, Persona* listaJugadores ,int nJugadores){
    int i,j=0, k=0;

    printf("\n----------");
    printf("\nNumber of Players:%d ",nJugadores);
    printf("\n");

    for(i=0;i<nJugadores;i++){
        printf("Name of Player (ID=%d): %s\t" , listaJugadores[i].id ,listaJugadores[i].nombre);
        printf(" Army Color: %s\t" , listaJugadores[i].color);
        printf(" Number of Cards:%d \t" , listaJugadores[i].numCartas);
        printf(" List of Cards: ");
        imprimirIds(&listaJugadores[i].listaCartas, nJugadores);
        printf("\n");
        /*EXAMPLE: Name of Player: Francesca Army Color: ROSSO Numero carte: 1 List of Cards: 13,5,6,4*/
    }

}

void imprimirArmadas(Persona* listaJugadores, int nJugadores){
    int i=0;

    printf("\n");
    for(i=0;i<nJugadores;i++){
        printf("Jugador[%d] Armadas:%d Territories:%d\n" , listaJugadores[i].id ,listaJugadores[i].numArmadas,
                listaJugadores[i].numTerritorios);
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

    for(i=0;i<dimensionVector;i++){ //Assigning id to Players since 0
        jugadoresInicio[i].id=id;
        id++;
    }

    for(i=0;i<dimensionVector;i++){ //Assigning id to Players since 0
        jugadoresOrdenados[i].id=0;
    }

    //Let's see who goes first
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

