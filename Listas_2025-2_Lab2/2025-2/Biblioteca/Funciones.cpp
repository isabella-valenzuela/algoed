//
// Created by crack on 1/05/2026.
//

#include "Funciones.h"

void inicializarLista(struct Lista &lista) {
    lista.cabeza=nullptr;
    lista.tamaño=0;
}

bool esListaVacia(const struct Lista &lista) {
    return lista.cabeza==nullptr;
}


void insertarJugador(struct Lista &lista , struct Jugador &jugador) {
    struct Nodo *ultimo=obtenerUltimoNodo(lista);
    struct Nodo *nuevo;
    nuevo=new Nodo;
    nuevo->jugador=jugador;
    nuevo->siguiente=nullptr;
    if (lista.cabeza==nullptr) {
        lista.cabeza=nuevo;
    }else {
        ultimo->siguiente=nuevo;
    }
    lista.tamaño++;
}

struct Nodo *obtenerUltimoNodo(struct Lista &lista) {
    struct Nodo *ultimo;
    struct Nodo *recorrido=lista.cabeza;
    while (recorrido!=nullptr) {
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}


void reordenaFormacion(struct Lista &lista,const char *poscion) {
    int i=0;
    struct Nodo *recorrido=lista.cabeza;
    struct Nodo *ultimo=obtenerUltimoNodo(lista);
    struct Nodo *anterior=nullptr;
    while (recorrido!=nullptr) {
        if (strcmp(recorrido->jugador.posicion,poscion)==0) {
            if (recorrido!=nullptr) {
                if (anterior==nullptr) {
                    lista.cabeza=recorrido->siguiente;
                    ultimo->siguiente=recorrido;
                    recorrido->siguiente=nullptr;
                }
                else if (recorrido!=ultimo) {
                    anterior->siguiente=recorrido->siguiente;
                    ultimo->siguiente=recorrido;
                    recorrido->siguiente=nullptr;
                }
            }
            recorrido=lista.cabeza;
            ultimo=obtenerUltimoNodo(lista);
            i++;
            if (i==2) break;
        }else {
            anterior=recorrido;
            recorrido=recorrido->siguiente;
        }

    }
    // while (recorrido!=nullptr) {
    //     if (strcmp(recorrido->jugador.posicion,"Portero")==0) {
    //         if (recorrido!=nullptr) {
    //             if (anterior==nullptr) {
    //
    //             }else {
    //                 anterior->siguiente=recorrido->siguiente;
    //                 recorrido->siguiente=anterior;
    //                 lista.cabeza=recorrido;
    //
    //             }
    //         }
    //         recorrido=recorrido->siguiente;
    //     }else {
    //         anterior=recorrido;
    //         recorrido=recorrido->siguiente;
    //     }

    //}
}

