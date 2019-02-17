#include "docente.h"


void risika(){

    Persona *jugadores;
    Territorio *territorios;
    int nJugadores, i;

    nJugadores= cantidadJugadores();//3,4,5,6
    jugadores = creacionPersonas(nJugadores); //We save in dinamic vector the list of players before initializing

    Lista mazo; //In this list, we will do all the changes
    Lista baraja; //This will be the list of each player

    inicializaLista(&mazo);
    inicializarBarajas(jugadores,nJugadores); //Initializing list of each player

    crearTodasLasCartas(&mazo); //Let's create the 26 cards

    repartirCartas(&mazo , jugadores, nJugadores);
    repartirTerritorio(&mazo);
    repartirEquipo(&mazo);
    actualizarNumeroCartasPlayerN(&mazo,jugadores,nJugadores);

    insertarEnBaraja(&mazo,jugadores,nJugadores);

    //Let's create the list of Territories
    territorios=listaTerritorios();
    //actualizarTerritorios(territorios,jugadores,nJugadores);

    //imprimirListaCartas(&mazo);
    /*for(i=0;i<nJugadores;i++){
        printf("\n-----Jugador %d------" , i);
        imprimirListaCartas(&jugadores[i].listaCartas);
    }*/
    imprimirInicio(&mazo,jugadores,nJugadores);
    //imprimirTerritorios(territorios);
}

void actualizarTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores){
    int n=0;

    /*while(n<26){
        if(territorios[n].id==jugadores[n].listaCartas[n]){ //Controlar n en el vector de Jugadores, poner otro indice
            territorios[n].id=jugadores[n].listaCartas[n];
            n++;
        }
    }*/
}

Territorio* listaTerritorios(){
    Territorio* territorios;
    int i=0;

    territorios=malloc(sizeof(Territorio)*N_MAX_TERRITORIOS);
    territorios[N_MAX_TERRITORIOS];

    for(i=0;i<N_MAX_TERRITORIOS;i++){   //We assign an ID
        territorios[i].id=i;
        territorios[i].numArmadas=0;
        territorios[i].prop=0;
        strcpy(territorios[i].nombre,"");
    }

    return territorios;
}

void imprimirTerritorios(Territorio a[]){
    int i;
    for(i=0;i<N_MAX_TERRITORIOS;i++){
        printf("\nID:%d\tArmies:%d\tOwner[#%d]:%s", a[i].id,a[i].numArmadas,a[i].prop,a[i].nombre);
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
        jugadoresOrdenados[i].numCartas=0;     //We initialize the NUMBER of CARDS the player have
    }

    //We assign random NAMES to the players
    strcpy(jugadoresOrdenados[0].nombre , "Andres");
    strcpy(jugadoresOrdenados[1].nombre , "Manuel");
    strcpy(jugadoresOrdenados[2].nombre , "Ivan");
    strcpy(jugadoresOrdenados[3].nombre , "Adrian");
    strcpy(jugadoresOrdenados[4].nombre , "Alvaro");
    strcpy(jugadoresOrdenados[5].nombre , "Fabio");

    //We assign random COLORS to the players: ROJO,VERDE,AMARILLO,VIOLETA,AZUL,NEGRO
    jugadoresOrdenados[0].color=ROJO;
    jugadoresOrdenados[1].color=VERDE;
    jugadoresOrdenados[2].color=AMARILLO;
    jugadoresOrdenados[3].color=VIOLETA;
    jugadoresOrdenados[4].color=AZUL;
    jugadoresOrdenados[5].color=NEGRO;


    return jugadoresOrdenados;
}

/*void addCartas(Lista *lista, Persona *jugadores, int nJugadores){
    Carta* it=lista->first;
    int i=0,n=0,j=0,contadorLista=0;

    while(it!=NULL){

        for(n=0;n<nJugadores;n++){  //It let us to check all the ID's
            if(it->inf.propietario.id==n){  //The card that is with id=0,1,2,3,4,5
                for(i=0;i<nJugadores;i++){ //It travels inside the vector of Jugadores
                    if(jugadores[i].id==n){ //The player that is with with id=0,1,2,3,4,5
                        //Let's add the card found in the only one space
                        jugadores[i].listaCartas[contadorLista]=it->inf.numeroCarta;
                        //A card of a player has been found, then we book another space
                        jugadores[i].listaCartas=realloc(jugadores[i].listaCartas, contadorLista*sizeof(int));
                        contadorLista++;
                    }
                }
            }
        }

        it=it->next;
    }
}*/

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
        it->inf.propietario=jugadores[k%nJugadores].id;
        it=it->next;
        k++;
    }
}

