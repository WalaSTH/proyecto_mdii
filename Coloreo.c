#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"
#include "EstructuraGrafo.h"
#include "sort_r.h"
#include "Queue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/* Funciones de coloreo */

static bool BFSBipartito(Grafo G, u32 parent, u32 *coloreo){
    Queue q = QueueEmpty();
    q = QueueEnqueue(q, parent);
    coloreo[parent] = 1;

    while(!QueueIsEmpty(q)){
        parent = QueueFirst(q);
        for(u32 j = 0; j<Grado(parent, G); ++j){
            u32 u = IndiceONVecino(j, parent, G);
            if(!coloreo[u]){
                q = QueueEnqueue(q, u);
                coloreo[u] = 3-coloreo[parent];
            } else if(coloreo[u]==coloreo[parent]) {
                q = QueueDestroy(q);
                return false;
            }
        }
        q = QueueDequeue(q);
    }

    q = QueueDestroy(q);
    return true;
}

u32 *Bipartito(Grafo G){
    u32 vertices = NumeroDeVertices(G);
    u32 *coloreo = calloc(vertices, sizeof(u32));
    bool bipartito = true;

    u32 i = 0;
    while(bipartito && i<vertices){
        if(!coloreo[i]){
            bipartito = BFSBipartito(G, i, coloreo);
            if(!bipartito) {
                free(coloreo);
                coloreo = NULL;
                return coloreo;
            }
        }
        ++i;
    }

    return coloreo;
}

// Salve principe Sheogorath
u32 Greedy(Grafo G, u32 *Orden, u32 *Coloreo){
    u32 nVertices=NumeroDeVertices(G), delta=Delta(G);
    bool *vertFueColoreado = NULL;
    u32 *colorFueUsado = NULL;

    vertFueColoreado = calloc(nVertices, sizeof(bool));
    if (vertFueColoreado == NULL) {
        return U32_MAX;
    }

    colorFueUsado = calloc((delta + 1), sizeof(u32));
    if (colorFueUsado == NULL) {
        free(vertFueColoreado);
        vertFueColoreado = NULL;
        return U32_MAX;
    }

    // Coloreamos el primer vértice
    u32 maxColor = 0;
    u32 vertActual = Orden[0];
    Coloreo[vertActual] = 0;
    vertFueColoreado[vertActual] = true;

    for(u32 i = 1; i < nVertices; ++i){
        vertActual = Orden[i];
        u32 grado = Grado(vertActual, G);

        // Chequeamos los colores de cada vecino y actualizamos
        // el array de colores usados
        for(u32 j = 0; j < grado; ++j){
            u32 jVecino = IndiceONVecino(j, vertActual, G);
            if(vertFueColoreado[jVecino]){
                colorFueUsado[Coloreo[jVecino]] = i;
            }
        }

        // Buscamos el menor color que no haya sido usado
        u32 color = 0;
        while (colorFueUsado[color] == i && color < maxColor+1) {
            ++color;
        }

        // Asignamos el color
        Coloreo[vertActual] = color;
        vertFueColoreado[vertActual] = true;

        // Actualizamos el color máximo
        if(maxColor < color){
            maxColor = color;
        }
    }

    free(vertFueColoreado);
    vertFueColoreado = NULL;
    free(colorFueUsado);
    colorFueUsado = NULL;

    return maxColor + 1;
}

/* Funciones auxiliares para comparar claves según sus índices */

static int CmpKeys(const u32 x, const u32 y, u32 *key) {
    return (key[y] - key[x]);
}

static int CmpKeysP(const void *x, const void *y, void *key) {
    return CmpKeys(*(const u32*)x, (*(const u32*)y), (u32 *) key);
}

/* Función para crear un orden a partir de claves */

char OrdenFromKey(u32 n,u32* key,u32* Orden){
    for(u32 i=0; i<n+1; ++i)
        Orden[i] = i;
    sort_r(Orden, n+1, sizeof(u32), CmpKeysP, key);
    return (char)0;
}