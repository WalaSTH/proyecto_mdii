#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"


typedef struct QueueSt * Queue;

Queue QueueEmpty(void);

Queue QueueEnqueue(Queue q, u32 e);

bool QueueIsEmpty(Queue q);

u32 QueueSize(Queue q);

u32 QueueFirst(Queue q);

Queue QueueDequeue(Queue q);

Queue QueueDestroy(Queue q);

#endif
