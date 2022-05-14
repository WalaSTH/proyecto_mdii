#include <stdbool.h>
#include "u32.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"

// Prints every funcion from Query

bool es_propio(u32* col, Grafo G){
    u32 vertex_colour = 0;
    u32 neighbor_colour = 0;
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        vertex_colour = col[i];
        for(u32 j = 0; j < Grado(i, G); j++){
            neighbor_colour = col[IndiceONVecino(j, i, G)];
            if (vertex_colour == neighbor_colour){
                return false;
            }
        }
    }
    return true;
}

void Bipartito_test(Grafo g){
    // Run Bipartito
    u32* Color = Bipartito(g);
    // Check for Errors
    if (Color != NULL){
        bool propio = es_propio(Color, g);
        if (propio){
            printf("El coloreo dado por Bipartito es propio\n");
        }
        else{
            printf("El coloreo dado por Bipartito NO es propio\n");
        }
        free(Color);
    }
    else{
        printf("El grafo NO es bipartito\n");
    }
}

// Sets the given order in natural order.
u32* OrdenNatural(u32* orden, u32 n){
    for (u32 i = 0; i < n; i++){
        orden[i] = i;
    }
    return orden;
}

void Greedy_test(Grafo g){
    // Run Greedy with natural ordering
    u32* coloreo = calloc(NumeroDeVertices(g), sizeof(u32));
    u32* orden = calloc(NumeroDeVertices(g),sizeof(u32));
    orden = OrdenNatural(orden, NumeroDeVertices(g));

    u32 used_colors = Greedy(g,orden,coloreo);

    // Check for Errors
    if (used_colors > Delta(g) + 1){
        printf("Error: El numero de colores usados es mayor a Delta + 1\n");
    }
    else{
        bool propio = es_propio(coloreo, g);
        if (propio){
                printf("El coloreo dado por Greedy es propio\n");
        }
        else{
                printf("El coloreo dado por Greedy NO es propio\n");
        }
        printf("Se usaron %u colores con Greedy\n",used_colors);
    }

    // Frees all the memory
    free(coloreo);
    free(orden);
}

void OrdenFromKeyTest(u32 n, Grafo g){
    u32* key = calloc(n, sizeof(u32));

    u32* orden = calloc(n, sizeof(u32));

    AleatorizarKeys(n, rand(), key);
    // for(u32 i = 0; i < n; i++){
    //     key[i] = i;
    // }
    OrdenFromKey(n, key, orden);

    // Keys should be printed in decreasing order
    for (u32 i = 0; i < n; i++){
        printf("Key: %u\n", key[orden[i]]);
    }

    free(orden);
    free(key);
}

void Permutation_test(Grafo g){
    // Run Greedy with natural ordering for the first time.
    u32* colouring = calloc(NumeroDeVertices(g), sizeof(u32));
    u32* orden = calloc(NumeroDeVertices(g), sizeof(u32));
    orden = OrdenNatural(orden, NumeroDeVertices(g));
    u32 used_colors_in_greedy = Greedy(g, orden, colouring);

    // Generates a new colouring with permuted colors
    u32* new_colouring = PermutarColores(NumeroDeVertices(g), colouring, rand());

    // Array of indexes of vertices with the same colour.
    u32* vertices_with_color_k = calloc(NumeroDeVertices(g), sizeof(u32));
    u32 new_color = 0; // Represents the new color after a permutation of a color.
    u32 j = 0;
    u32 used_colors = 0;
    bool same_quantity_of_colours = true;
    bool same_colors = true;

    // Calculates how many colours are used in the new colouring
    for (u32 i = 0; i < NumeroDeVertices(g); i++)
    {
        if (new_colouring[i] > used_colors){
            used_colors = new_colouring[i];
        }
    }
    used_colors = used_colors + 1; // First colour is 0, we have 1 more colour.

    if (used_colors != used_colors_in_greedy) {
        same_quantity_of_colours = false;
    }

    // Check if vertices with same colours still have the same colour after a permutation.
    for (u32 k = 0; k < used_colors_in_greedy; k++){
        j = 0;
        for(u32 i = 0; i < NumeroDeVertices(g); i++){
            if(colouring[i] == k){
                vertices_with_color_k[j] = i;
                j++;
            }
        }

        new_color = new_colouring[vertices_with_color_k[0]];
        for (u32 i = 1; i < j; i++){
            if(new_colouring[vertices_with_color_k[i]] != new_color){
                same_colors = false;
            }
        }
    }

    if (!same_colors){
        printf("ERROR: Los vertices que tenian color 0 antes, no tienen el mismo color entre ellos luego de la permutacion.\n");
        return;
    }

    if (!same_quantity_of_colours)
    {
        printf("ERROR: En el coloreo permutado se usan: %u colores, en Greedy se usan: %u colores\n", used_colors, used_colors_in_greedy);
        return;
    }

    if(same_colors && same_quantity_of_colours){
        printf("La permutacion no genero errores!\n");
    }

    // Frees the memory.
    free(new_colouring);
    free(colouring);
    free(orden);
    free(vertices_with_color_k);
}


