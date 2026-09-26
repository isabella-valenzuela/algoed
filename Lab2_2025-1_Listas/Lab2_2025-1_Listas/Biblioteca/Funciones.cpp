//
// Created by crack on 2/05/2026.
//

#include "Funciones.h"

#include <optional>
#include <random>

void crearLista(struct Lista &lista) {
    lista.cabeza=nullptr;
    lista.cantidad=0;
}


void insertarCuadrigaAlFinal(struct Lista &lista,struct Cuadriga &cuadriga) {
    struct Nodo *ultimo=obtenerUltimoNodo(lista);
    struct Nodo *nuevo=new struct Nodo;
    nuevo->cuadrigas=cuadriga;
    nuevo->siguiente=nullptr;
    if (ultimo==nullptr) {
        lista.cabeza=nuevo;
        lista.cantidad++;
    }else {
        ultimo->siguiente=nuevo;
        lista.cantidad++;
    }
}

struct Nodo *obtenerUltimoNodo(struct Lista &lista) {
    struct Nodo *ultimo=nullptr;
    struct Nodo *recorrido=lista.cabeza;
    while (recorrido!=nullptr) {
        ultimo=recorrido;
        recorrido=recorrido->siguiente;
    }
    return ultimo;
}

void contarParesEImpares(struct Lista &lista,int &cantPares,int &cantImpares) {
    struct Nodo *recorrido=lista.cabeza;
    int id;
    while (recorrido!=nullptr) {
        id=recorrido->cuadrigas.id;
        if (id%2==0) {
            cantPares++;
        }else {
            cantImpares++;
        }
        recorrido=recorrido->siguiente;
    }
}

void ordenarLista(struct Lista &lista,const int cantPares,const int cantImpares) {
    int contCambios=0;
    struct Nodo *ultimo=obtenerUltimoNodo(lista);
    struct Nodo *anterior=nullptr;
    struct Nodo *recorrido1=lista.cabeza;
    while (recorrido1!=nullptr) {
        if (recorrido1->cuadrigas.id%2==0) {
            if (anterior==nullptr) {
                lista.cabeza=recorrido1->siguiente;
                ultimo->siguiente=recorrido1;
                recorrido1->siguiente=nullptr;
            }else {
                anterior->siguiente=recorrido1->siguiente;
                ultimo->siguiente=recorrido1;
                recorrido1->siguiente=nullptr;
            }
            recorrido1=lista.cabeza;
            ultimo=obtenerUltimoNodo(lista);
            contCambios++;
            if (contCambios==cantPares) break;
        }else {
            anterior=recorrido1;
            recorrido1=recorrido1->siguiente;
        }
    }
    //Lo reinicio
    struct Nodo *recorrido2=lista.cabeza;
    ultimo=obtenerUltimoNodo(lista);
    anterior=nullptr;
    contCambios=0;
    while (recorrido2!=nullptr) {
        if (recorrido2->cuadrigas.id%2==1) {
            if (anterior==nullptr) {
                lista.cabeza=recorrido2->siguiente;
                ultimo->siguiente=recorrido2;
                recorrido2->siguiente=nullptr;
            }else {
                anterior->siguiente=recorrido2->siguiente;
                ultimo->siguiente=recorrido2;
                recorrido2->siguiente=nullptr;
            }
            recorrido2=lista.cabeza;
            ultimo=obtenerUltimoNodo(lista);
            contCambios++;
            if (contCambios==cantImpares) break;
        }else {
            anterior=recorrido2;
            recorrido2=recorrido2->siguiente;
        }

    }


}