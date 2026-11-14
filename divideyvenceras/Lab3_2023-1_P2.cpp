/*
 * Laboratorio 3 (2023-1) - Pregunta 2
 * EGPSI: fusionar 5 listas de PSI (una por categoria, ordenadas por impacto de mayor
 * a menor) en una sola lista, moviendo nodos (sin new durante la fusion).
 * Empates de impacto: va primero la categoria de menor ID (A antes que D).
 */
#include <iostream>
using namespace std;

/* a) Estructuras */
struct NodoPSI {
    char categoria;
    int impacto;
    NodoPSI *sig;
};

struct Lista {
    NodoPSI *cabeza;
    NodoPSI *cola;
    int longitud;
};

void construirLista(Lista &l) {
    l.cabeza = l.cola = nullptr;
    l.longitud = 0;
}

bool esListaVacia(const Lista &l) {
    return l.cabeza == nullptr;
}

/* Solo para la carga de datos (parte a) */
void insertarAlFinal(Lista &l, char categoria, int impacto) {
    NodoPSI *nuevo = new NodoPSI;
    nuevo->categoria = categoria;
    nuevo->impacto = impacto;
    nuevo->sig = nullptr;
    if (esListaVacia(l)) l.cabeza = nuevo;
    else l.cola->sig = nuevo;
    l.cola = nuevo;
    l.longitud++;
}

/* a) Carga de una categoria a partir de los impactos (en el examen se leeria por teclado) */
void cargarCategoria(Lista &l, char categoria, const int impactos[], int n) {
    construirLista(l);
    for (int i = 0; i < n; i++) insertarAlFinal(l, categoria, impactos[i]);
}

/* Engancha el nodo al final de la lista resultado */
void engancharNodo(Lista &res, NodoPSI *nodo) {
    if (res.cabeza == nullptr) res.cabeza = nodo;
    else res.cola->sig = nodo;
    res.cola = nodo;
}

/*
 * b) Fusion de dos listas en la primera (l1), moviendo nodos.
 * l1 siempre contiene categorias con ID menor que las de l2, por eso en empate de
 * impacto se toma primero el nodo de l1.
 * Estrategia:
 *  - Caso O(1): si el ultimo de l1 tiene impacto >= que el primero de l2, basta
 *    enlazar la cola de l1 con la cabeza de l2. Si el ultimo de l2 tiene impacto
 *    estrictamente mayor que el primero de l1, se enlaza l2 delante de l1.
 *  - Caso general O(n1+n2): mezcla como en merge sort, re-enlazando los nodos.
 * Al final l2 queda vacia.
 */
void fusionarListas(Lista &l1, Lista &l2) {
    if (esListaVacia(l2)) return;
    if (esListaVacia(l1)) {
        l1 = l2;
        construirLista(l2);
        return;
    }
    /* Listas que no se interceptan: O(1) */
    if (l1.cola->impacto >= l2.cabeza->impacto) {
        l1.cola->sig = l2.cabeza;
        l1.cola = l2.cola;
    } else if (l2.cola->impacto > l1.cabeza->impacto) {
        l2.cola->sig = l1.cabeza;
        l1.cabeza = l2.cabeza;
    } else {
        /* Caso general: merge re-enlazando nodos */
        NodoPSI *p = l1.cabeza, *q = l2.cabeza;
        Lista res;
        construirLista(res);
        while (p != nullptr && q != nullptr) {
            if (p->impacto >= q->impacto) {   /* empate: gana l1 (menor ID) */
                NodoPSI *s = p->sig;
                engancharNodo(res, p);
                p = s;
            } else {
                NodoPSI *s = q->sig;
                engancharNodo(res, q);
                q = s;
            }
        }
        if (p != nullptr) {
            res.cola->sig = p;
            res.cola = l1.cola;
        } else {
            res.cola->sig = q;
            res.cola = l2.cola;
        }
        l1.cabeza = res.cabeza;
        l1.cola = res.cola;
    }
    l1.cola->sig = nullptr;
    l1.longitud += l2.longitud;
    construirLista(l2);
}

/*
 * b) Reorganizar las 5 categorias en una sola (queda en la lista de la categoria A).
 * Se fusiona A con B, el resultado con C, y asi sucesivamente, lo que respeta el
 * orden por ID en los empates.
 */
void reorganizar(Lista categorias[], int cantidad) {
    for (int i = 1; i < cantidad; i++) fusionarListas(categorias[0], categorias[i]);
}

/* c) Mostrar la lista */
void mostrarLista(const char *titulo, const Lista &l) {
    cout << titulo << endl;
    for (NodoPSI *r = l.cabeza; r != nullptr; r = r->sig) cout << "  " << r->categoria;
    cout << endl;
    for (NodoPSI *r = l.cabeza; r != nullptr; r = r->sig) {
        cout << (r->impacto < 10 ? "  " : " ") << r->impacto;
    }
    cout << endl;
}

void destruirLista(Lista &l) {
    while (l.cabeza != nullptr) {
        NodoPSI *s = l.cabeza->sig;
        delete l.cabeza;
        l.cabeza = s;
    }
    construirLista(l);
}

void ejecutarCaso(int numero, const int *datos[], const int tam[]) {
    cout << "===== Caso " << numero << " =====" << endl;
    const char ids[] = {'A', 'B', 'C', 'D', 'E'};
    Lista categorias[5];
    for (int i = 0; i < 5; i++) cargarCategoria(categorias[i], ids[i], datos[i], tam[i]);
    for (int i = 0; i < 5; i++) {
        char titulo[] = "Categoria X:";
        titulo[10] = ids[i];
        mostrarLista(titulo, categorias[i]);
    }
    reorganizar(categorias, 5);
    mostrarLista("Lista reorganizada:", categorias[0]);
    cout << "Total de PSI: " << categorias[0].longitud << endl << endl;
    destruirLista(categorias[0]);
}

int main() {
    /* Caso del enunciado */
    int A[] = {15, 13, 12, 11}, B[] = {20, 19}, C[] = {18, 17, 16};
    int D[] = {17, 15, 14, 13, 12}, E[] = {14, 12, 10, 8};
    const int *caso1[] = {A, B, C, D, E};
    int tam1[] = {4, 2, 3, 5, 4};
    ejecutarCaso(1, caso1, tam1);

    /* Caso donde todas las listas son disjuntas (solo fusiones O(1)) */
    int A2[] = {5, 4}, B2[] = {20, 18}, C2[] = {3, 1}, D2[] = {10, 9}, E2[] = {15};
    const int *caso2[] = {A2, B2, C2, D2, E2};
    int tam2[] = {2, 2, 2, 2, 1};
    ejecutarCaso(2, caso2, tam2);

    /* Caso con muchos empates y una categoria vacia */
    int A3[] = {10, 5}, B3[] = {10, 5}, D3[] = {10, 7, 5}, E3[] = {5};
    const int *caso3[] = {A3, B3, nullptr, D3, E3};
    int tam3[] = {2, 2, 0, 3, 1};
    ejecutarCaso(3, caso3, tam3);
    return 0;
}
