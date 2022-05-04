#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"

int main() {
    Grafo G = ConstruccionDelGrafo();
    u32 vertices=NumeroDeVertices(G), lados=NumeroDeLados(G),
        delta=Delta(G);

    // printf("Grafo con %u vértices, %u lados, Delta %u\n",
    //     vertices, lados, delta);

    // for (u32 i = 0; i < vertices; i++) {
    //     printf("\n");
    //     printf("===== Vértice %u =====\n", i);
    //     printf("Nombre: %u\nGrado: %u\n", Nombre(i, G), Grado(i, G));
    //     printf("Vecinos: (índice: nombre)\n");
    //     for (u32 j = 0; j < Grado(i, G); j++) {
    //         printf(" (%u: %u),", IndiceONVecino(j, i, G),
    //                                Nombre(IndiceONVecino(j, i, G), G));
    //     }
    //     printf("\n");
    // }

    u32 *coloreo = Bipartito(G);

    // Chequeamos que el grafo sea bipartitio.
    if (coloreo == NULL) {
        printf("No es bipartito\n");
    } else {
        printf("Es bipartito\n");

        // Chequeamos que el coloreo sea propio.
        bool propio = true;
        for (u32 i = 0; i < vertices; ++i) {
            for (u32 j = 0; j < Grado(i, G); ++j) {
                if (coloreo[i] == coloreo[IndiceONVecino(j, i, G)]) {
                    propio = false;
                    break;
                }
            }
            if (!propio) break;
        }
        propio ? printf("El coloreo es propio\n")
               : printf("El coloreo no es propio\n");
    }

    DestruccionDelGrafo(G);
    G = NULL;
    return 0;
}
