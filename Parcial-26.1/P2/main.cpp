#include <iostream>
using namespace std;
void contarPalabras(char *texto, char *palabra);
//void saltarPalabra(char *texto,int &contador);
void leerTexto(char *texto,char*palabra,int &cantPalabras,int &contador,int &indicePalabra);
int main() {

    char texto[300]{"negro negro negro negro negroxdxd"},palabraAContar[50]{};
    cin>>palabraAContar;
    contarPalabras(texto,palabraAContar);
    return 0;
}

void contarPalabras(char *texto, char *palabra) {
    int contador=0;
    int indicePalabra=0;
    int cantPalabras=0;
    leerTexto(texto,palabra,cantPalabras,contador,indicePalabra);
    cout<<cantPalabras<<endl;

}

void leerTexto(char *texto, char *palabra, int &cantPalabras, int &contador, int &indicePalabra) {
    char t = texto[contador];

    // CAMBIOS 1 y 2: un espacio o el fin del texto cierran la palabra actual
    if (t == '\0' or t == ' ') {
        // cuenta solo si no falló Y la palabra buscada terminó justo aquí
        if (indicePalabra >= 0 and palabra[indicePalabra] == '\0')
            cantPalabras++;
        if (t == '\0')
            return;               // caso base: antes de avanzar, para no pasarse del '\0'
        contador++;
        indicePalabra = 0;        // empieza una palabra nueva
        leerTexto(texto, palabra, cantPalabras, contador, indicePalabra);
        return;
    }

    // CAMBIO 3: es una letra normal
    if (indicePalabra >= 0 and palabra[indicePalabra] == t)
        indicePalabra++;          // sigue coincidiendo
    else
        indicePalabra = -1;       // ya falló: se ignora hasta el próximo espacio
    contador++;
    leerTexto(texto, palabra, cantPalabras, contador, indicePalabra);
}