#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;

int main() {
    char *x = malloc(sizeof(char)*1);
    assert(x!=NULL);
    u32 y, z;
    FILE *fp;

    unsigned int *ordArray = malloc(sizeof(u32)*3);
    assert(ordArray!=NULL);
    
    fp = fopen("datos.txt", "r");

    for(size_t i = 0; i<3; ++i){
        fscanf(fp, "%c %u %u\n", x, &y, &z);
        ordArray[i] = y;
        printf("%s %u %u\n", x, ordArray[i], z);
    }
    
    fclose(fp);
    free(x);
    free(ordArray);
    return 0;
}
