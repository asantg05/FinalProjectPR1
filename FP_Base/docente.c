#include "docente.h"
#include "creacionListas.h"
#include "territorios.h"

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
    //vaciarBarajas(jugadores,nJugadores);
    //preparacionArmadas(territorios, jugadores, nJugadores);

    //-----REINFORCEMENT------//
    turno(territorios,jugadores,nJugadores);

    //IMPRESIONES
    //imprimirListaCartas(&mazo);
    /*for(i=0;i<nJugadores;i++){
        printf("\n-----Jugador %d------" , jugadores[i].id);
        imprimirListaCartas(&jugadores[i].listaCartas);
    }*/
    imprimirInicio(&mazo,jugadores,nJugadores);
    imprimirTerritorios(territorios);
    //imprimirArmadas(jugadores,nJugadores);

}

void turno(Territorio *territorios, Persona *listaJugadores, int nJugadores){
    int contadorJugador=0;

    do{
        reforzamiento(territorios,listaJugadores,nJugadores,contadorJugador);
        //batalla
        //colocacion
        contadorJugador++;
    }while (contadorJugador<nJugadores);

};

/**
 * This is the first phase of each turn of the game
 * @param territorios
 * @param listaJugadores
 * @param nJugadores
 */
void reforzamiento(Territorio *territorios, Persona *listaJugadores, int nJugadores, int contadorJugador){
    int armsExtra, i=0, territorioElegido=0, inputArmadas=0, armadasAcumuladas=0;
    _Bool esMiTerritorio=false;

    printf("\n----------RISIKA STARTS-----------");
    do{
        printf("\nPlayer[%d]: %s", listaJugadores[contadorJugador].id, listaJugadores[contadorJugador].nombre);
        printf("\nTerritories: ");
        for (i = 0; i < N_MAX_TERRITORIOS; i++) {//We show the territories to each player
            if (territorios[i].prop == listaJugadores[contadorJugador].id) {
                printf("%d,", territorios[i].id); //0,6,12
            }
        }
        printf("(%d)", listaJugadores[contadorJugador].numTerritorios);//and we show the amount at the end

        armsExtra=armadasExtra(listaJugadores,contadorJugador);//We let know the user how many armies he has
        printf("\nExtra Armies: %d",(armsExtra-armadasAcumuladas));

        //----inputTerritory----//
        do {//Rules each insertion of armies
            printf("\nInsert Territory: "); //Insert the territory
            scanf("%d", &territorioElegido);

            if (inputNoValido(territorioElegido)) {//If it's an incorrect input, go back to scanf()
                printf("\nWrite a property between 0 and 25");
            } else {
                esMiTerritorio = miTerritorio(territorioElegido, contadorJugador, territorios, listaJugadores,
                                              nJugadores);
                if (esMiTerritorio == false) {//If it isn't his territory, go back to the scanf()
                    printf("\nWrite a territory of your property!");
                }
            }
        } while (esMiTerritorio == false);

        //----inputArmies----//
        do {//Checks if the armies that will be added, are between 1-armsExtra
            printf("\nTerritory[%d] - insert armies: ", territorios[territorioElegido].id);
            scanf("%d", &inputArmadas); //1,2,3

            if (inputArmadas > armsExtra || inputArmadas < 1) {
                printf("\nYou can only add 1-%d armies",armsExtra);
            }

        } while (inputArmadas>armsExtra || inputArmadas<0);

        territorios[territorioElegido].numArmadas += inputArmadas;//Adding armies to territories
        listaJugadores[contadorJugador].numArmadas -= inputArmadas;//Removing armies of players
        armadasAcumuladas += inputArmadas;//input=2 --> armAcum=2

        //When the armies are greater than the extra armies, we return to the scanf on this way
        if(armadasAcumuladas>armsExtra){
            armadasAcumuladas-=inputArmadas;//Discounting the wrong input armies
            printf("\nYou only have %d armies" , (armsExtra-armadasAcumuladas));
        }

        //Rules each turn of the players
        if (armadasAcumuladas == armsExtra) {
            contadorJugador++;//It goes to the next turn
            armadasAcumuladas = 0;//This value it's refreshed because it changes on each iteration
        }

        imprimirArmadas(listaJugadores,nJugadores);
        imprimirTerritorios(territorios);
        printf("\n-----------------");

    }while (contadorJugador<nJugadores);
}

