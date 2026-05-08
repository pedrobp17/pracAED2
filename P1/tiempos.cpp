#include <iostream>
#include <cassert>
#include <math.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "dyv.hpp"

using namespace std;

string generarPeorCaso(int n, char C){
    return string(n, C);
}
string generarMejorCaso( int n, char C){
    char otro = ( C == 'a' ) ? 'b' : 'a';
    return string(n, otro);
}

//dejo esto porque lo pide la memoria pero realmente va a dar lo mismo
//ya que nuestros algoritmos no tienen peores y mejores casos

double medirTiempo(const string& secuencia) {
    //m debe ser constante para que el análisis cuadre con el teórico 
    const int m = 100;
    char C = 'c';

    auto start = chrono::high_resolution_clock::now();

    Solucion resultado = rachasSubstringDyV(secuencia, 0, secuencia.length() - 1, m, C);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duracion = end - start;
    return duracion.count();
}

double mediana( vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;

    sort(v.begin(), v.end());

    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    vector<int> longitudes;
    char C = 'c';
    for (int i = 0; i <= 10; i += 1) {
        longitudes.push_back(1000 * pow(2, i));
    }
    std::ofstream csv("resultados.csv");
    csv << "Longitud,MejorCaso,PeorCaso\n";

    for (int longitud : longitudes) {
        auto mejorCaso = generarMejorCaso(longitud, C);
        vector<double> mejoresCasos;
        for (int j = 0; j < 10; j += 1){
            auto mejorTiempo = medirTiempo(mejorCaso);
            mejoresCasos.push_back(mejorTiempo);
        }
        auto medianaMejorTiempo = mediana(mejoresCasos);
        

        auto peorCaso = generarPeorCaso(longitud, C);
        vector<double> peoresCasos;
        for (int j = 0; j < 10; j += 1){
            auto peorTiempo = medirTiempo(peorCaso);
            peoresCasos.push_back(peorTiempo);
        }
        auto medianaPeorTiempo = mediana(peoresCasos);
        
        csv << longitud << "," << medianaMejorTiempo << "," << medianaPeorTiempo << "\n";
    }

    csv.close();
    return 0;
}