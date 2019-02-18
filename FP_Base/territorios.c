
#include "docente.h"
#include "territorios.h"

void asignarTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores){
    int j=0;
    Carta* it=NULL;//Initializing the iterator

    for(j=0;j<nJugadores;j++){
        it = jugadores[j].listaCartas.first;//Assigning the first of the list

        while(it!=NULL){
            territorios[it->inf.numeroCarta].prop = jugadores[j].id;//Charging the owner of each territory

            it=it->next;//iterator++
        }
    }

    asignarNombreTerritorios(territorios,jugadores,nJugadores); //Charging the name of each player
}

void asignarNombreTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores){
    int i=0, j=0;

    for(i=0;i<N_MAX_TERRITORIOS;i++){
        for(j=0;j<nJugadores;j++){
            if(territorios[i].prop==jugadores[j].id){
                strcpy(territorios[i].nombre, jugadores[j].nombre);
            }
        }
    }
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
        printf("\nID:%d\tArmies:%d\tOwner[#%d]: %s", a[i].id,a[i].numArmadas,a[i].prop,a[i].nombre);
    }
}