#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "u32.h"
#include "Queue.h"
#include "sort_r.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"


/* Funciones de coloreo */

static bool BFSBipartito(Grafo G, u32 parent, u32 *coloreo){
    Queue q = QueueEmpty();
    q = QueueEnqueue(q, parent);
    coloreo[parent] = 1u;

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

static u32 pseudoRandom(u32 R, u32 i) {
    R = R<<10;
    R = R+123;
    R = R*50;
    R *= (R + i + 1);
    return R;
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
    free(colorFueUsado);
    vertFueColoreado = NULL;
    colorFueUsado = NULL;

    return maxColor + 1;
}

/* Funciones auxiliares para comparar claves según sus índices */

static int CmpKeys(const u32 x, const u32 y, u32 *key) {
    return (key[y] - key[x]);
}

static int CmpKeysP(const void *x, const void *y, void *key) {
    return CmpKeys(*(const u32*)x, (*(const u32*)y), (u32*)key);
}

/* Función para crear un orden a partir de claves */

char OrdenFromKey(u32 n,u32* key,u32* Orden){
    for(u32 i=0; i<n; ++i)
        Orden[i] = i;
    sort_r(Orden, n, sizeof(u32), CmpKeysP, key);
    return (char)0;
}

/* Funciones para crear claves específicas */

void AleatorizarKeys(u32 n, u32 R, u32 *key){
    srand(R);
    for(u32 i=0; i<n; ++i){
        key[i] = rand() % n;
    }
}

u32 *PermutarColores(u32 n, u32 *Coloreo, u32 R){
    u32 *newColors = malloc(sizeof(u32) * n);
    if (NULL == newColors) {
        return NULL;
    }

    // Obtenemos el máximo color usado
    u32 maxColor = Coloreo[0];
    for(u32 i=0; i<n; ++i){
        if(Coloreo[i]>maxColor){
            maxColor = Coloreo[i];
        }
    }

    // Inicializamos el arreglo de colores
    u32 *PermC = malloc(sizeof(u32) * (maxColor+1));
    if (NULL == PermC) {
        free(newColors);
        newColors = NULL;
        return NULL;
    }
    for(u32 i=0; i<maxColor+1; ++i){
        PermC[i] = i;
    }

    // Permutamos los lugares de cada color
    srand(R);
    for(u32 i=0; i < maxColor+1; ++i){
        u32 random = rand() % (maxColor+1);
        u32 temp = PermC[i];
        PermC[i] = PermC[random];
        PermC[random] = temp;
    }

    // Asignamos el nuevo coloreo
    for(u32 i=0; i<n; ++i){
        newColors[i] = PermC[Coloreo[i]];
    }

    free(PermC);
    PermC = NULL;

    return newColors;
}


u32 *RecoloreoCardinalidadDecrecienteBC(u32 n, u32 *Coloreo) {
    u32 *newColors = malloc(n * sizeof(u32));
    if(NULL == newColors){
        // caso de error
        return NULL;
    }

    // Obtenemos el máximo color usado
    u32 maxColor = Coloreo[0];
    for(u32 i=0; i<n; ++i){
        if(Coloreo[i]>maxColor){
            maxColor = Coloreo[i];
        }
    }

    u32 *CardC = calloc(maxColor + 1, sizeof(u32));
    if (NULL == CardC) {
        // Caso de error
        free(newColors);
        newColors = NULL;
        return NULL;
    }

    // Obtenemos cardinalidad de cada color
    for(u32 i=0; i<n; ++i){
        ++CardC[Coloreo[i]];
    }

    // Arreglo para los nuevos nombres que va a tener cada color
    u32 *OrdC = malloc((maxColor + 1) * sizeof(u32));
    if (NULL == OrdC) {
        // caso de error
        free(newColors);
        free(CardC);
        newColors = NULL;
        CardC = NULL;
        return NULL;
    }

    // Obtenemos el nuevo nombre de cada color
    char OFKStatus = OrdenFromKey(maxColor + 1, CardC, OrdC);
    if (OFKStatus) {
        // caso de error
        free(CardC);
        free(OrdC);
        free(newColors);
        CardC = NULL;
        OrdC = NULL;
        newColors = NULL;
        return NULL;
    }

    // Que Bueno Estaria tener este array...
    u32 *QBE = CardC;
    for(u32 i = 0; i < maxColor+1; ++i){
        QBE[OrdC[i]] = i;
    }

    // Renombramos cada color
    for(u32 i = 0; i < n; ++i)
        newColors[i] = QBE[Coloreo[i]];

    free(CardC);
    free(OrdC);
    CardC = NULL;
    OrdC = NULL;
    QBE = NULL;

    return newColors;
}
