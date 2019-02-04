#include "docente.h"

#include <stdio.h>

int main() {
    Lista* lista;

    inicializaLista(&lista);
    generateSeed();
    crearVariasCartas(&lista);


    return 0;
}