#ifndef AVANCE_RAPIDO_H
#define AVANCE_RAPIDO_H

#include <vector>

using namespace std;

struct Nodo {
    int i, j, beneficio;
    Nodo(int i = 0, int j = 0, int beneficio = 0) : i(i), j(j), beneficio(beneficio) {}
};

struct Solucion {
    int resultado;
    std::vector<int> elegidos;
    Solucion(int resultado = 0, vector<int> elegidos = {}) : resultado(resultado), elegidos(elegidos) {}
};


Solucion avance_rapido(int n, int m, const vector<vector<int>>& distancias);

#endif