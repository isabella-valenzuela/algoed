#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Biblioteca/Funciones.h"
int main() {
    int cantPares=0,cantImpares=0;
    struct Lista lista;
    struct Cuadriga cuadriga {};
    crearLista(lista);
    bool estaVacia=lista.cabeza==nullptr;
    cout<<"La lista esta vacia :"<<estaVacia<<endl;
    //
    cuadriga.id=17;
    strcpy(cuadriga.nombre,"Messala");
    strcpy(cuadriga.equipo,"Rojo");
    insertarCuadrigaAlFinal(lista,cuadriga);
    //
    cuadriga.id=4;
    strcpy(cuadriga.nombre,"Ben-hur");
    strcpy(cuadriga.equipo,"Azul");
    insertarCuadrigaAlFinal(lista,cuadriga);
    //
    cuadriga.id=12;
    strcpy(cuadriga.nombre,"Artax");
    strcpy(cuadriga.equipo,"Verde");
    insertarCuadrigaAlFinal(lista,cuadriga);
    //
    cuadriga.id=7;
    strcpy(cuadriga.nombre,"Drusus");
    strcpy(cuadriga.equipo,"Negro");
    insertarCuadrigaAlFinal(lista,cuadriga);
    //

    struct Nodo *aux=lista.cabeza;
    while(aux!=nullptr) {
        cout<<"Cuadriga: "<<aux->cuadrigas.id<<','<<aux->cuadrigas.equipo<<','<<aux->cuadrigas.nombre<<endl;
        aux=aux->siguiente;
    }
    contarParesEImpares(lista,cantPares,cantImpares);
    cout<<"Cantidad de ID's pares en la lista: "<<cantPares<<endl;
    cout<<"Cantidad de ID's impares en la lista: "<<cantImpares<<endl;

    ordenarLista(lista,cantPares,cantImpares);

    struct Nodo *aux1=lista.cabeza;
    while(aux1!=nullptr) {
        cout<<"Cuadriga: "<<aux1->cuadrigas.id<<','<<aux1->cuadrigas.equipo<<','<<aux1->cuadrigas.nombre<<endl;
        aux1=aux1->siguiente;
    }

    return 0;
}