/*
 * Laboratorio 3 (2023-2) - Pregunta 1
 * Splinter elige la pizzeria con menos horas de pico (horas consecutivas con la
 * produccion maxima). Horario: 2pm a 11pm (10 horas).
 */
#include <iostream>
using namespace std;

const int MAX_EMPRESAS = 10;
const int HORAS = 10;   /* 2pm .. 11pm */

/* a) Estructura */
struct Empresa {
    int pedidos[HORAS];
    int maximo;        /* resultado de la parte b */
    int horasPico;     /* resultado de la parte c */
    int inicioPico;    /* indice de la hora donde empieza el pico */
};

int maximoEntre(int a, int b) { return a > b ? a : b; }

/*
 * b) Maxima produccion de una empresa con divide y venceras.
 * Se divide el arreglo de horas en dos mitades, se obtiene recursivamente el
 * maximo de cada mitad y se devuelve el mayor de ambos. La profundidad de la
 * recursion es log(m).
 */
int maximaProduccion(const int pedidos[], int ini, int fin) {
    if (ini == fin) return pedidos[ini];
    int med = (ini + fin) / 2;
    int izq = maximaProduccion(pedidos, ini, med);
    int der = maximaProduccion(pedidos, med + 1, fin);
    return maximoEntre(izq, der);
}

void calcularMaximos(Empresa empresas[], int n) {
    for (int i = 0; i < n; i++)
        empresas[i].maximo = maximaProduccion(empresas[i].pedidos, 0, HORAS - 1);
}

/*
 * c) Mayor bloque de horas consecutivas con produccion igual al maximo.
 * Divide y venceras (como subarreglo maximo): el mejor bloque esta en la mitad
 * izquierda, en la derecha o cruza el centro. El bloque que cruza se calcula
 * extendiendo desde med hacia la izquierda y desde med+1 hacia la derecha mientras
 * el valor sea igual al maximo. Devuelve la longitud y deja en 'inicio' donde empieza.
 */
int bloqueCruzado(const int pedidos[], int ini, int med, int fin, int maximo, int &inicio) {
    int i = med, j = med + 1;
    while (i >= ini && pedidos[i] == maximo) i--;
    while (j <= fin && pedidos[j] == maximo) j++;
    if (i == med || j == med + 1) return 0;   /* no cruza realmente el centro */
    inicio = i + 1;
    return j - i - 1;
}

int horasDePico(const int pedidos[], int ini, int fin, int maximo, int &inicio) {
    if (ini == fin) {
        inicio = ini;
        return pedidos[ini] == maximo ? 1 : 0;
    }
    int med = (ini + fin) / 2;
    int iniIzq, iniDer, iniCru = -1;
    int izq = horasDePico(pedidos, ini, med, maximo, iniIzq);
    int der = horasDePico(pedidos, med + 1, fin, maximo, iniDer);
    int cru = bloqueCruzado(pedidos, ini, med, fin, maximo, iniCru);
    if (izq >= der && izq >= cru) { inicio = iniIzq; return izq; }
    if (cru >= der) { inicio = iniCru; return cru; }
    inicio = iniDer;
    return der;
}

/*
 * c) Eleccion de la empresa: tambien por divide y venceras sobre el arreglo de
 * empresas. Devuelve el indice de la empresa con menos horas de pico (en empate,
 * la de menor indice).
 */
int elegirEmpresa(const Empresa empresas[], int ini, int fin) {
    if (ini == fin) return ini;
    int med = (ini + fin) / 2;
    int izq = elegirEmpresa(empresas, ini, med);
    int der = elegirEmpresa(empresas, med + 1, fin);
    return empresas[der].horasPico < empresas[izq].horasPico ? der : izq;
}

int horaReal(int indice) { return 2 + indice; }   /* indice 0 -> 2pm */

void ejecutarCaso(int numero, Empresa empresas[], int n) {
    cout << "===== Caso " << numero << " =====" << endl;
    calcularMaximos(empresas, n);
    for (int i = 0; i < n; i++) {
        empresas[i].horasPico = horasDePico(empresas[i].pedidos, 0, HORAS - 1,
                                            empresas[i].maximo, empresas[i].inicioPico);
        int ini = empresas[i].inicioPico;
        cout << "Empresa " << i + 1 << ": maximo = " << empresas[i].maximo
             << ", horas de pico = " << empresas[i].horasPico
             << " (" << horaReal(ini) << " a "
             << horaReal(ini + empresas[i].horasPico - 1) << "pm)" << endl;
    }
    int elegida = elegirEmpresa(empresas, 0, n - 1);
    int ini = empresas[elegida].inicioPico;
    cout << "Se debe comprar a la Empresa " << elegida + 1 << " con "
         << empresas[elegida].horasPico << " horas de pico ("
         << horaReal(ini) << " a " << horaReal(ini + empresas[elegida].horasPico - 1)
         << "pm)" << endl << endl;
}

int main() {
    /* Caso del enunciado */
    Empresa caso1[MAX_EMPRESAS] = {
        {{15, 12, 10, 17, 15, 18, 18, 18, 12, 16}, 0, 0, 0},
        {{14, 17, 17, 17, 17, 12, 14, 14, 12, 12}, 0, 0, 0},
        {{16, 18, 20, 20, 15, 18, 16, 18, 18, 16}, 0, 0, 0}
    };
    ejecutarCaso(1, caso1, 3);

    /* Caso con picos al inicio y al final del horario */
    Empresa caso2[MAX_EMPRESAS] = {
        {{30, 30, 30, 10, 10, 10, 10, 10, 10, 10}, 0, 0, 0},
        {{5, 6, 7, 8, 9, 10, 11, 12, 25, 25}, 0, 0, 0},
        {{9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, 0, 0, 0},
        {{1, 40, 2, 40, 40, 3, 40, 4, 5, 6}, 0, 0, 0}
    };
    ejecutarCaso(2, caso2, 4);
    return 0;
}
