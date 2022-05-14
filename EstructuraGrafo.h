#ifndef __ESTRUCTURAGRAFO_H
#define __ESTRUCTURAGRAFO_H
#include "u32.h"

struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 posicion;
    u32 indiceVec;
};

typedef struct VerticeSt VerticeSt;
typedef VerticeSt *Vertice;

struct LadoSt {
    Vertice a;
    Vertice b;
};

typedef struct LadoSt LadoSt;
typedef LadoSt *Lado;

struct GrafoSt {
    u32 n_vertices;
    u32 m_lados;
    u32 delta;
    Vertice *vertices;
    Lado *vecinos;
};

typedef struct GrafoSt GrafoSt;

#endif
