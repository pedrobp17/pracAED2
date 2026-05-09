#include <iostream>
#include <vector>
#include <algorithm>
#include "AR.h"

using namespace std;

static bool comparar(const Nodo& nodo1, const Nodo& nodo2) {
    return nodo1.beneficio > nodo2.beneficio;
}

static void actualizar_beneficio(vector<int>& v_aux, int& beneficio, int indice, const vector<vector<int>>& distancias){
    int size = v_aux.size();
    for( int i = 0; i < size; i++){
            beneficio += distancias[indice][v_aux[i]];    
            beneficio += distancias[v_aux[i]][indice];    
    }
    v_aux.push_back(indice);
}
            
Solucion avance_rapido(int n, int m, const vector<vector<int>>& distancias) {
    vector<vector<Nodo>> poblacion(n, vector<Nodo>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int valor = distancias[i][j];
            if (j >= i) {
                poblacion[i][j] = Nodo(i, j, valor);
            } else {
                poblacion[j][i].beneficio += valor;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        sort(poblacion[i].begin(), poblacion[i].end(), comparar);
    }

    vector<int> elegidos(n, 0);
    vector<int> aux;
    vector<int> indices(n, 0);
    int subpoblacion = m;
    int beneficio = 0;

    while (subpoblacion > 0) {
        int max_beneficio = -1;
        int fila = -1;

        for (int i = 0; i < n; i++) {
            if (indices[i] < n - i) { 
                if (poblacion[i][indices[i]].beneficio > max_beneficio) {
                    max_beneficio = poblacion[i][indices[i]].beneficio;
                    fila = i;
                }
            }
        }

        Nodo& actual = poblacion[fila][indices[fila]];
        
        if (elegidos[actual.i] < 1) {
            elegidos[actual.i] = 1;
            actualizar_beneficio(aux, beneficio, actual.i, distancias);
            subpoblacion--;
        }
        
        if (subpoblacion > 0 && elegidos[actual.j] < 1) {
            elegidos[actual.j] = 1;
            actualizar_beneficio(aux, beneficio, actual.j, distancias);
            subpoblacion--;
        }

        indices[fila]++;
    }

    return Solucion(beneficio, elegidos);
}