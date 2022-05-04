#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "EstructuraGrafo.h"
#include "queue.h"

struct _s_queue {
    u32 elem;
    struct _s_queue *next;
};

queue queue_empty(void) {
    return NULL;
}

queue queue_enqueue(queue q, u32 e) {
    queue new_node = calloc(1, sizeof(struct _s_queue));
    new_node->elem= e;
    new_node->next = q;
    q = new_node;
    return q;
}

bool queue_is_empty(queue q) {
    return q == NULL;
}

u32 queue_first(queue q) {
    u32 e;
    assert(!queue_is_empty(q));
    while(q->next != NULL){
        q = q->next;
    }
    e = q->elem;
    return e;
}

unsigned int queue_size(queue q) {
    unsigned int size=0;
    while (q != NULL) {
        size++;
        q = q->next;
    }
    return size;
}

queue queue_dequeue(queue q) {
    queue p = q;
    assert(!queue_is_empty(q));
    if(q->next == NULL){
        free(q);
        q = NULL;
    } else {
        while(p->next->next != NULL){
            p = p->next;
        }
        free(p->next);
        p->next = NULL;
    }
    return q;
}

queue queue_destroy(queue q) {
    queue aux=NULL;
    while (q != NULL) {
        aux=q;
        q = q->next;
        free(aux);
    }
    return q;
}