/**
 * This method let us know our extra armies
 * @param listaJugadores
 * @param nJugadores
 * @param contadorJugador
 * @return amount of extra armies
 */
int armadasExtra(Persona *listaJugadores, int contadorJugador){
    int arms=0;

    arms=listaJugadores[contadorJugador].numTerritorios/3;//5:3= 1 armada extra
    return arms;
}

/**
 * We use this method for adding the armies before the start of the game
 * @param territorios
 * @param listaJugadores
 * @param nJugadores
 */
void preparacionArmadas(Territorio *territorios, Persona *listaJugadores, int nJugadores) {
    int i = 0, j = 0, contadorJugador = 0, territorioElegido = 0, numArmadasInsertadas = 0, armadasAcumuladas = 0;
    int armadasIniciales, counter=0, nRondas, armadasFinales=0, inputFinal=0;
    _Bool esMiTerritorio = false;

    armadasIniciales=numeroArmadasIniciales(nJugadores); //We use this for controlling the number of rounds in the initial reinforcement

    ////In this part, we assign 1 army to each territory and discount one army of each player (20 armies - 5 territories = 15 armies)
    for (i = 0; i < N_MAX_TERRITORIOS; i++) {
        for (j = 0; j < nJugadores; j++) {
            if (territorios[i].prop == listaJugadores[j].id) {
                listaJugadores[j].numArmadas--;
                territorios[i].numArmadas++;
                armadasIniciales--; //16,15,14,13 --> 15 (5 territorios)
            }
        }
    }

    //Let's do the Distribution
    do{//Rounds of the Initial Reinforcement --> numeroRondas()
        do {//Control of each turn
            //If the amount of armies is 0, it goes to the next player
            if(listaJugadores[contadorJugador].numArmadas==0){
                contadorJugador++;
            }else{//If the armies are !=0, enters here
                //If the armies are less than 3 armies
                if(listaJugadores[contadorJugador].numArmadas<3){
                    armadasFinales=listaJugadores[contadorJugador].numArmadas;

                    //We show only the players with less than 3 armies
                    printf("\n------------\n");
                    printf("Player[%d]: %s", listaJugadores[contadorJugador].id, listaJugadores[contadorJugador].nombre);
                    printf("\nYou can only add %d to your territories" , armadasFinales);

                    do {//Rules each insertion of armies
                        printf("\nYour territories are: ");//Here, we show the territories of each player
                        for (i = 0; i < N_MAX_TERRITORIOS; i++) {
                            if (territorios[i].prop == listaJugadores[contadorJugador].id) {
                                printf("%d,", territorios[i].id); //0,6,12
                            }
                        }

                        printf("\nInsert Territory: "); //Insert the territory
                        scanf("%d", &territorioElegido);

                        if (inputNoValido(territorioElegido)) {//If it's an incorrect input, go back to scanf()
                            printf("\nWrite a property between 0 and 25");
                        } else {
                            esMiTerritorio = miTerritorio(territorioElegido, contadorJugador, territorios, listaJugadores,
                                                          nJugadores);
                            if (esMiTerritorio == false) {//If it isn't his territory, go back to the scanf()
                                printf("\nWrite a territory of your property!");
                            }
                        }
                    } while (esMiTerritorio == false);

                    do {//Checks if the armies that will be added, are between 1-3
                        printf("\nTerritory[%d] - insert armies: ", territorios[territorioElegido].id);
                        scanf("%d", &inputFinal); //1,2,3

                        if (inputFinal > 3 || inputFinal < 1) {
                            printf("\nYou can only add %d or less armies" , armadasFinales);
                        }

                    } while (inputFinal>armadasFinales || inputFinal<0);//armadasFinales=2

                    territorios[territorioElegido].numArmadas += inputFinal;//Adding armies to territories
                    listaJugadores[contadorJugador].numArmadas -= inputFinal;//Removing armies of players

                    imprimirArmadas(listaJugadores,nJugadores);
                    imprimirTerritorios(territorios);

                }else{//If the armies are > 3

                    //Here we show the players with more than 3 armies
                    //Let's show each player of the game
                    printf("\n------------\n");
                    printf("Player[%d]: %s", listaJugadores[contadorJugador].id, listaJugadores[contadorJugador].nombre);
                    printf("\nCurrently, you have %d armies, CHOOSE the territory for adding 1-3 armies", (3 - armadasAcumuladas));
                    //we show first, the number of armies and thenm which territory you want to choose

                    do {//Rules each insertion of armies
                        printf("\nYour territories are: ");//Here, we show the territories of each player
                        for (i = 0; i < N_MAX_TERRITORIOS; i++) {
                            if (territorios[i].prop == listaJugadores[contadorJugador].id) {
                                printf("%d,", territorios[i].id); //0,6,12
                            }
                        }

                        printf("\nInsert Territory: "); //Insert the territory
                        scanf("%d", &territorioElegido);

                        if (inputNoValido(territorioElegido)) {//If it's an incorrect input, go back to scanf()
                            printf("\nWrite a property between 0 and 25");
                        } else {
                            esMiTerritorio = miTerritorio(territorioElegido, contadorJugador, territorios, listaJugadores,
                                                          nJugadores);
                            if (esMiTerritorio == false) {//If it isn't his territory, go back to the scanf()
                                printf("\nWrite a territory of your property!");
                            }
                        }
                    } while (esMiTerritorio == false);

                    do {//Checks if the armies that will be added, are between 1-3
                        printf("\nTerritory[%d] - insert armies: ", territorios[territorioElegido].id);
                        scanf("%d", &numArmadasInsertadas); //1,2,3

                        if (numArmadasInsertadas > 3 || numArmadasInsertadas < 1) {
                            printf("\nYou can only add 1-3 armies");
                        }

                    } while (numArmadasInsertadas>3 || numArmadasInsertadas<0);

                    territorios[territorioElegido].numArmadas += numArmadasInsertadas;//Adding armies to territories
                    listaJugadores[contadorJugador].numArmadas -= numArmadasInsertadas;//Removing armies of players
                    armadasAcumuladas += numArmadasInsertadas;//input=2 --> armAcum=2

                    //When the armies are greater than 3, we return to the scanf on this way
                    if(armadasAcumuladas>3){
                        armadasAcumuladas-=numArmadasInsertadas;//Discounting the wrong input armies
                        printf("\nYou only have %d armies" , (3-armadasAcumuladas));
                    }

                    //Rules each turn of the players
                    if (armadasAcumuladas == 3) {
                        contadorJugador++;//It goes to the next turn
                        armadasAcumuladas = 0;//This value it's refreshed because it changes on each iteration
                    }

                    imprimirArmadas(listaJugadores,nJugadores);
                    imprimirTerritorios(territorios);
                }//If the armies are > 3

            }//If the armies !=0

        } while (contadorJugador < nJugadores);

        contadorJugador=0;//We refresh the counter of the players
        nRondas=numeroRondas(nJugadores);
        counter++;
    }while(counter<nRondas);
}

/**
 * This function is used for knowing the number of rounds in the initial reinforcement.
 * 3 Players = 9 Rounds
 * 4 Players = 8 Rounds
 * 5 Players = 7 Rounds
 * 6 Players = 6 Rounds
 * @param nJugadores
 * @return
 */
int numeroRondas(int nJugadores){
    int rondas;

    if(nJugadores==3){
        rondas=9; //35
    }
    else if(nJugadores==4){
        rondas=8; //30
    }
    else if(nJugadores==5){
        rondas=7; //25
    }
    else{
        rondas= 6; //20
    }

    return rondas;
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

