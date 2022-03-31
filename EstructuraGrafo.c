#include <stdbool.h>
#include <assert.h>
#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

u32 NombreVertice(Vertice x){
    return x->nombre;
}

static int cmp(static void *p1, static void *p2){
    int result = 0;
    u32 p1a = *(Lado *)p1, p1b, p2b;
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
            G->vertices = malloc(sizeof(struct VerticeSt)*(G->n_vertices));
            G->vecinos = malloc(sizeof(struct LadoSt)*(G->m_lados)*2);
            if (G->vertices == NULL || G->vecinos == NULL)
                error = true;
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
                       G->vecinos[read+1u]->a->nombre, G->vecinos[read+1u]->b->nombre);

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
    qsort(G->vecinos, G->m_lados*2, sizeof(ustruct LadoSt), cmp);
    
    // G->nameGrades = malloc(sizeof(u32)*G->n_vertices*2);
    // G->vecinos = malloc(sizeof(u32)*G->n_vertices);
    // if (read < G->m_lados && G->m_lados >= 2 &&
    //     G->nameGrades!=NULL && G->vecinos!=NULL){
    //     printf("Hubo un error al crear el grafo.\n");
    //     free(G);
    //     // TODO: Liberar toda la memoria reservada hasta ahora.
    //     G = NULL;
    //     return G;
    // }

    // G->n_vertices = nodes;
    // G->m_lados = edges;
    // assert(G->m_lados>=2 && G->nameGrades!=NULL && G->vecinos!=NULL);

    // u32 x=0, y=0, jx=0, jy=0, vertCount = 0;
    // for(size_t i=0; i < edges; ++i){
    //     fscanf(fp, "%c %u %u\n", id, &x, &y);
    //     if (strcmp(id, "e")!=0){
    //         free(G->nameGrades);
    //         free(G->vecinos);
    //         free(G);
    //         G = NULL;
    //         return G;
    //     }

    //     // Forma de indezar nameGrades[ancho * fila + columna]
    //     // Checkear que este antes en nameGrades
    //     jx = getIndex(x, vertCount, G->nameGrades);
    //     if (jx == vertCount) {
    //         ++vertCount;
    //         // G->vecinos[jx] = malloc(sizeof(u32)*nodes);
    //         G->nameGrades[2*jx] = x;
    //         G->nameGrades[2*jx+1] = 1;
    //     } else if (jx < vertCount)
    //         ++G->nameGrades[2*jx+1];

    //     jy = getIndex(y, vertCount, G->nameGrades);
    //     if (jy == vertCount) {
    //         ++vertCount;
    //         // G->vecinos[jy] = malloc(sizeof(u32)*nodes);  // FIXME esto rompe G->vecinos[0][0] en la iteracion 7
    //         G->nameGrades[2*jy] = y;
    //         G->nameGrades[2*jy+1] = 1;
    //     } else if (jy < vertCount)
    //         ++G->nameGrades[2*jy+1];

    //     // NOTE Hacer "bitmap" tipo hash es decir esta alocado n*n
    //     // pero solamente esta ocupado los indices con nombre
    //     // G->vecinos[jx][G->nameGrades[2*jx+1]-1] = y;
    //     // G->vecinos[jy][G->nameGrades[2*jy+1]-1] = x;

    // }

    // fclose(fp);
    // free(id);
    // fp = NULL, id = NULL;
    
    //TRABAJO ASUMIENDO G->vecinos ORDENADO "lexicograficamente"

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



