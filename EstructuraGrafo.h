#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H
#include <stdint.h>

typedef uint32_t u32;

struct GrafoSt {
    u32 n_vertices;
    u32 m_lados;
    u32 delta;
    u32 **nameGrades;
    u32 **vecinos;
};

typedef struct GrafoSt GrafoSt;

#endif
