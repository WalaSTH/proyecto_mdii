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
        for(u32 j = 0; j<Grado(parent, G); ++j){
            u32 u = IndiceONVecino(parent, j, G);
            if(!coloreo[u]){
                q = queue_enqueue(q, u);
                coloreo[u] = 3-coloreo[parent];
            } else if(coloreo[u]==coloreo[parent]) {
                q = queue_destroy(q);
                free(coloreo);
                coloreo = NULL;
                return false;
            }

        }
        q = queue_dequeue(q);
        parent = queue_first(q);
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
    u32 lados = G->m_lados;
    u32 vertices = G->n_vertices;
    u32 *coloreo = calloc(vertices, sizeof(u32));
    bool bipartito = true;

    u32 i = 0;
    while(bipartito && i<vertices){
        if(!coloreo[i]){
            bipartito = BFSBipartito(G, i, coloreo);
        }
        ++i;
    }
    // for(u32 j = 0; j<Grado(i, G); ++j){
    //     if(!encolados[j]){
            
    //     }
    //     q = queue_enqueue(q, IndiceONVecino(i, j, G));
    // }
    // u32 *coloreo = NULL;
    // coloreo = malloc(sizeof(u32) * n);
    // // Initialize every color in 0
    // for(u32 i = 0u; i<n; ++i){
    //     coloreo[i] = 0;
    // }
    // // Do the actual coloring
    // for(u32 i = 0u; i<n; ++i){
    //     if(coloreo[i] == 0){
    //         // FIXME No esta coloreado
    //         coloreo[i] = 1;
    //         estado = 1;
    //     }else{ 
    //         //Ya tiene color -> lo guardamos en estado
    //         estado = coloreo[i];
    //     }

    //     u32 gradoVertice = Grado(i, G);
    //     for(u32 j = 0u; j<gradoVertice; ++j){
    //         u32 indiceVecino = IndiceONVecino(i, j, G);
    //         u32 colorVecino = coloreo[indiceVecino];
    //         if(colorVecino == 0){
    //             coloreo[indiceVecino] = 3-estado; // si estado = 1 => 3-1 = 2, si estado = 2 => 3-2 = 1
    //         }
    //     }
    // }

    return coloreo;
}

// Salve principe Sheogorath
u32 Greedy(Grafo G, u32 *Orden, u32 *Coloreo){
    return 0;
}

//ordenamiento a partir de clave
char OrdenFromKey(u32 n,u32* key,u32* Orden){
    return (char) 0;
}