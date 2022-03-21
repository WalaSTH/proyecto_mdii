#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;

int main() {
    char *x;
    u32 y, z;
    FILE *fp;
    size_t i = 0;

    unsigned int *ordArray = malloc(sizeof(u32)*3);
    
    fp = fopen("datos.txt", "r");

    while(i<3){
        fscanf(fp, "%c %u %u\n", x, &y, &z);
        ordArray[i] = y;
        printf("%s %u %u\n", x, ordArray[i], z);
        ++i;
    }
    
    
    return 0;
}
