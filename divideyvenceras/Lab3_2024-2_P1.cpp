/*
 * Laboratorio 3 (2024-2) - Pregunta 1
 * Bitacora del Centro de Datos: hallar el empleado que ingreso y no salio.
 * Cada empleado aparece 2 veces (ingreso y salida), excepto uno que aparece 3 veces.
 * Estrategia (divide y venceras, O(n log n)):
 *  1) Ordenar la bitacora con merge sort (copia, para no alterar la original).
 *  2) En el arreglo ordenado los registros forman pares que empiezan en posiciones
 *     pares. El empleado con 3 registros desfasa los pares: se busca binariamente
 *     la primera posicion par i con v[i] != v[i+1]; ese es el empleado. O(log n).
 */
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 100;

void mezclar(int v[], int ini, int med, int fin) {
    int aux[MAX];
    int i = ini, j = med + 1, k = 0;
    while (i <= med && j <= fin) aux[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
    while (i <= med) aux[k++] = v[i++];
    while (j <= fin) aux[k++] = v[j++];
    for (int t = 0; t < k; t++) v[ini + t] = aux[t];
}

/* Merge sort: dividir en mitades, ordenar cada una y mezclarlas. O(n log n) */
void ordenarMerge(int v[], int ini, int fin) {
    if (ini >= fin) return;
    int med = (ini + fin) / 2;
    ordenarMerge(v, ini, med);
    ordenarMerge(v, med + 1, fin);
    mezclar(v, ini, med, fin);
}

/* Busqueda binaria sobre pares: el desfase indica al empleado que no salio */
int buscarSinSalida(const int v[], int ini, int fin) {
    if (ini == fin) return v[ini];
    int med = (ini + fin) / 2;
    if (med % 2 == 1) med--;
    if (v[med] == v[med + 1]) return buscarSinSalida(v, med + 2, fin);
    return buscarSinSalida(v, ini, med);
}

int empleadoSinSalida(const int bitacora[], int n) {
    int copia[MAX];
    for (int i = 0; i < n; i++) copia[i] = bitacora[i];
    ordenarMerge(copia, 0, n - 1);
    return buscarSinSalida(copia, 0, n - 1);
}

void ejecutarCaso(int numero, const int bitacora[], int n) {
    cout << "Caso " << numero << ": ";
    for (int i = 0; i < n; i++) cout << setw(2) << setfill('0') << bitacora[i] << " ";
    cout << setfill(' ') << endl;
    cout << "  El empleado " << empleadoSinSalida(bitacora, n)
         << " ingreso y no volvio a salir." << endl << endl;
}

int main() {
    int c1[] = {1, 6, 3, 4, 5, 6, 3, 7, 5, 4, 3, 1, 7};   /* esperado: 3 */
    int c2[] = {2, 2, 9};                                 /* esperado: 9 */
    int c3[] = {8, 1, 8, 2, 1, 2, 1};                     /* esperado: 1 */
    int c4[] = {10, 4, 4, 12, 10, 12, 15, 15, 12};        /* esperado: 12 */
    ejecutarCaso(1, c1, 13);
    ejecutarCaso(2, c2, 3);
    ejecutarCaso(3, c3, 7);
    ejecutarCaso(4, c4, 9);
    return 0;
}
