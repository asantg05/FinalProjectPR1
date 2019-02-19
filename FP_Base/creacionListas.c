
#include "creacionListas.h"
#include "docente.h"


void inicializarBarajas(Persona* jugadores, int nJugadores){
    int i=0;

    for(i=0;i<nJugadores;i++){
        jugadores[i].listaCartas.first=NULL;
    }

}

void inicializaLista(Lista *lista){
    lista->first=NULL;
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

void barajarMazo(Lista* lista){
    int random=0, random2=0;

    Carta* it= lista->first;//Iterator used for going through the list
    Informacion* a=NULL;//we create a pointer of information for interchange the info
    Informacion* b=NULL;
    Informacion aux;

    while(it!=NULL){
        random=generateRandom(0,MAX_ID);//Used both of them for the method obtenerCarta()
        random2=generateRandom(0,MAX_ID);//

        a=obtenerCarta(lista,random); //Here we obtain the id of the cards
        b=obtenerCarta(lista,random2);

        aux=*a; //In this part we use the aux for interchange the info
        *a=*b; //We acces to the pointers with *
        *b=aux;

        it=it->next;//iterator++
    }

}

/**
 * Method used for obtaining the Information of a Cards
 * @param lista
 * @param id
 * @return All the Information of the card
 */
Informacion* obtenerCarta(Lista* lista, int id){
    Carta* it= lista->first;

    while(it!=NULL){ //5

        if(it->inf.numeroCarta==id){
            return &it->inf;
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

    /*while(it!=NULL){
        for(i=0;i<nJugadores;i++){
            if(it!=NULL){
                insertarEnTesta(&listaJugadores[i].listaCartas,it->inf);
                it=it->next;
            }
        }
    }
     */

    while(it!=NULL){
        for(i=0;i<nJugadores;i++){
            if(it!=NULL){
                if(listaJugadores[i].id==it->inf.propietario){
                    insertarEnTesta(&listaJugadores[i].listaCartas,it->inf);
                    it=it->next;
                }
            }
        }
    }
}

Carta* insertarEnTesta(Lista *lista, Informacion infoCarta){

    Carta* cartaNueva= NULL;
    cartaNueva = colocarCarta();

    cartaNueva->inf=infoCarta;//l'elemento da inserire prende il contatto passato come paramentro
    cartaNueva->next=lista->first;//la testa della lista diventa il next del nuovoElemento
    lista->first= cartaNueva;//la testa della lista diventa il next del nuovoElemento

    return cartaNueva;
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

void vaciarBarajas(Persona *jugadores, int nJugadores){
    int i=0;

    for(i=0;i<nJugadores;i++){
        vaciarListaCartas(&jugadores[i].listaCartas);
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
    lista->first=NULL;

    //printf("...");
}

void vaciarCarta(Carta *carta){
    free(carta);
    carta=NULL;
}

_Bool listaVacia(Lista *lista){
    if(lista->first==NULL)//se la lista è vuota
        return true;
    else
        return false;
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