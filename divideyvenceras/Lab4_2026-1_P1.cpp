/*
 * Laboratorio 4 (2026-1) - Pregunta 1
 * Almacen de polos mundialistas: polo con mayor cantidad de unidades y cuantas hay.
 * Estrategia (divide y venceras, sin ordenar el arreglo):
 *  - Se divide el almacen en dos mitades y cada mitad devuelve su polo candidato.
 *  - Se cuentan las apariciones de ambos candidatos en todo el rango [ini, fin]
 *    (recorrido lineal) y se devuelve el que aparece mas veces.
 *  - Recurrencia T(n) = 2T(n/2) + O(n)  =>  O(n log n).
 */
#include <iostream>
using namespace std;

struct Resultado {
    char polo;
    int cantidad;
};

/* Cuenta cuantas veces aparece 'polo' en el rango [ini, fin] */
int contarEnRango(const char almacen[], int ini, int fin, char polo) {
    int cantidad = 0;
    for (int i = ini; i <= fin; i++)
        if (almacen[i] == polo) cantidad++;
    return cantidad;
}

Resultado poloMasFrecuente(const char almacen[], int ini, int fin) {
    if (ini == fin) {
        Resultado r = {almacen[ini], 1};
        return r;
    }
    int med = (ini + fin) / 2;
    Resultado izq = poloMasFrecuente(almacen, ini, med);
    Resultado der = poloMasFrecuente(almacen, med + 1, fin);

    /* Si ambas mitades coinciden en el candidato, basta sumar sus cantidades */
    if (izq.polo == der.polo) {
        Resultado r = {izq.polo, izq.cantidad + der.cantidad};
        return r;
    }
    int cantIzq = contarEnRango(almacen, ini, fin, izq.polo);
    int cantDer = contarEnRango(almacen, ini, fin, der.polo);
    Resultado r;
    if (cantIzq >= cantDer) { r.polo = izq.polo; r.cantidad = cantIzq; }
    else                    { r.polo = der.polo; r.cantidad = cantDer; }
    return r;
}

void ejecutarCaso(int numero, const char almacen[], int n) {
    cout << "Caso " << numero << ": N=" << n << " Almacen = {";
    for (int i = 0; i < n; i++) cout << "'" << almacen[i] << "'" << (i < n - 1 ? "," : "");
    cout << "}" << endl;
    Resultado r = poloMasFrecuente(almacen, 0, n - 1);
    cout << "  Polos con mas unidades: " << r.polo << endl;
    cout << "  Cantidad de polo: " << r.cantidad << endl << endl;
}

int main() {
    char c1[] = {'A', 'F', 'B', 'F', 'F', 'C', 'C', 'F'};               /* F, 4 */
    char c2[] = {'P'};                                                   /* P, 1 */
    char c3[] = {'B', 'B', 'A', 'C', 'A', 'B', 'D', 'A', 'B'};           /* B, 4 */
    char c4[] = {'E', 'E', 'E', 'E', 'E', 'E'};                          /* E, 6 */
    char c5[] = {'M', 'N', 'M', 'K', 'N', 'K', 'N', 'M', 'N', 'K', 'N'}; /* N, 5 */
    ejecutarCaso(1, c1, 8);
    ejecutarCaso(2, c2, 1);
    ejecutarCaso(3, c3, 9);
    ejecutarCaso(4, c4, 6);
    ejecutarCaso(5, c5, 11);
    return 0;
}
