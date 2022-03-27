#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

// TODO: Manage sanitize

int main() {
    char *id = malloc(sizeof(char)*2);
    assert(id!=NULL);
    u32 y = 0, z = 0, nodes = 0, edges = 0;
    FILE *fp = NULL;

    fp = fopen("datos.txt", "r");
    assert(fp != NULL);
    fscanf(fp, "%1c", id);
    if (strcmp(id, "c")==0){
        fscanf(fp, "%*s\n");
        while(fscanf(fp, "%c %*s\n", id) == 1 && strcmp(id, "c")==0){
        }
        fscanf(fp, "%u %u\n", &nodes, &edges);
        assert(strcmp(id, "p")==0);
    } else if (strcmp(id, "p")==0){
        fscanf(fp, "%*s %u %u\n", &nodes, &edges);
    } else {
        printf("Error, document bad formated\n");
        free(id);
        return 0;
    }
    
    unsigned int *ordArray = malloc(sizeof(u32)*(2*edges));
    assert(ordArray!=NULL);
    
    for(size_t i = 0; i<edges; ++i){
        fscanf(fp, "%c %u %u\n", id, &y, &z);
        
        // Forma de indezar ordArray[ancho * fila + columna]
        ordArray[2*i] = y;
        ordArray[2*i+1] = z;
    }
    
    fclose(fp);
    fp = NULL;

    for(u32 i=0; i<edges; ++i)
        printf("%u %u\n", ordArray[2*i], ordArray[2*i+1]);
    
    free(id);
    free(ordArray);
    id = NULL, ordArray = NULL;
    return 0;
}

// TODO: Implement
Grafo ConstruccionDelGrafo(){
    Grafo G = NULL;
    return G;
}

// REVIEW: Needs testing
void DestruccionDelGrafo(Grafo G){
    assert(G!=NULL);
    u32 n = G->n_vertices;
    
    for (size_t i=0; i<n; ++i){
        free(G->nameGrades[i]);
        G->nameGrades[i] = NULL;
        free(G->vecinos[i]);
        G->vecinos[i] = NULL;
    }

    free(G->nameGrades);
    free(G->vecinos);
    G->nameGrades = NULL;
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
    return G->nameGrades[i][0];
}

u32 Grado(u32 i,Grafo G){
    return G->nameGrades[i][1];
}

// REVIEW: Needs testing
u32 IndiceONVecino(u32 j,u32 k,Grafo G){
    return G->vecinos[j][k];
}
