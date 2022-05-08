#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "EstructuraGrafo.h"
#include "Queue.h"


struct NodeSt {
    u32 elem;
    struct NodeSt *next;
};

typedef struct NodeSt * Node;

struct QueueSt {
    Node first;
    Node last;
    u32 size;
};

Queue QueueEmpty(void) {
    Queue q = malloc(sizeof(struct QueueSt));
    q->first = NULL;
    q->last = NULL;
    q->size = 0u;
    return q;
}

Queue QueueEnqueue(Queue q, u32 e) {
    Node newNode = malloc(sizeof(struct NodeSt));
    newNode->elem= e;
    newNode->next = NULL;
    if (q->size == 0u) {
        q->first = newNode;
    } else {
        q->last->next = newNode;
    }
    q->last = newNode;
    ++q->size;
    return q;
}

bool QueueIsEmpty(Queue q) {
    return q->size == 0u;
}

u32 QueueFirst(Queue q) {
    return q->first->elem;
}

u32 QueueSize(Queue q) {
    return q->size;
}

Queue QueueDequeue(Queue q) {
    Node oldNode = q->first;
    q->first = oldNode->next;
    if (q->size == 1u) {
        q->last = NULL;
    }
    --q->size;
    free(oldNode);
    oldNode = NULL;
    return q;
}

Queue QueueDestroy(Queue q) {
    while (q->size != 0u) {
        q = QueueDequeue(q);
    }
    free(q);
    q = NULL;
    return q;
}

