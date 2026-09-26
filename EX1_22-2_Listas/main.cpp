#include <iostream>

#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/Lista.h"

using namespace std;

void fusionListas(struct Lista &lista1,struct Lista &lista2)
{
    NodoLista *inicioAux, *finAux;
    inicioAux = nullptr;
    finAux = nullptr;
    /*Voy a evaluar el caso de horas disjuntas*/
    if (lista1.fin->elemento.hora < lista2.inicio->elemento.hora)
    {
        inicioAux = lista1.inicio;
        lista1.fin->siguiente = lista2.inicio;
        finAux = lista2.fin;
    }
    else
    {
        if (lista2.fin->elemento.hora < lista1.inicio->elemento.hora)
        {
            inicioAux = lista2.inicio;
            lista2.fin->siguiente = lista1.inicio;
            finAux = lista1.fin;
        }
        else
        {
            NodoLista *recorrido1 = lista1.inicio;
            NodoLista *recorrido2 = lista2.inicio;

            while (recorrido1!=nullptr && recorrido2!=nullptr)
            {
                if (recorrido1->elemento.hora <= recorrido2->elemento.hora)
                {
                    if (inicioAux==nullptr)
                    {
                        inicioAux = recorrido1;
                        finAux = recorrido1;
                    }
                    else
                    {
                        finAux->siguiente = recorrido1;
                        finAux = recorrido1;
                    }
                    recorrido1 = recorrido1->siguiente;
                }
                else
                {
                    if (inicioAux==nullptr)
                    {
                        inicioAux = recorrido2;
                        finAux = recorrido2;
                    }
                    else
                    {
                        finAux->siguiente = recorrido2;
                        finAux = recorrido2;
                    }
                    recorrido2 = recorrido2->siguiente;
                }
            }
            if (recorrido1!=nullptr)
            {
                finAux->siguiente = recorrido1;
                finAux = lista1.fin;
            }
            else
            {
                finAux->siguiente = recorrido2;
                finAux = lista2.fin;
            }
        }
    }
    lista1.inicio = inicioAux;
    lista1.fin = finAux;
    lista1.longitud = lista1.longitud + lista2.longitud;
}

int main()
{
    /*Parte a*/
    Lista listaL, listaM, listaX, listaJ, listaV;
    construir(listaL);
    construir(listaM);
    construir(listaX);
    construir(listaJ);
    construir(listaV);

    /*Vamos a ingresar los datos a la lista*/
    ElementoLista elemento;
    elemento.hora = 8;
    elemento.sucursal = 6;
    insertarAlFinal(listaL,elemento);
    elemento.hora = 10;
    elemento.sucursal = 14;
    insertarAlFinal(listaL,elemento);
    elemento.hora = 12;
    elemento.sucursal = 1;
    insertarAlFinal(listaL,elemento);
    cout << "Lunes:  ";
    imprimir(listaL);
    elemento.hora = 9;
    elemento.sucursal = 3;
    insertarAlFinal(listaM,elemento);
    elemento.hora = 11;
    elemento.sucursal = 8;
    insertarAlFinal(listaM,elemento);
    cout << "Martes: ";
    imprimir(listaM);
    fusionListas(listaL,listaM);
    cout << "Resultado: ";
    imprimir(listaL);
    return 0;
}
