#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Nodo {
    int i;
    int j;
    int beneficio;
    Nodo(int i, int j, int beneficio) : i(i), j(j), beneficio(beneficio) {}
    Nodo() : i(0), j(0), beneficio(0) {}
};

struct Solucion {
    int resultado;
    vector<int> elegidos;
    Solucion(int resultado, vector<int> elegidos) : resultado(resultado), elegidos(elegidos) {}
    Solucion() : resultado(0), elegidos() {}
};

vector<vector<Nodo>> poblacion;
vector<vector<int>> distancias;

bool comparar(const Nodo& nodo1, const Nodo& nodo2) {
    return nodo1.beneficio > nodo2.beneficio;
}

void leerMatriz(int n) {
    poblacion.assign(n, vector<Nodo>(n, Nodo()));
    distancias.assign(n, vector<int>(n));
    int beneficio_actual;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> beneficio_actual;
            distancias[i][j]= beneficio_actual;
            if( j >= i ){
                poblacion[i][j] = Nodo(i, j, beneficio_actual);
            }else{
                poblacion[j][i].beneficio += beneficio_actual;
            }

        }
    }
}

void actualizar_beneficio(vector<int>& vector, int& beneficio, int indice){
    int size = vector.size();
    for( int i = 0; i < size; i++){
            beneficio += distancias[indice][vector[i]];    
            beneficio += distancias[vector[i]][indice];    
    }
    vector.push_back(indice);
}
            
Solucion avance_rapido(int n, int m) {
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
            actualizar_beneficio(aux, beneficio, actual.i);
            subpoblacion--;
        }
        
        if (subpoblacion > 0 && elegidos[actual.j] < 1) {
            elegidos[actual.j] = 1;
            actualizar_beneficio(aux, beneficio, actual.j);
            subpoblacion--;
        }

        indices[fila]++;
    }

    return Solucion(beneficio, elegidos);
}

int main() {
    int casos;
    if (!(cin >> casos)) return 0;
    
    for (int i = 0; i < casos; i++) {
        int n, m;
        if (!(cin >> n >> m)) break;
        
        leerMatriz(n);
        Solucion solucion = avance_rapido(n, m);
        cout << solucion.resultado << endl;
        for (int j = 0; j < n; j++) {
            cout << solucion.elegidos[j] << " ";
        }
        cout << endl;
    }
    return 0;
}