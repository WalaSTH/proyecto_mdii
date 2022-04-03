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
    return 0;
}

