#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Biblioteca/Funciones.h"
int main() {
    int numJugadores=0;
    char apellido[50];
    char posicion[50];
    struct Jugador jugador{};
    struct Lista listaDeJugadores;
    inicializarLista(listaDeJugadores);
    cout<<"La lista esta vacia: "<< esListaVacia(listaDeJugadores)<<endl;
    //Insercion de los 6 jugadores
    while (numJugadores<12) {
        cin>>jugador.num;
        if (jugador.num==-1) break;
        cin>>apellido>>posicion;
        strcpy(jugador.apellido,apellido);
        strcpy(jugador.posicion,posicion);
        insertarJugador(listaDeJugadores,jugador);
        numJugadores++;
    }

    //jugador.num=7;
    //struct Nodo *aux2=listaDeJugadores.cabeza;

    // while (aux2!=nullptr) {
    //     cout<<aux2->jugador.apellido<<','<<aux2->jugador.posicion<<','<<aux2->jugador.num<<endl;
    //     aux2=aux2->siguiente;
    // }

    //
    // jugador.num=1;
    // strcpy(jugador.apellido,"Ramirez");
    // strcpy(jugador.posicion,"Portero");
    // insertarJugador(listaDeJugadores,jugador);
    // //
    // jugador.num=5;
    // strcpy(jugador.apellido,"Perez");
    // strcpy(jugador.posicion,"Defensa");
    // insertarJugador(listaDeJugadores,jugador);
    // //
    // jugador.num=8;
    // strcpy(jugador.apellido,"Torres");
    // strcpy(jugador.posicion,"Mediocampo");
    // insertarJugador(listaDeJugadores,jugador);
    // //
    // jugador.num=9;
    // strcpy(jugador.apellido,"Lopez");
    // strcpy(jugador.posicion,"Delantero");
    // insertarJugador(listaDeJugadores,jugador);
    // //
    // jugador.num=3;
    // strcpy(jugador.apellido,"Gomez");
    // strcpy(jugador.posicion,"Defensa");
    // insertarJugador(listaDeJugadores,jugador);
    //
    // struct Nodo *aux=listaDeJugadores.cabeza;
    cout<<listaDeJugadores.tamaño<<endl;
    reordenaFormacion(listaDeJugadores,"Portero");
    reordenaFormacion(listaDeJugadores,"Defensa");
    reordenaFormacion(listaDeJugadores,"Mediocampo");
    reordenaFormacion(listaDeJugadores,"Delantero");


    struct Nodo *aux2=listaDeJugadores.cabeza;
    while (aux2!=nullptr) {
        cout<<aux2->jugador.num<<','<<aux2->jugador.apellido<<','<<aux2->jugador.posicion<<endl;
        aux2=aux2->siguiente;
    }
    cout<<listaDeJugadores.tamaño<<endl;
    return 0;
}