//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal 

#ifndef LISTASIMPLEMENTEENLAZADA_LISTA_H
#define LISTASIMPLEMENTEENLAZADA_LISTA_H
#include "NodoLista.h"
struct Lista {
    struct NodoLista * inicio;
    struct NodoLista * fin; //Esto se agregó por la particularidad del problema del O(1)
    int longitud;
};
#endif //LISTASIMPLEMENTEENLAZADA_LISTA_H