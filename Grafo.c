#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "u32.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"


/* Función auxiliar para comparar dos lados lexicográficamente */

static int CompLadoP(const void *lado1, const void *lado2){
    u32 nombre1a = (*(Lado *)lado1)->a->nombre;
    u32 nombre1b = (*(Lado *)lado1)->b->nombre;
    u32 nombre2a = (*(Lado *)lado2)->a->nombre;
    u32 nombre2b = (*(Lado *)lado2)->b->nombre;

    if (nombre1a < nombre2a ||
       (nombre1a == nombre2a && nombre1b < nombre2b))
        return -1;
    else if (nombre1a > nombre2a ||
        (nombre1a == nombre2a && nombre1b > nombre2b))
        return 1;

    return 0;
}


/* Funciones de construcción/destrucción del grafo */

Grafo ConstruccionDelGrafo(){
    Grafo G = NULL;
    G = malloc(sizeof(GrafoSt));
    assert(G!=NULL);
    FILE *fp = stdin;
    G->n_vertices = 0u, G->m_lados = 0u, G->delta = 0u;
    G->vecinos = NULL, G->vertices = NULL;
    bool error = false;
    u32 read = 0u;

    char c = (char) fgetc(fp);
    while (c != EOF && !error) {
        switch (c) {
        case 'p':
            fscanf(fp, "%*s %u %u\n", &(G->n_vertices), &(G->m_lados));
            error = error || G->n_vertices < 2u || G->m_lados < 1u;
            if (error)
                break;

            G->vertices = malloc(sizeof(Vertice)*(G->n_vertices));
            G->vecinos = malloc(sizeof(Lado)*(G->m_lados)*2u);
            assert(G->vertices != NULL && G->vecinos != NULL);
            c = (char) fgetc(fp);
            break;
        case 'e':
            if (read < 2u * G->m_lados) {
                Vertice ver_a = NULL, ver_b = NULL;
                Lado lado1 = NULL, lado2 = NULL;

                // Reservamos memoria para ambos vértices
                ver_a = malloc(sizeof(VerticeSt));
                ver_b = malloc(sizeof(VerticeSt));

                // Escaneamos los nombres
                fscanf(fp, "%u %u\n", &ver_a->nombre, &ver_b->nombre);

                // Reservamos memoria para cada lado
                lado1 = malloc(sizeof(LadoSt));
                lado2 = malloc(sizeof(LadoSt));

                // Metemos los vértices en los lados
                lado1->a = ver_a;
                lado1->b = ver_b;
                lado2->a = ver_b;
                lado2->b = ver_a;

                // Metemos los lados en el arreglo de vecinos
                G->vecinos[read] = lado1;
                G->vecinos[read+1u] = lado2;

                read += 2u;
                c = (char) fgetc(fp);
            }
            break;
        default:
            // Ignoramos la línea entera y leemos el primer caracter
            // de la siguiente
            while (c != '\n')
                c = (char) fgetc(fp);
            c = (char) fgetc(fp);
            break;
        }
    }

    error = error || (read < 2u*G->m_lados);
    if (error){
        DestruccionDelGrafo(G);
        G = NULL;
        return NULL;
    }

    // Ordenamos los lados lexicográficamente
    qsort(G->vecinos, G->m_lados*2u, sizeof(Lado), CompLadoP);

    Vertice ver, anterior;
    // Ord almacena el índice en orden natural del vertice
    // que estamos analizando
    u32 ord = 0u;
    ver = G->vecinos[0u]->a;
    ver->grado = 1u;
    ver->posicion = 0u;
    ver->indiceVec = 0u;
    G->vertices[0u] = ver;
    anterior = ver;
    u32 mayorGrado = 1u;

    for(u32 i = 1u; i < G->m_lados * 2u; ++i){
        ver = G->vecinos[i]->a;
        if(ver->nombre == anterior->nombre){
            // Es el mismo vértice que el anterior
            ver->posicion = ord;
            ++anterior->grado;
            if(mayorGrado < anterior->grado)
                mayorGrado = anterior->grado;
        }else{
            // Nuevo vértice, lo agregamos al arreglo de orden natural
            ++ord;
            anterior = ver;
            ver->grado = 1u;
            ver->posicion = ord;
            ver->indiceVec = i;
            G->vertices[ord] = ver;
        }
    }
    G->delta = mayorGrado;
    return G;
}

void DestruccionDelGrafo(Grafo G){
    if (G == NULL)
        return;

    Vertice ver = NULL;
    Lado edge = NULL;
    if (G->vecinos != NULL){
        for (u32 i = 0u; i < 2u * G->m_lados; ++i){
            edge = G->vecinos[i];
            if (edge != NULL) {
                ver = edge->a;
                if (ver != NULL) {
                    free(ver);
                    ver = NULL;
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

/* Funciones para extraer información de datos del grafo */

u32 NumeroDeVertices(Grafo G){
    return G->n_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G->m_lados;
}

u32 Delta(Grafo G){
    return G->delta;
}

/* Funciones para extraer información de los vertices */

u32 Nombre(u32 i,Grafo G){
    return G->vertices[i]->nombre;
}

u32 Grado(u32 i,Grafo G){
    if (i >= G->n_vertices)
        return U32_MAX;
    return G->vertices[i]->grado;
}

u32 IndiceONVecino(u32 j, u32 k, Grafo G){
    if (k >= G->n_vertices ||
       (k < G->n_vertices && j >= G->vertices[k]->grado))
        return U32_MAX;
    return G->vecinos[G->vertices[k]->indiceVec + j]->b->posicion;
}
