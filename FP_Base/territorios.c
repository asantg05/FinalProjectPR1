
#include "docente.h"
#include "territorios.h"
/**
 * Used for assigning the owner of each territory when the mazo has already been shuffled.
 * We take the owner of the first distribution of cards.
 * @param territorios
 * @param jugadores
 * @param nJugadores
 */
void asignarTerritorios(Territorio *territorios, Persona *jugadores, int nJugadores){
    int j=0;
    Carta* it=NULL;//Initializing the iterator

    for(j=0;j<nJugadores;j++){
        it = jugadores[j].listaCartas.first;//Assigning the first of the list

        while(it!=NULL){
            territorios[it->inf.numeroCarta].prop = jugadores[j].id;//Charging the owner of each territory
            jugadores[j].numTerritorios++;

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
/**
 * Initialize all the parameters of the Territory (ID,Name,A
 * @return Territorio
 */
Territorio* listaTerritorios(){
    Territorio* territorios;
    int i=0;

    territorios=malloc(sizeof(Territorio)*N_MAX_TERRITORIOS);
    territorios[N_MAX_TERRITORIOS];

    for(i=0;i<N_MAX_TERRITORIOS;i++){   //We Initialize the territories
        territorios[i].id=i;
        territorios[i].numArmadas=0;
        territorios[i].prop=0;
        strcpy(territorios[i].nombre,"");
        strcpy(territorios[i].nombreTerritorio,"");
    }

    escribirNombreTerritorios(territorios);

    return territorios;
}

/**
 * Write the name of each territory
 * @param territorios
 */
void escribirNombreTerritorios(Territorio territorios[]){
    strcpy(territorios[0].nombreTerritorio, "Psicologia");
    strcpy(territorios[1].nombreTerritorio, "Filosofia");
    strcpy(territorios[2].nombreTerritorio, "Pedagogia");
    strcpy(territorios[3].nombreTerritorio, "Lettere");
    strcpy(territorios[4].nombreTerritorio, "Lingue");
    strcpy(territorios[5].nombreTerritorio, "Economia");
    strcpy(territorios[6].nombreTerritorio, "Scienze Politiche");
    strcpy(territorios[7].nombreTerritorio, "Giurisprudenza");
    strcpy(territorios[8].nombreTerritorio, "Odontoiatria");
    strcpy(territorios[9].nombreTerritorio, "Infermieristica");
    strcpy(territorios[10].nombreTerritorio, "Medicina");
    strcpy(territorios[11].nombreTerritorio, "Scienze Motorie");
    strcpy(territorios[12].nombreTerritorio, "CTF");
    strcpy(territorios[13].nombreTerritorio, "Tossicologia");
    strcpy(territorios[14].nombreTerritorio, "Biologia");
    strcpy(territorios[15].nombreTerritorio, "Scienze della Natura");
    strcpy(territorios[16].nombreTerritorio, "Farmacia");
    strcpy(territorios[17].nombreTerritorio, "Ing. Chimica");
    strcpy(territorios[18].nombreTerritorio, "Ing. Meccanica");
    strcpy(territorios[19].nombreTerritorio, "Ing. Elettronica");
    strcpy(territorios[20].nombreTerritorio, "Architettura");
    strcpy(territorios[21].nombreTerritorio, "Ing. Civile");
    strcpy(territorios[22].nombreTerritorio, "Chimica");
    strcpy(territorios[23].nombreTerritorio, "Fisica");
    strcpy(territorios[24].nombreTerritorio, "Informatica");
    strcpy(territorios[25].nombreTerritorio, "Matematica");

}

/**
 * Print all the territories of the game
 * @param a
 */
void imprimirTerritorios(Territorio a[]){
    int i;
    for(i=0;i<N_MAX_TERRITORIOS;i++){
        printf("\nID[%d]: %s - Armies:%d - Owner[#%d]: %s", a[i].id,a[i].nombreTerritorio,a[i].numArmadas,a[i].prop,a[i].nombre);
    }
}