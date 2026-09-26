//
// Created by crack on 1/05/2026.
//

#ifndef INC_2025_2_FUNCIONES_H
#define INC_2025_2_FUNCIONES_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Nodo.h"
#include "Lista.h"
#include "Jugador.h"

void inicializarLista(Lista &);
bool esListaVacia(const struct Lista &lista);
void insertarJugador(struct Lista &lista , struct Jugador &jugador);
struct Nodo *obtenerUltimoNodo(struct Lista &lista);
void reordenaFormacion(struct Lista &lista,const char *poscion);
#endif //INC_2025_2_FUNCIONES_H