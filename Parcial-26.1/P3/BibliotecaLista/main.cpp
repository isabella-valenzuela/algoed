//Fecha:  sábado 30 Agosto 2025 
//Autor: Ana Roncal

#include <iostream>
#include "BibliotecaLista/Lista.h"
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
using namespace std;

int longitud(Lista plista) {
    int cont=0;
    NodoLista*ptr;
    ptr=plista.lista;
    while (ptr) {
        ptr=ptr->siguiente;
        cont++;
    }
    return cont;
}

void invierte(Lista &plista) {
    NodoLista*ptr,*ant,*ini;
    int n=longitud(plista);
    for (int i=1;i<n;i++) {
        ptr=plista.lista;
        for (int j=i;j<n;j++) {
            ant=ptr;
            ptr=ptr->siguiente;
        }
        if (i==1)ini=ptr;
        ptr->siguiente=ant;
    }
    plista.lista->siguiente=nullptr;
    plista.lista=ini;
}

NodoLista* avanzarec(NodoLista*ptr) {
    if (ptr->siguiente==nullptr)return ptr;
    NodoLista *ini=avanzarec(ptr->siguiente);
    ptr->siguiente->siguiente=ptr;
    return ini;
}

void invierterec(Lista &plista) {
    NodoLista*ini=avanzarec(plista.lista);
    plista.lista->siguiente=nullptr;
    plista.lista=ini;
}



int main(int argc, char **argv) {

    struct ElementoLista elemento;
    struct Lista listaInicio;
    construir(listaInicio);
    elemento.codigo=18;
    insertarAlFinal(listaInicio,elemento);
    elemento.codigo=10;
    insertarAlFinal(listaInicio,elemento);
    elemento.codigo=5;
    insertarAlFinal(listaInicio,elemento);
    elemento.codigo=12;
    insertarAlFinal(listaInicio,elemento);
    imprimir(listaInicio);
    invierte(listaInicio);
    imprimir(listaInicio);
    invierterec(listaInicio);
    imprimir(listaInicio);
    return 0;
}
