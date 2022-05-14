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

// void testOrdenFromKey(void) {
//     u32 n = 6;
//     u32 *Key=NULL;
//     Key   = calloc(n, sizeof(u32));
//     Key[0] = 1;
//     Key[1] = 0;
//     Key[2] = 2;
//     Key[3] = 1;
//     Key[4] = 2;
//     Key[5] = 1;
//     u32 *ordenado = RecoloreoCardinalidadDecrecienteBC(n, Key);
//     for(u32 i = 0; i < n; ++i){
//         printf("%u ", ordenado[i]);
//     }
//     printf("\n");
//     /*
//     array original = [1 0 2 1 2 1]
//     colores=     [0  1  2]
//     se usan veces 1   3  2
//     ordenamos segun las veces-> [1 2 0]

//     Reemplazamos todo el array original de la siguiente forma->
//     Por cada elemento del original, la posicion de ese elemento en el array ordenado
//     segun las veces -> QBE

//     Deberia devolver [0 2 1 0 1 0] mal, devuelve [0 1 2 0 2 0]
//     */
//     free(Key);
//     Key = NULL;
// }

void testRecoloreoCardDecBC(void) {
    u32 n = 11;
    u32 *Coloreo = calloc(n, sizeof(u32));
    Coloreo[0] = 0;
    Coloreo[1] = 0;
    Coloreo[2] = 2;
    Coloreo[3] = 3;
    Coloreo[4] = 1;
    Coloreo[5] = 0;
    Coloreo[6] = 3;
    Coloreo[7] = 0;
    Coloreo[8] = 3;
    Coloreo[9] = 2;
    Coloreo[10] = 0;
    u32 *Recoloreo = RecoloreoCardinalidadDecrecienteBC(n, Coloreo);
    for(u32 i = 0; i < n; ++i){
        printf("%u ", Recoloreo[i]);
    }
    printf("\n");
    free(Recoloreo);
    Recoloreo = NULL;
}

int main() {
    //Grafo G = ConstruccionDelGrafo();
    // dumpGrafo(G);

    // testBipartito(G);
    // testGreedy(G);
    testRecoloreoCardDecBC();
    /* testOrdenFromKey(); */

    //DestruccionDelGrafo(G);
    //G = NULL;
    return 0;
}
