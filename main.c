#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"


static void dumpGrafo(Grafo G) {
    u32 nroVertices = NumeroDeVertices(G);
    u32 nroLados = NumeroDeLados(G);
    u32 delta = Delta(G);

    printf("Grafo con %u vértices, %u lados, delta %u\n",
        nroVertices, nroLados, delta);

    for (u32 i = 0; i < nroVertices; i++) {
        printf("\n===== Vértice %u =====\n", i);
        printf("Nombre: %u\nGrado: %u\n", Nombre(i, G), Grado(i, G));
        printf("Vecinos: (índice: nombre)\n");
        for (u32 j = 0; j < Grado(i, G); j++) {
            u32 indVecino = IndiceONVecino(j, i, G);
            printf(" (%u: %u) ", indVecino, Nombre(indVecino, G));
        }
        printf("\n");
    }
}

static bool ColoreoEsPropio(u32 *Coloreo, Grafo G) {
    bool esPropio = true;
    u32 nroVertices = NumeroDeVertices(G);
    for (u32 x = 0; x < nroVertices && esPropio; ++x) {
        for (u32 y = 0; y < Grado(x, G) && esPropio; ++y) {
            esPropio = Coloreo[x] != Coloreo[IndiceONVecino(y, x, G)];
        }
    }
    return esPropio;
}

static void testBipartito(Grafo G) {
    u32 *Coloreo = Bipartito(G);

    // Chequeamos que el grafo sea bipartitio.
    if (!Coloreo) {
        printf("No es bipartito\n");
    } else {
        printf("Es bipartito\n");

        // Chequeamos que el coloreo sea propio.
        if (ColoreoEsPropio(Coloreo, G)) {
            printf("El coloreo es propio\n");
        } else {
            printf("El coloreo no es propio\n");
        }
    }

    free(Coloreo);
    Coloreo = NULL;
}

static void testGreedy(Grafo G) {
    u32 nroVertices = NumeroDeVertices(G);
    u32 *Coloreo=NULL, *Orden=NULL;
    Coloreo = calloc(nroVertices, sizeof(u32));
    Orden   = calloc(nroVertices, sizeof(u32));

    for (u32 i = 0; i < nroVertices; ++i) {
        Orden[i] = i;
    }

    clock_t t = clock();
    u32 nroColores = Greedy(G, Orden, Coloreo);
    t = clock() - t;
    double timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("Greedy en orden natural: %u colores en %f segundos\n",
            nroColores, timeTaken);

    if (ColoreoEsPropio(Coloreo, G)) {
        printf("El coloreo es propio\n");
    } else {
        printf("El coloreo no es propio\n");
    }

    free(Coloreo);
    Coloreo = NULL;
    free(Orden);
    Orden = NULL;
}

void testOrdenFromKey(void) {
    u32 rango = 3;
    u32 *Key=NULL, *Orden=NULL;
    Orden = calloc(rango+1, sizeof(u32));
    Key   = calloc(rango+1, sizeof(u32));
    Key[0] = 2;
    Key[1] = 3;
    Key[2] = 0;
    Key[3] = 1;

    char ordenado = OrdenFromKey(rango, Key, Orden);
    if (!ordenado) {
        for(u32 i = 0; i < rango+1; ++i){
            printf("%u ", Orden[i]);
        }
        printf("\n");
    }

    free(Key);
    Key = NULL;
    free(Orden);
    Orden = NULL;
}

int main() {
    Grafo G = ConstruccionDelGrafo();
    // dumpGrafo(G);

    // testBipartito(G);
    // testGreedy(G);

    testOrdenFromKey();

    DestruccionDelGrafo(G);
    G = NULL;
    return 0;
}
