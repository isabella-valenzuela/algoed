//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal

#include <iostream>
#include <iomanip>
#include "Lista.h"
#include "funcionesLista.h"
#include "NodoLista.h"
using namespace std;

void construir(struct Lista & listaTAD) {
    listaTAD.lista = nullptr;
}

bool esListaVacia(const struct Lista & listaTAD) {
    return listaTAD.lista == nullptr;
}

/*Inserta los elementos al inicio de la lista*/
void insertarAlInicio(struct Lista & listaTAD, const struct ElementoLista & elemento) {

    struct NodoLista * nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->next = listaTAD.lista;
    listaTAD.lista = nuevo;
}

/*Inserta un elemento siempre al final de la lista*/
void insertarAlFinal(struct Lista & listaTAD, const struct ElementoLista & elemento) {

    struct NodoLista * ultimoNodoLista = obtenerUltimoNodo(listaTAD);
    struct NodoLista * nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->next = nullptr;
    nuevo->skip_next = nullptr;

    if (ultimoNodoLista == nullptr) /*Si la lista está vacía*/
        listaTAD.lista = nuevo; /*se inserta en la cabeza de la lista*/
    else //La lista ya tiene NodoListas
        ultimoNodoLista->next = nuevo;
}

/*Obtiene el último NodoLista de la lista*/


void insertarEnOrden(struct Lista & listaTAD, const struct ElementoLista & elemento) {

    struct NodoLista *nuevo, *recorrido = listaTAD.lista, * anterior = nullptr;

    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    while(recorrido){
        if(recorrido->elemento.node_id > elemento.node_id) break;
        anterior = recorrido;
        recorrido = recorrido->next;
    }
    nuevo->next = recorrido;
    if(anterior == nullptr) listaTAD.lista = nuevo;
    else anterior->next = nuevo;
}

void eliminaNodo(struct Lista & listaTAD, const struct ElementoLista & elemento) {
    struct NodoLista * ultimo = nullptr;
    struct NodoLista * recorrido = listaTAD.lista;
    /*Avanzo hasta encontrar el elemento*/
    /*Si no lo encuentra no elimina nada*/
    while ((recorrido != nullptr) and (recorrido->elemento.node_id != elemento.node_id)) {
        ultimo = recorrido;
        recorrido = recorrido->next;
    }

    if (recorrido != nullptr) {
        if (ultimo == nullptr) /*Estoy al inicio de la lista*/
            listaTAD.lista = recorrido->next;
        else
            ultimo->next = recorrido->next;
        delete recorrido; /*libera la memoria*/

    }
}

void destruir(struct Lista & listaTAD) {
    /*recorrido apunta al inicio del tad*/
    struct NodoLista * recorrido = listaTAD.lista;

    while (recorrido != nullptr) {
        /*NodoLista auxiliar que va servir para eliminar los NodoListas*/
        struct NodoLista * NodoListaAEliminar = recorrido;
        recorrido = recorrido->next;
        delete NodoListaAEliminar;
    }
    /*la lista queda vacia*/
    listaTAD.lista = nullptr;

}

/*con const aquello que pasas no va cambiar, el compilador se da cuenta que es constante*/
void imprimir(const struct Lista & listaTAD) {

    if (esListaVacia(listaTAD)) {
        cout << "La lista esta vacia no se puede mostrar" << endl;
    } else {
        struct NodoLista * recorrido = listaTAD.lista;
        int estaImprimiendoLaCabeza = 1;
        cout << "[";

        while (recorrido != nullptr) {
            /*Este artificio coloca las comas despuÃ©s de la cabeza*/
            if ( not estaImprimiendoLaCabeza)
                cout << ", ";
            estaImprimiendoLaCabeza = 0;
            cout << recorrido->elemento.node_id;
            recorrido = recorrido->next;
        }
        cout << "]" << endl;
    }
}