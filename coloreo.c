#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"
#include "EstructuraGrafo.h"
#include "queue.h"
#include <stdbool.h>
#include <stdlib.h>

static bool BFSBipartito(Grafo G, u32 parent, u32 *coloreo){
    queue q = queue_empty();
    q = queue_enqueue(q, parent);
    coloreo[parent] = 1;

    while(!queue_is_empty(q)){
        parent = queue_first(q);
        for(u32 j = 0; j<Grado(parent, G); ++j){
            u32 u = IndiceONVecino(j, parent, G);
            if(!coloreo[u]){
                q = queue_enqueue(q, u);
                coloreo[u] = 3-coloreo[parent];
            } else if(coloreo[u]==coloreo[parent]) {
                q = queue_destroy(q);
                return false;
            }
        }
        q = queue_dequeue(q);
    }

    q = queue_destroy(q);
    return true;
}

/* Si χ(G) ≤ 2, (y como todos nuestros grafos tienen al menos un lado, χ(G) ≤ 2 es equivalente a χ(G) = 2) devuelve un
puntero a un array de u32s que debe tener longitud n = n ́umero de v ́ertices de G, y ser un coloreo propio de G con los colores
1 y 2, con la entrada i del array diciendo que color tiene el v ́ertice cuyo  ́ındice es i en el Orden Natural. La reserva de memoria
para ese array debe ser hecha dentro de Bipartito, obviamente.
Si χ(G) ≥ 3, devuelve un puntero a NULL. */
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
    u32 nVertices = NumeroDeVertices(G);
    bool *vertFueColoreado = calloc(nVertices, sizeof(bool)),
         *colorFueUsado = NULL;

    // Coloreamos el primer vértice
    u32 maxColor = 0;
    u32 vertActual = Orden[0];
    Coloreo[vertActual] = 0;
    vertFueColoreado[vertActual] = true;

    for(u32 i = 1; i < nVertices; ++i){
        // Elegimos el vértice actual
        vertActual = Orden[i];
        u32 grado = Grado(vertActual, G);

        // Inicializamos el array de colores usados
        colorFueUsado = calloc(maxColor + 2, sizeof(bool));
        for(u32 j = 0; j < grado; ++j){
            u32 jVecino = IndiceONVecino(j, vertActual, G);
            if(vertFueColoreado[jVecino]){
                colorFueUsado[Coloreo[jVecino]] = true;
            }
        }

        // Buscamos el menor color que no haya sido usado
        u32 color = 0;
        while(colorFueUsado[color]){
            ++color;
        }

        // Asignamos el color
        Coloreo[vertActual] = color;
        vertFueColoreado[vertActual] = true;

        // Actualizamos el color máximo
        if(maxColor < color){
            maxColor = color;
        }

        // Liberamos el array de colores usados
        free(colorFueUsado);
        colorFueUsado = NULL;
    }

    free(vertFueColoreado);
    vertFueColoreado = NULL;

    return maxColor + 1;
}

// Ordenamiento a partir de clave
char OrdenFromKey(u32 n,u32* key,u32* Orden){
    return (char) 0;
}