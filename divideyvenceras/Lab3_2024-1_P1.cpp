/*
 * Laboratorio 3 (2024-1) - Pregunta 1
 * DLP: suma de paquetes contiguos con la acumulacion negativa mas alta
 * (subarreglo de suma minima) usando divide y venceras.
 */
#include <iostream>
using namespace std;

struct Resultado {
    int suma;
    int ini;   /* indice inicial (base 0) */
    int fin;   /* indice final (base 0) */
};

/*
 * Subarreglo minimo que cruza el centro: desde med se avanza hacia la izquierda
 * acumulando y guardando la menor suma; igual desde med+1 hacia la derecha. La
 * respuesta es la union de ambos tramos. Son dos ciclos simples (sin anidar).
 */
Resultado minimoCruzado(const int marcas[], int ini, int med, int fin) {
    int suma = 0, mejorIzq = marcas[med], posIzq = med;
    for (int i = med; i >= ini; i--) {
        suma += marcas[i];
        if (suma < mejorIzq) { mejorIzq = suma; posIzq = i; }
    }
    suma = 0;
    int mejorDer = marcas[med + 1], posDer = med + 1;
    for (int j = med + 1; j <= fin; j++) {
        suma += marcas[j];
        if (suma < mejorDer) { mejorDer = suma; posDer = j; }
    }
    Resultado r = {mejorIzq + mejorDer, posIzq, posDer};
    return r;
}

/*
 * Divide y venceras: el subarreglo de suma minima esta completamente en la mitad
 * izquierda, completamente en la derecha o cruza el centro. Se resuelven las dos
 * mitades recursivamente, se calcula el cruzado y se devuelve el menor de los tres.
 * Complejidad O(n log n).
 */
Resultado sumaMinima(const int marcas[], int ini, int fin) {
    if (ini == fin) {
        Resultado r = {marcas[ini], ini, fin};
        return r;
    }
    int med = (ini + fin) / 2;
    Resultado izq = sumaMinima(marcas, ini, med);
    Resultado der = sumaMinima(marcas, med + 1, fin);
    Resultado cru = minimoCruzado(marcas, ini, med, fin);
    if (izq.suma <= der.suma && izq.suma <= cru.suma) return izq;
    if (der.suma <= cru.suma) return der;
    return cru;
}

void ejecutarCaso(int numero, const int marcas[], int n) {
    cout << "Caso " << numero << ": ";
    for (int i = 0; i < n; i++) cout << marcas[i] << (i < n - 1 ? ", " : "");
    Resultado r = sumaMinima(marcas, 0, n - 1);
    cout << endl << "  Acumulacion negativa mas alta: " << r.suma << endl;
    cout << "  Paquetes: ";
    for (int i = r.ini; i <= r.fin; i++) {
        cout << i + 1;
        if (i < r.fin - 1) cout << ", ";
        else if (i == r.fin - 1) cout << " y ";
    }
    cout << endl << endl;
}

int main() {
    int c1[] = {2, 5, -6, 2, 3, -1, -5, 6};
    int c2[] = {2, -3, 4, -5, -7};
    int c3[] = {-4, 5, 6, -4, 3, -1, -5, 6};
    int c4[] = {3, -2, 4, -8, 1};          /* adicional: un solo paquete */
    ejecutarCaso(1, c1, 8);   /* esperado: -7, paquetes 3, 4, 5, 6 y 7 */
    ejecutarCaso(2, c2, 5);   /* esperado: -12, paquetes 4 y 5 */
    ejecutarCaso(3, c3, 8);   /* esperado: -7, paquetes 4, 5, 6 y 7 */
    ejecutarCaso(4, c4, 5);   /* esperado: -8, paquete 4 */
    return 0;
}
