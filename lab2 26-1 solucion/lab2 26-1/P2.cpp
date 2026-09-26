// g++ -g -o algoed .\test.cpp
#include <bits/stdc++.h>
using namespace std;

#define N 10

// recorre la columna 0 en busca de candidatos, es O(n)
int buscarCandidato(int regGenetico[N][N], int i, int prev, bool can_be_zero) {
    // Caso base: se llega al final de la columna
    if (i>=N) return prev!=-1 ? prev : (can_be_zero ? 0 : -1); // si hubieron ceros en esta columna, se descarta al canario 0

    int v_candidato = regGenetico[i][0];

    // este canario recibio aporte genetico, descartado
    if (v_candidato != 0)
        return buscarCandidato(regGenetico, i+1, prev, can_be_zero);

    // no hay un candidato previo, nos llevamos este canario por default
    if (prev==-1)
        return buscarCandidato(regGenetico, i+1, i, false);
    

    // si este canario es candidato, compite por el puesto con el previo
    // el canario ancestral debio darle aporte genetico al resto pero no haber recibido de ninguno
    if (regGenetico[prev][i]!=0 && regGenetico[i][prev]==0)
        return buscarCandidato(regGenetico, i+1, i, false);
    if (regGenetico[prev][i]==0 && regGenetico[i][prev]!=0)
        return buscarCandidato(regGenetico, i+1, prev, false);
    
    // ninguno cumple con los requisitos, ambos quedan descartados
    return buscarCandidato(regGenetico, i+1, -1, false);
}

// evalua si es el canario ancestral viendo si da aporte genetico a todos pero no recibe de ninguno, es O(2n)
int evaluarCandidato(int regGenetico[N][N], int candidato, char eje=0, int i=0) {
    // Caso base: se termino de evaluar el eje horizontal o vertical
    if (i>=N) return eje=='h' ? 0 : 1;

    // solo se ejecuta la primera vez que se llama a la funcion
    if (eje==0) {
        int fila = 0 + evaluarCandidato(regGenetico, candidato, 'h'),
            columna = 1 * evaluarCandidato(regGenetico, candidato, 'v');

        return (fila==100 && columna!=0) ? candidato : -1;
    }

    // suma horizontal
    if (eje=='h')
        return regGenetico[candidato][i] + evaluarCandidato(regGenetico, candidato, 'h', i+1);
    
    // producto vertical
    return regGenetico[i][candidato] * evaluarCandidato(regGenetico, candidato, 'v', i+1);
}

int buscarCanarioAncestral(int regGenetico[N][N]) { // O(n + 2n) = O(3n) ~ O(n) cuando n->∞
    int candidato = buscarCandidato(regGenetico, 0, -1, true); // O(n)

    return evaluarCandidato(regGenetico, candidato); // O(2n)
}

int main() {
    int regGenetico[N][N] = {
        {100, 0, 50, 40, 30, 20, 30, 0, 80, 0},
        {50, 100, 0, 40, 30, 20, 20, 0, 10, 25},
        {80, 30, 100, 40, 30, 0, 30, 20, 10, 60},
        {50, 0, 0, 100, 30, 0, 50, 30, 30, 90},
        {50, 10, 10, 10, 100, 0, 10, 50, 10, 50},
        {20, 0, 0, 0, 0, 100, 90, 20, 40, 20},
        {0, 0, 0, 0, 0, 0, 100, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 50, 100, 50, 20},
        {20, 0, 0, 40, 0, 0, 90, 0, 100, 10},
        {0, 10, 0, 0, 0, 0, 10, 0, 60, 100},
    },
    canarioAncestral = buscarCanarioAncestral(regGenetico);


    cout << "Canario ancestral: ";
    (canarioAncestral!=-1 ? cout << canarioAncestral : cout << "no halladoxdx") << endl;

    return 0;
}