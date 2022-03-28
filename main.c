#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

// TODO: Manage sanitize

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

    // Grafo G = malloc(sizeof(struct GrafoSt));
    // char *id = malloc(sizeof(char)*2);
    // assert(id!=NULL);
    // u32 y = 0, z = 0, nodes = 0, edges = 0;
    // FILE *fp = NULL;

    // fp = fopen("datos.txt", "r");
    // assert(fp != NULL);
    // fgets(id, 2, fp);
    // if (strcmp(id, "c") == 0){
    //     fscanf(fp, "%*[^\n]%*c");
    //     while(strcmp(id, "c")==0){
    //         fscanf(fp, "%c", id);
    //         if (strcmp(id, "p")==0)
    //             break;
    //         fscanf(fp, "%*[^\n]\n");
    //     }
    //     fscanf(fp, "%*s %u %u\n", &nodes, &edges);
    //     printf("nodes: %u, edges: %u\n", nodes, edges);
    //     assert(strcmp(id, "p")==0);
    // } else if (strcmp(id, "p")==0){
    //     fscanf(fp, "%*s %u %u\n", &nodes, &edges);
    // } else {
    //     printf("Error, document bad formated\n");
    //     free(id);
    //     return 0;
    // }

    // assert(edges>=2);
    // unsigned int *ordArray = malloc(sizeof(u32)*(2*edges));
    // G->vecinos = malloc(sizeof(u32)*nodes);
    // assert(ordArray!=NULL && G->vecinos!=NULL);

    // for(size_t i = 0; i<edges; ++i){
    //     fscanf(fp, "%c %u %u\n", id, &y, &z);

    //     // Forma de indezar ordArray[ancho * fila + columna]
    //     ordArray[2*i] = y;
    //     ordArray[2*i+1] = z;
    // }

    // fclose(fp);
    // fp = NULL;

    // for(u32 i=0; i<edges; ++i)
    //     printf("%u %u\n", ordArray[2*i], ordArray[2*i+1]);

    // free(id);
    // free(ordArray);
    // id = NULL, ordArray = NULL;
    // return 0;
}

u32 getIndex(u32 x, u32 vertCount, u32 *nameGrades){
    u32 i = 0;
    while (i < vertCount && nameGrades[2*i] != x)
        ++i;
    return i;
}

// TODO: Orden O(m) o algo no mucho peor
Grafo ConstruccionDelGrafo(){
    FILE *fp = fopen("datos.txt", "r");
    Grafo G = malloc(sizeof(struct GrafoSt));
    char *id = malloc(sizeof(char)*2);
    u32 nodes = 0, edges = 0;
    assert(G!=NULL && id!=NULL && fp != NULL);

    fgets(id, 2, fp);
    if (strcmp(id, "c") == 0){
        fscanf(fp, "%*[^\n]%*c");
        while(strcmp(id, "c")==0){
            fscanf(fp, "%c", id);
            if (strcmp(id, "p")==0)
                break;
            fscanf(fp, "%*[^\n]\n");
        }
        fscanf(fp, "%*s %u %u\n", &nodes, &edges);
        assert(strcmp(id, "p")==0);
    } else if (strcmp(id, "p")==0){
        fscanf(fp, "%*s %u %u\n", &nodes, &edges);
    } else {
        printf("Error, document bad formated\n");
        free(id);
        return 0;
    }
    assert(strcmp(id, "p")==0);

    G->n_vertices = nodes;
    G->m_lados = edges;
    G->nameGrades = malloc(sizeof(u32)*G->n_vertices*2);
    G->vecinos = malloc(sizeof(u32)*G->n_vertices);
    assert(G->m_lados>=2 && G->nameGrades!=NULL && G->vecinos!=NULL);

    u32 x=0, y=0, jx=0, jy=0, vertCount = 0;
    for(size_t i=0; i < edges; ++i){
        fscanf(fp, "%c %u %u\n", id, &x, &y);
        if (strcmp(id, "e")!=0){
            free(G->nameGrades);
            free(G->vecinos);
            free(G);
            G = NULL;
            return G;
        }

        // Forma de indezar nameGrades[ancho * fila + columna]
        // Checkear que este antes en nameGrades
        jx = getIndex(x, vertCount, G->nameGrades);
        if (jx == vertCount) {
            ++vertCount;
            // G->vecinos[jx] = malloc(sizeof(u32)*nodes);
            G->nameGrades[2*jx] = x;
            G->nameGrades[2*jx+1] = 1;
        } else if (jx < vertCount)
            ++G->nameGrades[2*jx+1];

        jy = getIndex(y, vertCount, G->nameGrades);
        if (jy == vertCount) {
            ++vertCount;
            // G->vecinos[jy] = malloc(sizeof(u32)*nodes);  // FIXME esto rompe G->vecinos[0][0] en la iteracion 7
            G->nameGrades[2*jy] = y;
            G->nameGrades[2*jy+1] = 1;
        } else if (jy < vertCount)
            ++G->nameGrades[2*jy+1];

        // NOTE Hacer "bitmap" tipo hash es decir esta alocado n*n
        // pero solamente esta ocupado los indices con nombre
        // G->vecinos[jx][G->nameGrades[2*jx+1]-1] = y;
        // G->vecinos[jy][G->nameGrades[2*jy+1]-1] = x;

    }

    fclose(fp);
    free(id);
    fp = NULL, id = NULL;
    return G;
}

// REVIEW: Needs testing (usar orden O(m))
void DestruccionDelGrafo(Grafo G){
    assert(G!=NULL);
    u32 n = G->n_vertices;

    free(G->nameGrades);
    G->nameGrades = NULL;
    for (size_t i=0; i<n; ++i){
        /*free(G->vecinos[i]);
        G->vecinos[i] = NULL;*/
    }

    free(G->vecinos);
    G->vecinos = NULL;
    free(G);
    G = NULL;
}

u32 NumeroDeVertices(Grafo G){
    return G->n_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G->m_lados;
}

u32 Delta(Grafo G){
    return G->delta;
}

u32 Nombre(u32 i,Grafo G){
    return G->nameGrades[2*i];
}

u32 Grado(u32 i,Grafo G){
    return G->nameGrades[2*i+1];
}

// REVIEW: Needs testing
u32 IndiceONVecino(u32 j,u32 k,Grafo G){
    return G->vecinos[j][k];
}
