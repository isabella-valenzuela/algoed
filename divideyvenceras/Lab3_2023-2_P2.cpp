/*
 * Laboratorio 3 (2023-2) - Pregunta 2
 * a) Filas de combos con un bocadito extra (busqueda binaria sobre pares).
 * b) Asiento con el bocadito mas caro que sus dos vecinos (pico de arreglo bitonico).
 */
#include <iostream>
using namespace std;

const int MAX_FILAS = 8;
const int MAX_BOC = 11;
const int MAX_ASIENTOS = 5;

/*
 * a) Divide y venceras sobre una fila de n = 11 bocaditos (una fila correcta tiene
 * 10, y la posicion 11 queda vacia con ' ').
 * Si la fila tiene el bocadito extra, antes de el los pares empiezan en posiciones
 * pares (0,2,4...) y son iguales; desde el error en adelante el par se desfasa.
 * Se busca binariamente la primera posicion par 'med' donde fila[med] != fila[med+1].
 * El bocadito en esa posicion es el extra. Complejidad O(log n) por fila.
 */
int buscarExtra(const char fila[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    if (med % 2 == 1) med--;               /* trabajar siempre con inicio de par */
    if (fila[med] == fila[med + 1])
        return buscarExtra(fila, med + 2, fin);   /* el error esta a la derecha */
    return buscarExtra(fila, ini, med);           /* el error esta en med o antes */
}

void filasConExtra(char combos[][MAX_BOC], int m, int n) {
    for (int i = 0; i < m; i++) {
        /* Si la ultima columna esta ocupada, la fila tiene un bocadito de mas: O(1) */
        if (combos[i][n - 1] != ' ') {
            int pos = buscarExtra(combos[i], 0, n - 1);
            cout << "La fila " << i + 1 << " tiene un " << combos[i][pos]
                 << " adicional." << endl;
        }
    }
}

/*
 * b) En cada fila los precios suben hasta un punto y luego bajan. Busqueda binaria
 * del pico: si precio[med] < precio[med+1] el pico esta a la derecha; si no, esta
 * en med o a la izquierda. Complejidad O(log n) por fila, O(m log n) en total.
 */
int buscarPico(const int fila[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    if (fila[med] < fila[med + 1]) return buscarPico(fila, med + 1, fin);
    return buscarPico(fila, ini, med);
}

void asientosMasCaros(int precios[][MAX_ASIENTOS], int m, int n) {
    for (int i = 0; i < m; i++) {
        int pos = buscarPico(precios[i], 0, n - 1);
        cout << "En la fila " << i + 1 << ", el pasajero del asiento " << pos + 1
             << " tiene el bocadito mas caro que sus 2 vecinos" << endl;
    }
}

int main() {
    /* Caso del enunciado (m = 8, n = 11). ' ' marca la posicion vacia */
    char combos[MAX_FILAS][MAX_BOC] = {
        {'O','O','C','C','A','A','E','E','R','R','R'},
        {'C','C','A','A','R','R','E','E','B','B',' '},
        {'R','R','E','E','C','C','F','F','A','A',' '},
        {'E','E','F','F','A','A','A','B','B','R','R'},
        {'C','C','C','A','A','R','R','O','O','E','E'},
        {'O','O','C','C','A','A','R','R','E','E',' '},
        {'A','A','F','F','R','R','E','E','O','O',' '},
        {'E','E','A','A','O','O','B','B','F','F',' '}
    };
    cout << "===== Parte a: caso del enunciado =====" << endl;
    filasConExtra(combos, 8, 11);

    /* Caso adicional: extra al inicio, al medio y sin errores */
    char combos2[3][MAX_BOC] = {
        {'F','F','F','C','C','A','A','R','R','E','E'},
        {'A','A','B','B','C','C','C','E','E','O','O'},
        {'R','R','O','O','B','B','A','A','E','E',' '}
    };
    cout << endl << "===== Parte a: caso adicional =====" << endl;
    filasConExtra(combos2, 3, 11);

    int precios[MAX_FILAS][MAX_ASIENTOS] = {
        {1, 2, 3, 2, 1},
        {2, 3, 2, 2, 1},
        {1, 2, 2, 5, 3},
        {2, 5, 3, 3, 1},
        {2, 2, 3, 2, 1},
        {1, 2, 3, 2, 1},
        {3, 5, 2, 1, 1},
        {2, 3, 2, 1, 1}
    };
    cout << endl << "===== Parte b: caso del enunciado =====" << endl;
    asientosMasCaros(precios, 8, 5);

    int precios2[3][MAX_ASIENTOS] = {
        {1, 3, 5, 4, 2},
        {4, 6, 9, 8, 7},
        {2, 9, 8, 7, 6}
    };
    cout << endl << "===== Parte b: caso adicional =====" << endl;
    asientosMasCaros(precios2, 3, 5);
    return 0;
}
