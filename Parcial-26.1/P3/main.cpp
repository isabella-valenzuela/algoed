#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/funcionesLista.h"
using namespace std;

struct NodoLista * obtenerUltimoNodo(const struct Lista & listaTAD) {
    struct NodoLista* recorrido = listaTAD.lista;

    if (esListaVacia(listaTAD)) return nullptr;

    while (recorrido->next != listaTAD.lista) {
        recorrido = recorrido->next;
    }
    return recorrido;
}

void agregar_nodo(struct Lista & listaTAD, const struct ElementoLista & elemento) {
    struct NodoLista * ultimoNodoLista = obtenerUltimoNodo(listaTAD);
    struct NodoLista * nuevo;
    nuevo = new struct NodoLista;
    nuevo->elemento = elemento;
    nuevo->next = nullptr;
    nuevo->skip_next = nullptr;

    if (esListaVacia(listaTAD)) {
        nuevo->next = nuevo;
        listaTAD.lista = nuevo;
    }
    else {
        ultimoNodoLista->next = nuevo;
        nuevo->next = listaTAD.lista;
    }
}

void calcular_skip_next(struct Lista & listaTAD) {
    struct NodoLista *actual = listaTAD.lista;
    struct NodoLista *anterior = nullptr;
    do {
        if (anterior != nullptr) {
            anterior->skip_next = actual->next;
        }
        anterior = actual;
        actual = actual->next;
    }while (actual != listaTAD.lista);
    anterior->skip_next = actual->next;

}

void auto_healing(Lista &lista, int &n) {
    if (esListaVacia(lista)) return;                          // NUEVO
    NodoLista *recorrido = lista.lista;
    NodoLista *aux = lista.lista;
    NodoLista *borrar = nullptr;
    NodoLista *ultimo = obtenerUltimoNodo(lista);             // NUEVO
    while (lista.lista->elemento.is_active == false) {        // NUEVO: cabeza caída
        if (n == 1) {                                         // NUEVO: era el único nodo
            delete lista.lista;                               // NUEVO
            lista.lista = nullptr;                            // NUEVO
            n = 0;                                            // NUEVO
            return;                                           // NUEVO
        }                                                     // NUEVO
        borrar = lista.lista;                                 // NUEVO
        lista.lista = borrar->next;                           // NUEVO: nueva cabeza
        ultimo->next = lista.lista;                           // NUEVO: el anillo sigue cerrado
        delete borrar;                                        // NUEVO
        n--;                                                  // NUEVO
    }                                                         // NUEVO
    recorrido = lista.lista;                                  // NUEVO: reubicar con la nueva cabeza
    aux = lista.lista;                                        // NUEVO

    do {
        if (recorrido->next->elemento.is_active == false) {
            aux = recorrido->next;
            do {
                borrar = aux;
                aux = aux->next;
                delete borrar;
                n--;
            }while (aux->elemento.is_active == false);
            recorrido->next = aux;
        }
        recorrido = recorrido->next;
        aux = recorrido;
    }while (recorrido != lista.lista);
    calcular_skip_next(lista);
}

void desactivar_nodo(Lista &lista, int idNodo) {
    NodoLista *recorrido = lista.lista;
    do {
        if (idNodo == recorrido->elemento.node_id) {
            recorrido->elemento.is_active = false;
            cout <<">>> Nodo "<<recorrido->elemento.node_id<<" cae <<<"<<endl;
            cout<<endl;

        }
        recorrido = recorrido->next;
    }while (recorrido != lista.lista);
}

void imprimir(int n, Lista lista) {
    cout<<"Anillo ("<<n<<" nodos):"<<endl;
    NodoLista *nodoAux = lista.lista;
    for (int i = 0; i < n; i++) {
        cout<<"Nodo "<<nodoAux->elemento.node_id;
        if (nodoAux->elemento.is_active) cout<<" [ACTIVO] ";
        else cout<<" [CAIDO] ";
        cout<<"siguiente="<<nodoAux->next->elemento.node_id;
        cout<<" skip_next="<<nodoAux->skip_next->elemento.node_id<<endl;
        nodoAux = nodoAux->next;
    }
    cout<<endl;

}

void creaLista(int &n, Lista &lista, ElementoLista &elementoAux) {
    construir(lista);
    cin>>n;
    for (int i = 1; i <= n; i++) {
        elementoAux.node_id = i*10;
        elementoAux.is_active = true;
        agregar_nodo(lista, elementoAux);
    }
}

int main() {
    int n;
    Lista lista;
    ElementoLista elementoAux;
    creaLista(n, lista, elementoAux);
    calcular_skip_next(lista);

    cout<<"==Estado inicial=="<<endl;
    imprimir(n, lista);

    desactivar_nodo(lista, 10);
    desactivar_nodo(lista, 20);
    cout<<"==Estado antes de auto_healing=="<<endl;
    imprimir(n, lista);
    auto_healing(lista, n);
    cout<<"==Estado despues de auto_healing=="<<endl;
    imprimir(n, lista);

    return 0;
}
