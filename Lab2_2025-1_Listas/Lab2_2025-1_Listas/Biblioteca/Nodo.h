//
// Created by crack on 2/05/2026.
//

#ifndef INC_2025_1_NODO_H
#define INC_2025_1_NODO_H
#include "Cuadriga.h"
struct Nodo {
    struct Cuadriga cuadrigas;
    struct Nodo *siguiente;
};
#endif //INC_2025_1_NODO_H