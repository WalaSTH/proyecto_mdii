#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

int main() {
    Grafo G = ConstruccionDelGrafo();

    // for (size_t i = 0; i<G->n_vertices; ++i){
    //     printf("%u %u\n", G->nameGrades[2*i], G->nameGrades[2*i+1]);
    //     for (size_t j = 0; j < G->nameGrades[2*i+1]; ++j){
    //         printf("Vecino de %u numero %u es: %u \n", G->nameGrades[2*i], j, G->vecinos[i][j]);
    //     }
    //     printf("\n");
    // }

    DestruccionDelGrafo(G);
    G = NULL;
    return 0;
}

