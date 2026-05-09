#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "AR.h"

using namespace std;

struct CasoPrueba {
    int n;
    int m;
    vector<vector<int>> distancias;
};

// Peor caso: Matriz llena de valores altos (maximiza cálculos de beneficios)
CasoPrueba generarPeorCasoAR(int n) {
    CasoPrueba caso;
    caso.n = n;
    caso.m = n / 2;
    caso.distancias = vector<vector<int>>(n, vector<int>(n, 100));
    return caso;
}

CasoPrueba generarPeorCasoARreal(int n) {
    CasoPrueba caso;
    caso.n = n;
    caso.m = n / 2;
    caso.distancias = vector<vector<int>>(n, vector<int>(n, 0));
    int m = caso.m;
    int base = n * n + 1;  // garantiza distancias positivas dentro del clique
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int prioridad = base - j * n - i;
            caso.distancias[i][j] = prioridad;
            caso.distancias[j][i] = prioridad;  // matriz simétrica
        }
    }
    return caso;
}

// Mejor caso: Matriz vacía o con ceros (mínimo esfuerzo de actualización)
CasoPrueba generarMejorCasoAR(int n) {
    CasoPrueba caso;
    caso.n = n;
    caso.m = n / 2;
    caso.distancias = vector<vector<int>>(n, vector<int>(n, 0));
    return caso;
}

double medirTiempoAR(int n, int m, const vector<vector<int>>& distancias) {
    auto start = chrono::high_resolution_clock::now();
    avance_rapido(n, m, distancias);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = end - start;
    return duracion.count();
}

double calcularMediana(vector<double> v) {
    if (v.empty()) return 0.0;
    sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    vector<int> longitudes;
    for (int i = 0; i <= 4; i++) { 
        longitudes.push_back(200 * pow(2, i));
    }

    ofstream csv("resultados_AR.csv");
    // IMPORTANTE: Ahora la cabecera incluye MejorCaso
    csv << "Longitud,PeorCaso,MejorCaso\n";

    for (int n : longitudes) {
        cout << "Procesando n = " << n << "..." << endl;
        
        // Medir Peor Caso
        CasoPrueba peor = generarPeorCasoARreal(n);
        vector<double> muestrasPeor;
        for (int j = 0; j < 5; j++) muestrasPeor.push_back(medirTiempoAR(peor.n, peor.m, peor.distancias));
        double tiempoPeor = calcularMediana(muestrasPeor);

        // Medir Mejor Caso
        CasoPrueba mejor = generarMejorCasoAR(n);
        vector<double> muestrasMejor;
        for (int j = 0; j < 5; j++) muestrasMejor.push_back(medirTiempoAR(mejor.n, mejor.m, mejor.distancias));
        double tiempoMejor = calcularMediana(muestrasMejor);
        
        // Escribir ambos en el CSV
        csv << n << "," << tiempoPeor << "," << tiempoMejor << "\n";
    }

    csv.close();
    cout << "Fichero resultados_AR.csv generado con éxito." << endl;
    return 0;
}