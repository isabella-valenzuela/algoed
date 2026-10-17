#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "BibliotecaPila/ElementoPila.h"
#include "BibliotecaPila/funcionesPila.h"
#include "BibliotecaPila/NodoPila.h"
#include "BibliotecaPila/Pila.h"

bool esMayuscula(char c) {
    return    (c >= 'A' && c <= 'Z');
}
bool esMinuscula(char c) {
    return (c >= 'a' && c <= 'z');
}

char pasarMinuscula(char c) {
    return  c - 'A'  + 'a';
}
char pasarMayuscula(char c) {
    return c - 'a'  + 'A';
}
bool esSecuenciaValida(char *secuencia) {
    Pila pila;
    NodoPila nodo;
    ElementoPila elemento;
    construir(pila);
    for (int i = 0; secuencia[i] != '\0'; i++) {
        elemento.codigo = secuencia[i];
        nodo.elemento = elemento;
        nodo.siguiente = nullptr;
        if (not(secuencia[i]>= 'A' && secuencia[i] <= 'Z' or
            secuencia[i] >= 'a' && secuencia[i] <= 'z' )) {
            return false;
        }

        if (esPilaVacia(pila)) {
            if (esMinuscula(secuencia[i]) ) {
                return false;
            }
            apilar(pila, elemento);
        }
        else {
            ElementoPila elementoCima;
            elementoCima = cima(pila);
            if (secuencia[i] == elementoCima.codigo) return false;
            if (esMayuscula(secuencia[i]) and esMayuscula(elementoCima.codigo)) {
                apilar(pila, elemento);
            }else {
                char secMin = secuencia[i];
                if (esMayuscula(secuencia[i])) secMin = pasarMinuscula(secuencia[i]);
                char cimMin = elementoCima.codigo;
                if (esMayuscula(elementoCima.codigo)) cimMin = pasarMinuscula(elementoCima.codigo);
                if ( esMinuscula(secuencia[i]) and esMayuscula(elementoCima.codigo) and cimMin == secMin) {
                    desapilar(pila) ;
                }
            }
        }

    }
    if (esPilaVacia(pila))return true;
    return false;
}


void impresion(char secuencia[100]) {
    cout<<"Secuencia: "<<secuencia<<endl;
    bool valido = esSecuenciaValida(secuencia);
    cout << "Salida: Secuencia ";
    if (valido) cout << "valida" << endl;
    else cout << "invalida" << endl;
}

int main() {
    char secuencia2[100]="ABba";
    impresion(secuencia2);
    char secuencia3[100]="ABabCcAa";
    impresion(secuencia3);
    char secuencia[100]="ABbaCcAa";
    impresion(secuencia);

    return 0;
}
