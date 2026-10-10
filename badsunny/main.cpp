#include <iostream>
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"
using namespace std;
#define N 20
void calcularFrecuenciayDuracion(int *frecuencias, int n, int& frecMax, int& dur) {
    Pila pila;
    ElementoPila elemento;
    construir(pila);
    int tiempo=1, area, intervalo, areaMaxima=0;
    while (tiempo<=n)
    {
        if (esPilaVacia(pila))
        {
            elemento.numero = tiempo;
            apilar(pila,elemento);
            tiempo++;
        }
        else
        {
            elemento = cima(pila);
            if (frecuencias[tiempo-1]>=frecuencias[elemento.numero-1])
            {
                elemento.numero = tiempo;
                apilar(pila,elemento);
                tiempo++;
            }
            else
            {
                //Aqui hay una desafinacion (bajada)
                elemento = desapilar(pila);
                intervalo = tiempo - elemento.numero;
                area = intervalo * frecuencias[elemento.numero-1];
                if (area>areaMaxima)
                {
                    frecMax = frecuencias[elemento.numero-1];
                    dur = intervalo;
                    areaMaxima = area;
                }
            }
        }
    }
}

int main() {
    int frecuencias[N] = {1,2,1,4,5,6,4,5,2,2,1};
    int n=11, frecMaxima, duracion;
    calcularFrecuenciayDuracion(frecuencias,n,frecMaxima,duracion);
    cout << "Frecuencia MÃ¡xima: " << frecMaxima << endl;
    cout << "DuraciÃ³n: " << duracion << endl;
    return 0;
}