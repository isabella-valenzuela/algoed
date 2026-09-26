//
// Created by crack on 2/05/2026.
//

#ifndef INC_2025_1_FUNCIONES_H
#define INC_2025_1_FUNCIONES_H

#include "Lista.h"

void crearLista(struct Lista &lista);
void insertarCuadrigaAlFinal(struct Lista &lista,struct Cuadriga &cuadriga);
struct Nodo *obtenerUltimoNodo(struct Lista &lista);
void contarParesEImpares(struct Lista &lista,int &cantPares,int &cantImpares);
void ordenarLista(struct Lista &lista,const int cantPares,const int cantImpares);
#endif //INC_2025_1_FUNCIONES_H