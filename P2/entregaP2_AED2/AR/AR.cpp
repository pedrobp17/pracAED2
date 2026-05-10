#include <iostream>
#include <vector>
#include <algorithm>
#include "AR.h"

using namespace std;

//funcion para comparar Nodos mas facilmente
static bool comparar(const Nodo& nodo1, const Nodo& nodo2) {
    return nodo1.beneficio > nodo2.beneficio;
}

//funcion auxiliar para sumar todas las distancias que dependen de la ciudad: indice
//ejemplo:
// Se elige la cuidad 2 y ya tenemos seleccionadas 1, 3
// realiza beneficio = d(2,1) + d(1,2) + d(2,3) + d(3,2)
static void actualizar_beneficio(vector<int>& v_aux, int& beneficio, int indice, const vector<vector<int>>& distancias){
    int size = v_aux.size();
    for( int i = 0; i < size; i++){
            beneficio += distancias[indice][v_aux[i]];    
            beneficio += distancias[v_aux[i]][indice];    
    }
    v_aux.push_back(indice);
}
         
//funcion principal
Solucion avance_rapido(int n, int m, const vector<vector<int>>& distancias) {
    
    //matriz auxiliar
    //supongamos distancias = { {0, 2, 3, 4}, {2, 0, 3, 4}, {2, 3, 0, 4}, {2, 3, 4, 0}}
    //entonces poblacion = 
    //{ {(i=j=0, b=0), (i=0, j=1, b=4), (i=0, j=2, b=5), (i=0, j=3, b=6)},
    //{(i=j=1, b=0), (i=1, j=2, b=6), (i=1, j=3, b=7)},
    //{ (i=j=2, b=0), (i=2, j=3, b=8)},
    //{(i=j=3, b=0)}}
    vector<vector<Nodo>> poblacion(n, vector<Nodo>(n));

    //inicializacion matriz auxiliar
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

    //ordenamos todas las filas(i) para tener en primera posicion siempre la ciudad con mayor distancia de i
    for (int i = 0; i < n; i++) {
        sort(poblacion[i].begin(), poblacion[i].end(), comparar);
    }

    //vector que obtendra todas las ciudades elegidas
    vector<int> elegidos(n, 0);
    //vector auxiliar
    vector<int> aux;
    vector<int> indices(n, 0);
    //tamaño de la poblacion que queremos elegir
    int subpoblacion = m;
    //beneficio que producen todas las cuidades elegidas
    int beneficio = 0;

    //mientras queden ciudades por elegir realizamos el bucle
    while (subpoblacion > 0) {
        //variables auxiliares
        int max_beneficio = -1;
        int fila = -1;

        //recorremos la matriz solo visitando la columna que tiene la ciudad mas alejada a la actual(i), es decir, la marcada por indices
        for (int i = 0; i < n; i++) {
            //si no hemos llegado al final de la fila i
            if (indices[i] < n - i) { 
                //comprobacion de maximalidad
                if (poblacion[i][indices[i]].beneficio > max_beneficio) {
                    //actualizacion de variables
                    max_beneficio = poblacion[i][indices[i]].beneficio;
                    fila = i;
                }
            }
        }

        Nodo& actual = poblacion[fila][indices[fila]];
        
        //comprobamos si la cuidad i o j ya estan elegidas y sino se suman sus beneficios relacionados
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
        
        //aumentamos el indice de por donde empezar en la fila i
        indices[fila]++;
    }

    return Solucion(beneficio, elegidos);
}