void RecoloreoCardinalidadDecrecienteBCTest(u32 n, Grafo g){
    // Run Greedy to obtain a colouring
    u32* orden = calloc(NumeroDeVertices(g),sizeof(u32));
    for (u32 i = 0; i < NumeroDeVertices(g); i++){
        orden[i] = i;
    }
    u32* Coloreo = calloc(NumeroDeVertices(g),sizeof(u32));
    u32 used_colors = Greedy(g,orden,Coloreo);
    printf("Se usaron %u colores\n", used_colors);

    u32* color_appareances = calloc(used_colors, sizeof(u32));

    // Counts the appareances of every colour
    for(u32 i = 0; i < n; i++){
        color_appareances[Coloreo[i]]++;
    }

    for(u32 i = 0; i < used_colors; i++){
        printf("Apariciones del color %u en el coloreo original: %u\n", i, color_appareances[i]);
    }

    // Recolour the original colouring
    u32* new_colouring = RecoloreoCardinalidadDecrecienteBC(n, Coloreo);

    // Reset appareances to count appareances in the new colouring
    for(u32 i = 0; i < used_colors; i++){
        color_appareances[i] = 0;
    }

    // Counts the appareances of every colour in the new colouring
    for(u32 i = 0; i < n; i++){
        color_appareances[new_colouring[i]]++;
    }

    for(u32 i = 0; i < used_colors; i++){
        printf("Apariciones del color %u en el nuevo coloreo: %u\n", i, color_appareances[i]);
    }

    // Check if vertices with same colours still have the same colour after a permutation.
    bool same_colors = true;
    u32* vertices_with_color_k = calloc(NumeroDeVertices(g), sizeof(u32));
    u32 new_color = 0; // Represents the new color after a permutation of a color.
    u32 j = 0;
    for (u32 k = 0; k < used_colors; k++){
        j = 0;
        for(u32 i = 0; i < NumeroDeVertices(g); i++){
            if(Coloreo[i] == k){
                vertices_with_color_k[j] = i;
                j++;
            }
        }

        new_color = new_colouring[vertices_with_color_k[0]];
        for (u32 i = 1; i < j; i++){
            if(new_colouring[vertices_with_color_k[i]] != new_color){
                same_colors = false;
            }
        }
    }

    if (!same_colors){
        printf("ERROR: Los vertices que tenian color 0 antes, no tienen el mismo color entre ellos luego de la permutacion.\n");
        return;
    }

    // Calculates how many colours are used in the new colouring
    u32 new_used_colors = 0;
    bool same_quantity_of_colours = true;
    for (u32 i = 0; i < n; i++)
    {
        if (new_colouring[i] > new_used_colors){
            new_used_colors = new_colouring[i];
        }
    }
    new_used_colors = new_used_colors + 1; // First colour is 0, we have 1 more colour.

    // Check that the amount of colors is the same in both colourings
    if (new_used_colors != used_colors) {
        same_quantity_of_colours = false;
    }

    if (!same_quantity_of_colours)
    {
        printf("ERROR: En el coloreo permutado se usan: %u colores, en Greedy se usan: %u colores\n", new_used_colors, used_colors);
        return;
    }

    //Prints the colour of every vertex in both colourings
    // for(u32 i = 0; i < n; i++){
    //     printf("Color de %u antes del Recoloreo: %u\n", i, Coloreo[i]);
    // }

    // for(u32 i = 0; i < n; i++){
    //     printf("Color de %u despues del Recoloreo: %u\n", i, new_colouring[i]);
    // }

    // Frees all the memory
    free(vertices_with_color_k);
    free(orden);
    free(Coloreo);
    free(color_appareances);
    free(new_colouring);
}

