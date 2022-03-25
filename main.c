#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;

int main() {
    char *id = malloc(sizeof(char)*2);
    assert(id!=NULL);
    u32 y = 0, z = 0, nodes = 0, edges = 0;
    FILE *fp = NULL;

    fp = fopen("datos.txt", "r");
    assert(fp != NULL);
    // while(fscanf(fp, "%c %*s\n", id) == 1 && strcmp(id, "c")==0){
    //     printf("id=%s", id);
    //     if(strcmp(id, "c")==0)
    //         continue;
    //     else
    //         break;
    // }
    fscanf(fp, "%c %*s %u %u\n", id, &nodes, &edges);
    assert(strcmp(id,"p") == 0);
    
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
