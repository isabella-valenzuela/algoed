/*
 * Laboratorio 3 (2024-1) - Pregunta 2
 * Oppenheimer: km donde empieza la radiacion y potencia maxima de la bomba.
 * Sin iteraciones y sin recorrer todo el arreglo: solo busquedas binarias recursivas.
 */
#include <iostream>
using namespace std;

/*
 * Inicio de la radiacion: antes de la radiacion todos los valores son <= 0 y
 * despues todos son > 0 (el arreglo termina donde acaba la radiacion). Se busca
 * binariamente la primera posicion con valor positivo. Cada celda es 1 km, asi
 * que la posicion (base 0) es la distancia en km. Complejidad O(log n).
 */
int inicioRadiacion(const int zona[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    if (zona[med] > 0) return inicioRadiacion(zona, ini, med);
    return inicioRadiacion(zona, med + 1, fin);
}

int mayor(int a, int b) { return a > b ? a : b; }

/*
 * Potencia maxima: dentro de la zona con radiacion los valores suben hasta el
 * punto central y luego bajan, y cada nivel ocupa 2 celdas (excepto el centro).
 * Busqueda binaria del pico con manejo de los pares iguales:
 *  - si zona[med] < zona[med+1] el pico esta a la derecha;
 *  - si zona[med] > zona[med+1] el pico esta en med o a la izquierda;
 *  - si son iguales (un par), se mira la celda siguiente al par o la anterior para
 *    saber si el par esta en la subida o en la bajada.
 * Complejidad O(log n).
 */
int potenciaMaxima(const int zona[], int ini, int fin) {
    if (fin - ini <= 1) return mayor(zona[ini], zona[fin]);
    int med = (ini + fin) / 2;
    if (zona[med] < zona[med + 1]) return potenciaMaxima(zona, med + 1, fin);
    if (zona[med] > zona[med + 1]) return potenciaMaxima(zona, ini, med);
    /* zona[med] == zona[med+1] */
    if (med + 2 <= fin && zona[med + 2] > zona[med]) return potenciaMaxima(zona, med + 2, fin);
    if (med - 1 >= ini && zona[med - 1] > zona[med]) return potenciaMaxima(zona, ini, med - 1);
    return zona[med];
}

void ejecutarCaso(int numero, const int zona[], int n) {
    cout << "Caso " << numero << ": ";
    for (int i = 0; i < n; i++) cout << zona[i] << " ";
    int inicio = inicioRadiacion(zona, 0, n - 1);
    int potencia = potenciaMaxima(zona, inicio, n - 1);
    cout << endl << "  La radiacion empieza a " << inicio << " km. Potencia maxima "
         << potencia << " megatones." << endl << endl;
}

int main() {
    int c1[] = {0, -1, 0, -1, 0, 1, 1, 2, 2, 3, 2, 2, 1, 1};
    int c2[] = {-1, 0, -1, 0, 1, 1, 2, 2, 3, 3, 4, 3, 3, 2, 2, 1, 1};
    int c3[] = {-2, 1, 1, 2, 1, 1};                       /* adicional */
    int c4[] = {0, 0, 0, 0, 0, 0, 0, -3, 1, 1, 2, 2, 3, 3, 4, 4, 5, 4, 4, 3, 3, 2, 2, 1, 1};
    ejecutarCaso(1, c1, 14);   /* esperado: 5 km, 3 megatones */
    ejecutarCaso(2, c2, 17);   /* esperado: 4 km, 4 megatones */
    ejecutarCaso(3, c3, 6);    /* esperado: 1 km, 2 megatones */
    ejecutarCaso(4, c4, 25);   /* esperado: 8 km, 5 megatones */
    return 0;
}
