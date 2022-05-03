#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

typedef struct _s_queue * queue;

queue queue_empty(void);

queue queue_enqueue(queue q, u32 e);

bool queue_is_empty(queue q);

unsigned int queue_size(queue q);

u32 queue_first(queue q);

queue queue_dequeue(queue q);

queue queue_destroy(queue q);

#endif
