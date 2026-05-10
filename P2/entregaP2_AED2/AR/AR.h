#ifndef AVANCE_RAPIDO_H
#define AVANCE_RAPIDO_H

#include <vector>

using namespace std;

//estructura que usaremos para crear nuestra matriz guia
struct Nodo {
    int i, j, beneficio; // (i,j) representa la posicion de la matriz y beneficio = d(i,j) != d(j,i)
    Nodo(int i = 0, int j = 0, int beneficio = 0) : i(i), j(j), beneficio(beneficio) {}
};

//estructura que devuelve la solucion
struct Solucion {
    int resultado; //valor total de la suma de todas las ciudades elegidas
    std::vector<int> elegidos; //vector con las ciudades elegidas
    Solucion(int resultado = 0, vector<int> elegidos = {}) : resultado(resultado), elegidos(elegidos) {} //constructor
};


Solucion avance_rapido(int n, int m, const vector<vector<int>>& distancias); //funcion que realiza el avance rapido

#endif