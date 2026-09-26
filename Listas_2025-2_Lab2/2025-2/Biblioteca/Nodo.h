//
// Created by crack on 1/05/2026.
//

#ifndef INC_2025_2_NODO_H
#define INC_2025_2_NODO_H
#include "Jugador.h"
struct  Nodo {
    struct Jugador jugador;
    struct Nodo* siguiente;
};
#endif //INC_2025_2_NODO_H