#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

u32 NombreVertice(Vertice x){
    return x->nombre;
}

/*
    Función que compara dos lados.
*/
static int CompLadoP(const void *lado1, const void *lado2){
    int result = 0;
    u32 nombre1a = (*(Lado *)lado1)->a->nombre;
    u32 nombre1b = (*(Lado *)lado1)->b->nombre;
    u32 nombre2a = (*(Lado *)lado2)->a->nombre;
    u32 nombre2b = (*(Lado *)lado2)->b->nombre;

    if (nombre1a < nombre2a ||
       (nombre1a == nombre2a && nombre1b < nombre2b))
        result = -1;
    else if (nombre1a > nombre2a ||
        (nombre1a == nombre2a && nombre1b > nombre2b))
        result = 1;

    return result;
}

Grafo ConstruccionDelGrafo(){
    Grafo G = malloc(sizeof(struct GrafoSt));
    FILE *fp = fopen("datos.txt", "r");
    assert(G!=NULL && fp != NULL);
    bool error = false;
    u32 read = 0;

    char input = (char) fgetc(fp);
    while (input != EOF && !error) {
        switch (input) {
        case 'p':
            fscanf(fp, "%*s %u %u\n", &G->n_vertices, &G->m_lados);
            G->vertices = malloc(sizeof(Vertice)*(G->n_vertices));
            G->vecinos = malloc(sizeof(Lado)*(G->m_lados)*2);
            error = G->vertices == NULL || G->vecinos == NULL;
            input = (char) fgetc(fp);
            break;
        case 'e':
            if (read < G->m_lados*2) {
                Vertice ver_a, ver_b;
                Lado lado1, lado2;
                /* aloco vertices */
                ver_a = malloc(sizeof(VerticeSt));
                ver_b = malloc(sizeof(VerticeSt));
                /* escaneamos los nombres */
                fscanf(fp, "%u %u\n", &ver_a->nombre, &ver_b->nombre);

                /* aloco lado */
                lado1 = malloc(sizeof(LadoSt));
                lado2 = malloc(sizeof(LadoSt));

                /* meto los vertices en los lados */
                lado1->a = ver_a;
                lado1->b = ver_b;
                lado2->a = ver_b;
                lado2->b = ver_a;

                /* meto los lados en el Big Array */
                G->vecinos[read] = lado1;
                G->vecinos[read+1u] = lado2;
                printf("(%u %u), (%u %u)\n",
                       G->vecinos[read]->a->nombre,
                       G->vecinos[read]->b->nombre,
                       G->vecinos[read+1u]->a->nombre,
                       G->vecinos[read+1u]->b->nombre);

                // TODO: cargar info de c/lado
                read = read + 2u;
                input = (char) fgetc(fp);
            }
            break;
        default:
            fscanf(fp, "%*[^\n]%*c");
            input = (char) fgetc(fp);
            break;
        }
    }

    if (error){
        if (G->vertices != NULL)
            free(G->vertices);
        if (G->vecinos != NULL)
            free(G->vecinos);
        free(G);
        return NULL;
    }

    // printf("\n");
    qsort(G->vecinos, G->m_lados*2, sizeof(Lado), CompLadoP);
    // for (u32 i = 0; i < G->m_lados*2; i++)
    //     printf("(%u %u)\n",
    //            G->vecinos[i]->a->nombre,
    //            G->vecinos[i]->b->nombre);
    // printf("\n");


    //TRABAJO ASUMIENDO G->vecinos ORDENADO "lexicográficamente"
    //Ej big array = [(1,2), (1,12), (2,1), (2,3), (3,2), (12,1)]
    Vertice ver, anterior;
    Lado *bigArray = G->vecinos;
    /* ord almacena el orden natural del vertice que estamos analizando */
    u32 ord = 0u;
    ver = bigArray[0u]->a;
    ver->grado = 1u;
    ver->posicion = 0u;
    ver->indiceVec = 0u;
    G->vertices[0u] = ver;
    anterior = ver;
    u32 mayorGrado = 1u;

    for(u32 i = 1u; i < G->m_lados * 2u; ++i){
        Vertice newVer = bigArray[i]->a;
        if(newVer->nombre == anterior->nombre){
            /* Es el mismo vertice */
            anterior->grado++;
            if(mayorGrado < anterior->grado){
                mayorGrado = anterior->grado;
            }
        }else{
            /* Nuevo vertice -> lo agrego al array de orden natural*/
            ++ord;
            anterior = newVer;
            newVer->grado = 1u;
            newVer->posicion = ord;
            newVer->indiceVec = i;
            G->vertices[ord] = newVer;
        }
    }
    G->delta = mayorGrado;

    for (u32 i = 0; i < G->n_vertices; i++)
        printf("Vértice %u.\tnombre = %u,\tgrado = %u,\tposición = %u,\tíndiceVec = %u\n",
               i, G->vertices[i]->nombre, G->vertices[i]->grado,
               G->vertices[i]->posicion, G->vertices[i]->indiceVec);
    printf("\n");
    return G;
}

// REVIEW: Needs testing (usar orden O(m))
void DestruccionDelGrafo(Grafo G){
    assert(G!=NULL);
    // u32 n = G->n_vertices;

    // free(G->nameGrades);
    // G->nameGrades = NULL;
    // for (size_t i=0; i<n; ++i){
    //     /*free(G->vecinos[i]);
    //     G->vecinos[i] = NULL;*/
    // }

    // free(G->vecinos);
    // G->vecinos = NULL;
    free(G);
    G = NULL;
}

// u32 NumeroDeVertices(Grafo G){
//     return G->n_vertices;
// }

// u32 NumeroDeLados(Grafo G){
//     return G->m_lados;
// }

// u32 Delta(Grafo G){
//     return G->delta;
// }

// u32 Nombre(u32 i,Grafo G){
//     return G->nameGrades[2*i];
// }

// u32 Grado(u32 i,Grafo G){
//     return G->nameGrades[2*i+1];
// }

// // REVIEW: Needs testing
// u32 IndiceONVecino(u32 j,u32 k,Grafo G){
//     return G->vecinos[j][k];
// }