void actualizarNumeroCartasPlayerN(Lista *lista, Persona* jugadores, int nJugadores){
    Carta * it = lista->first;
    int i=0, n=0;

    while(it != NULL){

        for(n=0;n<nJugadores;n++){
            if(it->inf.propietario==n){
                for(i=0;i<nJugadores;i++){
                    if(jugadores[i].id==n){
                        jugadores[i].numCartas++;
                    }
                }
            }
        }

        it=it->next;
    }
}

//escribirNombre( )
/*
char* escribirNombre(int nJugadores){

    char nombre[DIM_NAME];
    int i=0, random=0,j=0;

    int *vectorAleatorios;
    vectorAleatorios=malloc(sizeof(int)*nJugadores);
    vectorAleatorios[nJugadores];

    random = generateRandom(0,N_MAX_JUGADORES-1);

    //Creating names in an list for using it later
    char listaNombres[N_MAX_JUGADORES][DIM_NAME]={
            "Andres",
            "Alvaro",
            "Ivan",
            "Adrian",
            "Fabio",
            "Stefano"
    };

    while(i<nJugadores){    //4
        if(vectorAleatorios[i]!=random){
            vectorAleatorios[i]=random;
            i++;
        }
    }//4,1,2,3

    //Assigning a name to the person in the card
    strcpy(nombre , listaNombres[vectorAleatorios[j]]);

    return nombre;
}*/

void imprimirVector(Persona a[] , int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("Player %d: %s----\tArmadas=%d" , a[i].id, a[i].nombre, a[i].numArmadas);
        printf("\n");
    }
}

void imprimirInicio(Lista* lista, Persona* listaJugadores ,int nJugadores){
    int i, numeroCartas=0, j=0, k=0;
    numeroCartas=contadorCartas(lista);

    printf("\n----------");
    printf("\nNumber of Players:%d ",nJugadores);
    printf("\n");

    for(i=0;i<nJugadores;i++){
        printf("Name of Player (ID=%d): %s\t" , listaJugadores[i].id ,listaJugadores[i].nombre);
        printf(" Army Color: %s\t" , imprimirColor(listaJugadores[i]));
        printf(" Number of Cards:%d \t" , listaJugadores[i].numCartas);
        printf(" List of Cards: ");
        imprimirIds(&listaJugadores[i].listaCartas, nJugadores);

        printf("\n");
        /*EXAMPLE: Name of Player: Francesca Army Color: ROSSO Numero carte: 1 List of Cards: 13,5,6,4*/
    }

}

void imprimirIds(Lista* baraja, int nJugadores){
    int i=0;

    Carta* it= NULL;
    it=baraja->first;

    while(it!=NULL){
            if(it!=NULL){
                printf("%d,", it->inf.numeroCarta);
                it=it->next;
            }
    }
}

void insertarEnBaraja(Lista* mazo, Persona* listaJugadores, int nJugadores){
    int i=0;

    Carta* it= NULL;
    it=mazo->first;

    while(it!=NULL){
        for(i=0;i<nJugadores;i++){
            if(it!=NULL){
                insertarEnTesta(&listaJugadores[i].listaCartas,it->inf);
                it=it->next;

            }
        }

    }
}



void inicializaLista(Lista *lista){
    lista->first=NULL;
}

void inicializarBarajas(Persona* jugadores, int nJugadores){
    int i=0;

    for(i=0;i<nJugadores;i++){
        jugadores[i].listaCartas.first=NULL;
    }

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

    return insertarEnTesta(lista, infoCarta);
}

void imprimirCarta(Informacion carta){
    printf("\nTerritory: %d Owner: %d Team: %d" ,carta.numeroCarta , carta.propietario, carta.equipo);
}

Informacion inicializarCarta(){
    Informacion iCarta;

    //Let's initialize all the variables of iCarta
    iCarta.propietario=0;
    iCarta.equipo=0;
    iCarta.numeroCarta=0;

    return iCarta;
}

/**
 * Function that let us to put a Card at the beginning of the list of cards
 * @param List of Cards
 * @param Information that is gonna be saved
 * @return The new card of the list
 */
Carta* insertarEnTesta(Lista *lista, Informacion infoCarta){

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
    return generateRandom(N_MIN_JUGADORES,N_MAX_JUGADORES);
}

_Bool listaVacia(Lista *lista){
    if(lista->first==NULL)//se la lista è vuota
        return true;
    else
        return false;
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

