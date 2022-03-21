#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;

int main() {
    char *x = malloc(sizeof(char)*2);
    assert(x!=NULL);
    u32 y, z, n;
    FILE *fp;

    n = 3;
    unsigned int *ordArray = malloc(sizeof(u32)*(2*n));
    assert(ordArray!=NULL);
    
    // Empiezo a leer datos
    fp = fopen("datos.txt", "r");
    for(size_t i = 0; i<n; ++i){
        fscanf(fp, "%c %u %u\n", x, &y, &z);
        
        // Forma de indezar ordArray[ancho * fila + columna]
        ordArray[2*i] = y;
        ordArray[2*i+1] = z;
    }
    
    fclose(fp);
    // Termine de leer datos

    for(u32 i=0; i<(2*n); ++i)
        printf("%u\n", ordArray[i]);
    
    free(x);
    free(ordArray);
    return 0;
}
