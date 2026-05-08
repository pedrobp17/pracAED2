#include <iostream>
#include <cassert>
#include <vector>
#include "AR.h"

vector<vector<int>> crearMatrizTest(int n, int valor_base) {
    return vector<vector<int>>(n, vector<int>(n, valor_base));
}

void testBasico() {
    int n = 4;
    int m = 2;

    vector<vector<int>> dist = crearMatrizTest(n, 10); 
    
    Solucion sol = avance_rapido(n, m, dist);

    int cont = 0;
    for(int e : sol.elegidos) if(e == 1) cont++;
    
    assert(cont == m);
    assert(sol.resultado > 0);
}

void testConjVacio() {
    int n = 4;
    int m = 0;
    vector<vector<int>> dist = crearMatrizTest(n, 10);
    
    Solucion sol = avance_rapido(n, m, dist);
    
    assert(sol.resultado == 0);
    for(int e : sol.elegidos) assert(e == 0);
}

void testTodosEntran() {
    int n = 4;
    int m = 4; 
    vector<vector<int>> dist = {
        {0, 5, 0, 0},
        {5, 0, 0, 0},
        {0, 0, 0, 5},
        {0, 0, 5, 0}
    };
    
    Solucion sol = avance_rapido(n, m, dist);
    
    assert(sol.resultado == 20); 
    for(int e : sol.elegidos) assert(e == 1);
}

int main() {
    testBasico();
    testConjVacio();
    testTodosEntran();
    cout << "Todos los tests de Avance Rapido pasaron con exito!" << endl;
    return 0;
}