// Tests VIT. Colors should remain the same or decrease in every iteration of Greedy
// if amount of used colors increases there is an Error.
void VIT(u32 n, Grafo g){
    u32* Coloreo = malloc(n * sizeof(u32));
    u32* orden = malloc(n * sizeof(u32));
    u32* key;
    u32 used_colors = 0;
    u32 new_used_colors = 0;
    char error = 0;

    orden = OrdenNatural(orden, n);
    used_colors = Greedy(g, orden, Coloreo);

    for (u32 i = 0; i < 10 && error == 0; i++){
        new_used_colors = Greedy(g, orden, Coloreo);
        //printf("Cantidad de colores usados en la iteracion %u de greedy: %u\n", i, used_colors);
        key = PermutarColores(n, Coloreo, rand());
        error = OrdenFromKey(n, key, orden);
        free(key);
        key = NULL;
        // if(new_used_colors > used_colors){
        //     printf("Error: Se usan mas colores luego de la iteracion de Greedy que antes, no cumple con el VIT\n");
        //     break;
        // }
        // if(error == 1){
        //     printf("Error al alocar memoria en OrdenFromKey\n");
        //     break;
        // }
        used_colors = new_used_colors;
    }
    printf("Se han usado %u colores luego de correr 1058 greedys\n", used_colors);
    free(Coloreo);
    free(orden);
}


int main(){
    Grafo g = ConstruccionDelGrafo();
    u32 n = NumeroDeVertices(g);
    u32 *orden = malloc(n * sizeof(u32));
    u32 *Coloreo = malloc(n * sizeof(u32));
    u32* key;
    u32 used_colors = 0;
    u32 new_used_colors = 0;
    char error = 0;

    orden = OrdenNatural(orden, n);
    used_colors = Greedy(g, orden, Coloreo);
    for (u32 i = 0; i < 1058 && error == 0; ++i){
        for (u32 j = 0; j < n; ++j) {
            printf("%u ", orden[j]);
        }
        printf("\n");
        new_used_colors = Greedy(g, orden, Coloreo);
        //printf("Cantidad de colores usados en la iteracion %u de greedy: %u\n", i, used_colors);
        key = PermutarColores(n, Coloreo, rand());
        error = OrdenFromKey(n, key, orden);
        free(key);
        key = NULL;
        // if(new_used_colors > used_colors){
        //     printf("Error: Se usan mas colores luego de la iteracion de Greedy que antes, no cumple con el VIT\n");
        //     break;
        // }
        // if(error == 1){
        //     printf("Error al alocar memoria en OrdenFromKey\n");
        //     break;
        // }
        used_colors = new_used_colors;
    }

    free(Coloreo);
    free(orden);
    Coloreo = NULL;
    orden = NULL;
    /*Bipartito_test(g);
    Greedy_test(g);
    OrdenFromKeyTest(NumeroDeVertices(g), g);
    Permutation_test(g);
    RecoloreoCardinalidadDecrecienteBCTest(NumeroDeVertices(g), g);*/
    //VIT(NumeroDeVertices(g), g);
    DestruccionDelGrafo(g);
    g = NULL;
    return 0;
}
