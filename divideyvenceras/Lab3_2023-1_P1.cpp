/*
 * Laboratorio 3 (2023-1) - Pregunta 1
 * Pilas de guerreros Kupa: unir, ordenar (mayor a menor) y pasar al mundo champinon.
 * Las pilas se implementan como listas enlazadas. En ningun momento se crean nodos
 * nuevos durante las operaciones: siempre se mueven los nodos existentes.
 */
#include <iostream>
using namespace std;

struct Nodo {
    int ataque;
    Nodo *sig;
};

struct Pila {
    Nodo *cima;
    int longitud;
};

void construirPila(Pila &p) {
    p.cima = nullptr;
    p.longitud = 0;
}

bool esPilaVacia(const Pila &p) {
    return p.cima == nullptr;
}

/* Solo se usa para cargar los datos iniciales del caso de prueba */
void apilar(Pila &p, int valor) {
    Nodo *nuevo = new Nodo;
    nuevo->ataque = valor;
    nuevo->sig = p.cima;
    p.cima = nuevo;
    p.longitud++;
}

/* Saca el nodo de la cima SIN liberarlo, para poder moverlo a otra pila */
Nodo *desapilarNodo(Pila &p) {
    Nodo *nodo = p.cima;
    p.cima = nodo->sig;
    nodo->sig = nullptr;
    p.longitud--;
    return nodo;
}

/* Coloca un nodo ya existente en la cima de la pila */
void apilarNodo(Pila &p, Nodo *nodo) {
    nodo->sig = p.cima;
    p.cima = nodo;
    p.longitud++;
}

int verCima(const Pila &p) {
    return p.cima->ataque;
}

void imprimirPila(const char *titulo, const Pila &p) {
    cout << titulo;
    for (Nodo *r = p.cima; r != nullptr; r = r->sig) {
        cout << r->ataque;
        if (r->sig != nullptr) cout << " -> ";
    }
    cout << endl;
}

void destruirPila(Pila &p) {
    while (!esPilaVacia(p)) delete desapilarNodo(p);
}

/*
 * a) Unir las dos pilas en una sola.
 * Estrategia: se desapilan los nodos de la pila 2 y se apilan directamente en la
 * pila 1. Como se mueven los mismos nodos, no se usa memoria extra ni otra
 * estructura. Al final la pila 2 queda vacia. Complejidad O(m).
 */
void unirPilas(Pila &pila1, Pila &pila2) {
    while (!esPilaVacia(pila2)) {
        apilarNodo(pila1, desapilarNodo(pila2));
    }
}

/*
 * b) Ordenar la pila unica de mayor a menor (el mayor queda en la cima).
 * Estrategia: se usa una sola pila auxiliar que se mantiene ordenada con el menor
 * en la cima. Se saca un nodo de la pila original; mientras la cima de la auxiliar
 * sea menor que ese nodo, se devuelven esos nodos a la pila original. Luego se
 * apila el nodo en la auxiliar. Al terminar, se pasan todos los nodos de la
 * auxiliar a la original, con lo que el mayor queda en la cima. Complejidad O(n^2).
 */
void ordenarPila(Pila &pila) {
    Pila auxiliar;
    construirPila(auxiliar);
    while (!esPilaVacia(pila)) {
        Nodo *actual = desapilarNodo(pila);
        while (!esPilaVacia(auxiliar) && verCima(auxiliar) < actual->ataque) {
            apilarNodo(pila, desapilarNodo(auxiliar));
        }
        apilarNodo(auxiliar, actual);
    }
    /* La auxiliar tiene el menor en la cima: al pasarla, el mayor queda arriba */
    while (!esPilaVacia(auxiliar)) {
        apilarNodo(pila, desapilarNodo(auxiliar));
    }
}

/*
 * c) Pasar los guerreros a la pila del mundo champinon respetando el orden.
 * Estrategia: recursion. Se desapila la cima, se pasa recursivamente el resto
 * y, al volver de la recursion, se apila el nodo guardado en la pila destino.
 * Asi el fondo de la pila origen es el primero en llegar al destino y el orden se
 * conserva. No se usan estructuras adicionales. Complejidad O(n).
 */
void pasarPila(Pila &origen, Pila &destino) {
    if (esPilaVacia(origen)) return;
    Nodo *nodo = desapilarNodo(origen);
    pasarPila(origen, destino);
    apilarNodo(destino, nodo);
}

/* Carga una pila de modo que datos[0] quede en la cima */
void cargarPila(Pila &p, const int datos[], int n) {
    for (int i = n - 1; i >= 0; i--) apilar(p, datos[i]);
}

void ejecutarCaso(int numero, const int d1[], int n1, const int d2[], int n2) {
    cout << "===== Caso " << numero << " =====" << endl;
    Pila robot1, robot2, champinon;
    construirPila(robot1);
    construirPila(robot2);
    construirPila(champinon);
    cargarPila(robot1, d1, n1);
    cargarPila(robot2, d2, n2);
    imprimirPila("Robot Kupa 1: ", robot1);
    imprimirPila("Robot Kupa 2: ", robot2);

    unirPilas(robot1, robot2);
    imprimirPila("Pila unida: ", robot1);

    ordenarPila(robot1);
    imprimirPila("Pila unica ordenada: ", robot1);

    pasarPila(robot1, champinon);
    imprimirPila("Pila en el mundo champinon: ", champinon);
    cout << endl;
    destruirPila(champinon);
}

int main() {
    /* Caso del enunciado */
    int a1[] = {85, 15, 56, 30, 27};
    int b1[] = {45, 22, 68, 20};
    ejecutarCaso(1, a1, 5, b1, 4);

    /* Caso con repetidos y pilas de distinto tamano */
    int a2[] = {10, 40, 10};
    int b2[] = {5, 90, 40, 1, 70};
    ejecutarCaso(2, a2, 3, b2, 5);

    /* Caso con una pila vacia */
    int a3[] = {3, 1, 2};
    ejecutarCaso(3, a3, 3, nullptr, 0);
    return 0;
}
