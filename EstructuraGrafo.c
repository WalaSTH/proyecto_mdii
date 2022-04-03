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
    Grafo G = NULL;
    G = malloc(sizeof(GrafoSt));
    //FILE *fp = stdin;
    FILE *fp = NULL;
    fp = fopen("./ejemplos/malo.txt", "r");
    assert(G!=NULL && fp != NULL);
    G->n_vertices = 0, G->m_lados = 0, G->delta = 0;
    G->vecinos = NULL, G->vertices = NULL;
    bool error = false;
    u32 read = 0u;

    char input = (char) fgetc(fp);
    while (input != EOF && !error) {
        switch (input) {
        case 'p':
            fscanf(fp, "%*s %u %u\n", &(G->n_vertices), &(G->m_lados));
            G->vertices = malloc(sizeof(Vertice)*(G->n_vertices));
            G->vecinos = malloc(sizeof(Lado)*(G->m_lados)*2);
            assert(G->vertices != NULL && G->vecinos != NULL);
            error = error || G->n_vertices < 2 || G->m_lados < 1;
            input = (char) fgetc(fp);
            break;
        case 'e':
            if (read < 2 * G->m_lados) {
                Vertice ver_a = NULL, ver_b = NULL;
                Lado lado1 = NULL, lado2 = NULL;
                /* Aloco vertices */
                ver_a = malloc(sizeof(VerticeSt));
                ver_b = malloc(sizeof(VerticeSt));
                /* escaneamos los nombres */
                fscanf(fp, "%u %u\n", &ver_a->nombre, &ver_b->nombre);

                /* Aloco lado */
                lado1 = malloc(sizeof(LadoSt));
                lado2 = malloc(sizeof(LadoSt));

                /* Meto los vertices en los lados */
                lado1->a = ver_a;
                lado1->b = ver_b;
                lado2->a = ver_b;
                lado2->b = ver_a;

                /* Meto los lados en el Big Array */
                G->vecinos[read] = lado1;
                G->vecinos[read+1u] = lado2;

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
    error = error || (read < 2*G->m_lados);
    if (error){
        printf("ERROR: Hubo un problema al construir el grafo\n");
        fclose(fp);
        DestruccionDelGrafo(G);
        G = NULL;
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
            ++anterior->grado;
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

    // for (u32 i = 0; i < G->n_vertices; ++i)
    //     printf("Vértice %u.\tnombre = %u,\tgrado = %u,\tposición = %u,\tíndiceVec = %u\n",
    //            i, G->vertices[i]->nombre, G->vertices[i]->grado,
    //            G->vertices[i]->posicion, G->vertices[i]->indiceVec);
    // printf("\n");
    // printf("Vecinos del vértice 1:");
    // for (u32 i = 0; i < G->vertices[0]->grado; ++i)
    //     printf(" %u ", G->vecinos[G->vertices[0]->indiceVec + i]->b->nombre);
    // printf("\n");
    // printf("Delta= %u\n", G->delta);
    fclose(fp);
    return G;
}

void DestruccionDelGrafo(Grafo G){
    if(G!=NULL){
        Vertice ver_a = NULL;
        Lado edge = NULL;
        if (G->vecinos != NULL){
            for (u32 i = 0; i < 2 * G->m_lados; ++i) {
                edge = G->vecinos[i];
                if (edge != NULL) {
                    ver_a = edge->a;
                    if (ver_a != NULL) {
                        // There will be NO mirror's edge problems (mirror's edge lol)
                        free(ver_a);
                        ver_a = NULL;
                    }
                    free(edge);
                    edge = NULL;
                }
            }
            free(G->vecinos);
            G->vecinos = NULL;
        }

        if (G->vertices != NULL) {
            free(G->vertices);
            G->vertices = NULL;
        }
        free(G);
        G = NULL;
    }
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
    return G->vertices[i]->nombre;
}

u32 Grado(u32 i,Grafo G){
    return G->vertices[i]->grado;
}

// REVIEW: Needs testing
u32 IndiceONVecino(u32 j, u32 k, Grafo G){
    assert(k < G->vertices[j]->grado);
    return G->vecinos[G->vertices[j]->indiceVec + k]->b->posicion;
}
