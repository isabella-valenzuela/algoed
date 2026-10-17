#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#define MAX 100

void extrafiliacion(int cantFilas, int cantColumnas, int maxAncho, int maxAlto, int umbral, int trafico[MAX][MAX]) {
    int suma = 0, bloquesSospechosos = 0;

    for (int columnaInicial = 0; columnaInicial < cantColumnas; columnaInicial++) {
        for (int columnaFinal = columnaInicial; columnaFinal < cantColumnas; columnaFinal++) {
            for (int filaInicial = 0; filaInicial < cantFilas; filaInicial++) {
                for (int filaFinal = filaInicial; filaFinal < cantFilas; filaFinal++) {
                    int alto = filaFinal - filaInicial +  1 ;
                    int ancho =   columnaFinal -columnaInicial + 1;
                    if (alto<= maxAlto and ancho <= maxAncho) {
                        for (int n = columnaInicial; n <= columnaFinal; n++) {
                            for (int m = filaInicial; m <= filaFinal; m++) {
                                suma += trafico[m][n];
                            }
                        }
                        if (suma > umbral) {
                            bloquesSospechosos++;
                            cout << "bloque sospechoso " << bloquesSospechosos << endl;
                            cout << "fila inicial: " << filaInicial << endl;
                            cout << "columna inicial: " << columnaInicial << endl;
                            cout << "fila final: " << filaFinal << endl;
                            cout <<"columna final: " << columnaFinal << endl;
                            cout << "suma: " << suma << endl;
                            cout << "---------------------------------"<<endl;
                        }
                        suma = 0;

                    }




                }
            }
        }
    }
    if (bloquesSospechosos == 0) cout << "no se encontraron bloques sospechosos" << endl;
}

int main() {
    int cantFilas=4, cantColumnas=4, maxAncho=2, maxAlto=2, umbral=50;

    int trafico[MAX][MAX] = {{1,2,3,4}, {5,20,1,2}, {3,25,4,1}, {1,2,30,3}};

    cout << "Matriz evaluada:" << endl;
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++)
            cout << trafico[i][j] << " ";
        cout << endl;
    }
    cout << "Altura maxima del bloque : " << maxAlto << endl;
    cout << "Ancho maximo del bloque : " << maxAncho << endl;
    cout << "Umbral sospechoso: " << umbral << endl;

extrafiliacion(cantFilas, cantColumnas, maxAncho, maxAlto, umbral, trafico);
    cantFilas=3, cantColumnas=3, maxAncho=2, maxAlto=2, umbral=50;

    int trafico2[MAX][MAX] = {{1,2,3}, {4,5,6}, {7,8,9}};
    cout << "Matriz evaluada:" << endl;
    for (int i = 0; i < cantFilas; i++) {
        for (int j = 0; j < cantColumnas; j++)
            cout << trafico2[i][j] << " ";
        cout << endl;
    }
    cout << "Altura maxima del bloque : " << maxAlto << endl;
    cout << "Ancho maximo del bloque : " << maxAncho << endl;
    cout << "Umbral sospechoso: " << umbral << endl;
    extrafiliacion(cantFilas, cantColumnas, maxAncho, maxAlto, umbral, trafico2);

    return 0;
}
