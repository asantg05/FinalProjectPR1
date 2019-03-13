//
// Created by ANDRES on 13/03/2019.
//
#include "docente.h"
#include "juego.h"
#include "creacionListas.h"

/**
 * This is the first phase of each turn of the game, we can get the bonus armies
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

        listaJugadores[contadorJugador].numArmadas += inputArmadas;//First, Adding armies to players
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

                    //Let's controll the territory that is going to be choosed
                    territorioElegido=insertarTerritorio(territorios,listaJugadores,nJugadores,contadorJugador);

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
 * We use this method for controlling the territory that has been choosed
 * @param territorios
 * @param listaJugadores
 * @param nJugadores
 * @param contadorJugador
 * @return
 */
int insertarTerritorio(Territorio *territorios, Persona *listaJugadores, int nJugadores, int contadorJugador){
    int i=0, territorioElegido=0;
    _Bool esMiTerritorio=false;

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

    return territorioElegido;
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

/**
 * Checks if a Territory is of my property
 * @param territorioElegido
 * @param idJugador
 * @param territorios
 * @param listaJugadores
 * @param nJugadores
 * @return
 */
_Bool miTerritorio(int territorioElegido, int idJugador, Territorio* territorios , Persona* listaJugadores, int nJugadores){

    if(territorios[territorioElegido].prop==listaJugadores[idJugador].id){
        return true;
    }else{
        return false;
    }

}

/**
 * Checks if the Territory is between 0-25
 * @param territorioElegido
 * @return
 */
_Bool inputNoValido(int territorioElegido){

    if(territorioElegido>N_MAX_TERRITORIOS && territorioElegido<0){
        return true;
    }
    return false;
}

