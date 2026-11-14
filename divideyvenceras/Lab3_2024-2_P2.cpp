/*
 * Laboratorio 3 (2024-2) - Pregunta 2
 * Robot perforador: N muestras con N estratos cada una.
 * a) Maxima pureza entre todas las muestras.
 * b) Muestras con mayor cantidad de estratos con minerales (valores distintos de 0).
 */
#include <iostream>
using namespace std;

const int MAX_N = 10;

struct Pico {
    int valor;
    int estrato;   /* base 0 */
};

/*
 * a) En cada muestra la pureza sube hasta un maximo y luego baja. Busqueda binaria
 * del pico: si v[med] < v[med+1] se va a la derecha, si v[med] > v[med+1] se va a
 * la izquierda (incluyendo med). Cuando son iguales (meseta) no se sabe en que lado
 * esta el pico, asi que se resuelven ambas mitades y se queda el mayor.
 * O(log n) por muestra en los casos normales, O(n log n) para las N muestras.
 */
Pico picoMuestra(const int v[], int ini, int fin) {
    if (ini == fin) {
        Pico p = {v[ini], ini};
        return p;
    }
    int med = (ini + fin) / 2;
    if (v[med] < v[med + 1]) return picoMuestra(v, med + 1, fin);
    if (v[med] > v[med + 1]) return picoMuestra(v, ini, med);
    Pico izq = picoMuestra(v, ini, med);
    Pico der = picoMuestra(v, med + 1, fin);
    return (der.valor > izq.valor) ? der : izq;
}

/* Divide y venceras sobre las muestras: mejor pico de la mitad izquierda vs derecha */
int muestraMaxPureza(int m[][MAX_N], int n, int ini, int fin, Pico &pico) {
    if (ini == fin) {
        pico = picoMuestra(m[ini], 0, n - 1);
        return ini;
    }
    int med = (ini + fin) / 2;
    Pico pIzq, pDer;
    int izq = muestraMaxPureza(m, n, ini, med, pIzq);
    int der = muestraMaxPureza(m, n, med + 1, fin, pDer);
    if (pDer.valor > pIzq.valor) { pico = pDer; return der; }
    pico = pIzq;
    return izq;
}

/* Primera posicion con valor distinto de 0 cuando los ceros estan al inicio */
int primerNoCero(const int v[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    if (v[med] != 0) return primerNoCero(v, ini, med);
    return primerNoCero(v, med + 1, fin);
}

/* Primera posicion con valor 0 cuando los ceros estan al final */
int primerCero(const int v[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    if (v[med] == 0) return primerCero(v, ini, med);
    return primerCero(v, med + 1, fin);
}

/*
 * b) La zona sin minerales (ceros) esta solo al inicio o solo al final de la
 * muestra. Se mira un extremo en O(1) para saber de que lado estan y luego se ubica
 * con busqueda binaria el limite entre ceros y minerales. O(log n) por muestra.
 */
int estratosConMineral(const int v[], int n) {
    if (v[0] == 0) return n - primerNoCero(v, 0, n - 1);
    if (v[n - 1] == 0) return primerCero(v, 0, n - 1);
    return n;   /* no hay zona sin minerales */
}

/* Divide y venceras para obtener la mayor cantidad de estratos con minerales */
int maxEstratos(const int cantidades[], int ini, int fin) {
    if (ini == fin) return cantidades[ini];
    int med = (ini + fin) / 2;
    int izq = maxEstratos(cantidades, ini, med);
    int der = maxEstratos(cantidades, med + 1, fin);
    return izq > der ? izq : der;
}

void ejecutarCaso(int numero, int m[][MAX_N], int n) {
    cout << "===== Caso " << numero << " (N = " << n << ") =====" << endl;
    Pico pico;
    int muestra = muestraMaxPureza(m, n, 0, n - 1, pico);
    cout << "La maxima pureza de las muestras es: " << pico.valor
         << " (encontrado en la muestra " << muestra + 1 << ", en el estrato "
         << pico.estrato + 1 << ")" << endl;

    int cantidades[MAX_N];
    for (int i = 0; i < n; i++) cantidades[i] = estratosConMineral(m[i], n);
    int mayor = maxEstratos(cantidades, 0, n - 1);
    int veces = 0;
    for (int i = 0; i < n; i++) if (cantidades[i] == mayor) veces++;
    cout << "Las muestras con mayor cantidad de niveles con minerales son: ";
    int impresas = 0;
    for (int i = 0; i < n; i++) {
        if (cantidades[i] == mayor) {
            cout << i + 1;
            impresas++;
            if (impresas < veces) cout << ", ";
        }
    }
    cout << (veces > 1 ? " ambas con " : " con ") << mayor
         << " estratos de minerales." << endl << endl;
}

int main() {
    int caso1[MAX_N][MAX_N] = {
        {0, 0, 0, 3, 3, 7, 5, 5, 1, 1},
        {8, 8, 10, 9, 9, 5, 4, 4, 2, 0},
        {3, 5, 8, 9, 7, 6, 4, 2, 0, 0},
        {9, 7, 7, 4, 4, 4, 2, 0, 0, 0},
        {0, 2, 2, 3, 3, 4, 4, 5, 3, 3},
        {0, 0, 0, 0, 0, 0, 2, 3, 4, 5},
        {1, 2, 2, 3, 3, 4, 3, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 5, 5, 7},
        {6, 5, 5, 2, 2, 1, 0, 0, 0, 0},
        {3, 2, 2, 0, 0, 0, 0, 0, 0, 0}
    };
    ejecutarCaso(1, caso1, 10);
    /* esperado: pureza 10 (muestra 2, estrato 3); muestras 2, 5 con 9 estratos */

    int caso2[MAX_N][MAX_N] = {
        {0, 0, 1, 4, 2},
        {5, 6, 3, 1, 0},
        {0, 1, 2, 3, 9},
        {2, 2, 0, 0, 0},
        {0, 0, 0, 0, 3}
    };
    ejecutarCaso(2, caso2, 5);
    /* esperado: pureza 9 (muestra 3, estrato 5); muestras 2, 3 con 4 estratos */
    return 0;
}
