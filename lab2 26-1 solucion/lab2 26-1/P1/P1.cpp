// g++ -g -o algoed .\P1.cpp .\funcionesLista.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "BibliotecaLista/Estructuras.h"
#include "BibliotecaLista/funcionesLista.h"

void crear_baraja(Baraja &baraja) {
    Carta carta;
    construir(baraja);

    for (int i=1;i<=13;i++) {
        carta.numero=i;
        carta.palo = 'C';
        insertarAlFinal(baraja, carta);
    }
    for (int i=1;i<=13;i++) {
        carta.numero=i;
        carta.palo = 'D';
        insertarAlFinal(baraja, carta);
    }
    for (int i=1;i<=13;i++) {
        carta.numero=i;
        carta.palo = 'T';
        insertarAlFinal(baraja, carta);
    }
    for (int i=1;i<=13;i++) {
        carta.numero=i;
        carta.palo = 'E';
        insertarAlFinal(baraja, carta);
    }

}

NodoBaraja* extraer_en_posicion(Baraja &baraja, int posicion) {
    struct NodoBaraja * ultimo = nullptr;
    struct NodoBaraja * recorrido = baraja.inicio;

    for (int i=0; i<posicion; i++) {
        ultimo = recorrido;
        if (recorrido != nullptr) recorrido = recorrido->siguiente;
    }

    if (recorrido != nullptr) {
        if (ultimo == nullptr)
            baraja.inicio = recorrido->siguiente;
        else
            ultimo->siguiente = recorrido->siguiente;
        if (recorrido->siguiente == nullptr) baraja.fin = ultimo;
        baraja.longitud--;
        return recorrido;
    }
    return nullptr;
}

void barajar(Baraja &baraja) {
    for (int i=0;i<52;i++) {
        srand(time(nullptr));
        int pos = rand()%(52-i); // la zona pendiente se va reduciendo
        if (i==51) pos=0; // por sea caso

        NodoBaraja* nodoExtraido = extraer_en_posicion(baraja, pos);
        if (nodoExtraido != nullptr) {
            Carta cartaExtraida {.numero = nodoExtraido->carta.numero,
                                 .palo = nodoExtraido->carta.palo};
            delete nodoExtraido;

            insertarAlFinal(baraja, cartaExtraida);
        }
    }
}

// copypasteado de la biblioteca
void destruir(Baraja &baraja) {
    /*recorrido apunta al inicio del tad*/
    struct NodoBaraja * recorrido = baraja.inicio;

    while (recorrido != nullptr) {
        /*NodoLista auxiliar que va servir para eliminar los NodoListas*/
        struct NodoBaraja * NodoListaAEliminar = recorrido;
        recorrido = recorrido->siguiente;
        delete NodoListaAEliminar;
    }
    /*la lista queda vacia*/
    baraja.inicio = nullptr;
    baraja.fin = nullptr;
    baraja.longitud = 0;
}

int main(int argc, char **argv) {
    Baraja baraja;

    crear_baraja(baraja);
    cout << "----------------------------" << endl;
    cout << "BARAJA ORIGINAL" << endl;
    cout << "----------------------------" << endl;
    imprimir(baraja);

    barajar(baraja);
    cout << endl << "----------------------------" << endl;
    cout << "BARAJADO" << endl;
    cout << "----------------------------" << endl;
    imprimir(baraja);

    destruir(baraja);
    cout << endl << "----------------------------" << endl;
    cout << "LIBERAR MEMORIA" << endl;
    cout << "----------------------------" << endl;
    imprimir(baraja);

    return 0;
}
