/*
 * Laboratorio 4 (2026-1) - Pregunta 2
 * Ciudades del Peru y su distancia desde Lima.
 *  - Ordenar por distancia con merge sort, O(n log n), manteniendo nombre y distancia juntos.
 *  - Contar e imprimir las ciudades en el rango [D1, D2] con dos busquedas binarias
 *    recursivas (divide y venceras), O(log n).
 */
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX = 20;

struct Ciudad {
    char nombre[30];
    int distancia;
};

/* Impresion simple (no recursiva) */
void imprimirCiudades(const char *titulo, const Ciudad c[], int ini, int fin) {
    if (titulo != nullptr) cout << titulo << endl;
    for (int i = ini; i <= fin; i++)
        cout << "  " << left << setw(9) << c[i].nombre << ": " << c[i].distancia << " km." << endl;
}

void mezclar(Ciudad c[], int ini, int med, int fin) {
    Ciudad aux[MAX];
    int i = ini, j = med + 1, k = 0;
    while (i <= med && j <= fin) aux[k++] = (c[i].distancia <= c[j].distancia) ? c[i++] : c[j++];
    while (i <= med) aux[k++] = c[i++];
    while (j <= fin) aux[k++] = c[j++];
    for (int t = 0; t < k; t++) c[ini + t] = aux[t];
}

/* Merge sort por distancia: se mueve la estructura completa, asi los datos siguen asociados */
void ordenarPorDistancia(Ciudad c[], int ini, int fin) {
    if (ini >= fin) return;
    int med = (ini + fin) / 2;
    ordenarPorDistancia(c, ini, med);
    ordenarPorDistancia(c, med + 1, fin);
    mezclar(c, ini, med, fin);
}

/*
 * Primera posicion con distancia >= d1 (limite inferior). Si c[med] >= d1, la
 * respuesta esta en med o a la izquierda; si no, a la derecha. Devuelve n si no hay.
 */
int limiteInferior(const Ciudad c[], int ini, int fin, int d1) {
    if (ini > fin) return ini;
    int med = (ini + fin) / 2;
    if (c[med].distancia >= d1) return limiteInferior(c, ini, med - 1, d1);
    return limiteInferior(c, med + 1, fin, d1);
}

/*
 * Ultima posicion con distancia <= d2 (limite superior). Si c[med] <= d2, la
 * respuesta esta en med o a la derecha; si no, a la izquierda. Devuelve -1 si no hay.
 */
int limiteSuperior(const Ciudad c[], int ini, int fin, int d2) {
    if (ini > fin) return fin;
    int med = (ini + fin) / 2;
    if (c[med].distancia <= d2) return limiteSuperior(c, med + 1, fin, d2);
    return limiteSuperior(c, ini, med - 1, d2);
}

void buscarEnRango(const Ciudad c[], int n, int d1, int d2) {
    int desde = limiteInferior(c, 0, n - 1, d1);
    int hasta = limiteSuperior(c, 0, n - 1, d2);
    int total = (desde <= hasta) ? hasta - desde + 1 : 0;
    cout << "Ciudades entre " << d1 << " km y " << d2 << " km" << endl;
    if (total == 0) cout << "  No hay ciudades en ese rango" << endl;
    else imprimirCiudades(nullptr, c, desde, hasta);
    cout << "Total: " << total << " ciudades" << endl;
}

void ejecutarCaso(int numero, const Ciudad datos[], int n, int d1, int d2) {
    cout << "========== Caso " << numero << " (D1=" << d1 << ", D2=" << d2 << ") ==========" << endl;
    Ciudad c[MAX];
    for (int i = 0; i < n; i++) c[i] = datos[i];
    imprimirCiudades("Ciudades al inicio", c, 0, n - 1);
    ordenarPorDistancia(c, 0, n - 1);
    imprimirCiudades("Ciudades ordenadas por distancia", c, 0, n - 1);
    buscarEnRango(c, n, d1, d2);
    cout << endl;
}

int main() {
    /* Datos cargados directamente en el codigo */
    Ciudad base[] = {
        {"Lima", 34}, {"Cusco", 12}, {"Arequipa", 67}, {"Trujillo", 8},
        {"Piura", 45}, {"Iquitos", 23}, {"Tacna", 89}, {"Puno", 5}
    };
    Ciudad soloPuno[] = {{"Puno", 15}};
    Ciudad caso6[] = {
        {"Lima", 10}, {"Cusco", 20}, {"Arequipa", 30}, {"Trujillo", 40}, {"Piura", 50}
    };

    ejecutarCaso(1, base, 8, 10, 45);     /* Total 4 */
    ejecutarCaso(2, base, 8, 90, 100);    /* Total 0 */
    ejecutarCaso(3, base, 8, 5, 89);      /* Total 8 */
    ejecutarCaso(4, base, 8, 23, 23);     /* Total 1 */
    ejecutarCaso(5, soloPuno, 1, 10, 20); /* Total 1 */
    ejecutarCaso(6, caso6, 5, 25, 35);    /* Total 1 */
    return 0;
}
