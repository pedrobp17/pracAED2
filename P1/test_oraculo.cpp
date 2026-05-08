#include <iostream>
#include "dyv.hpp"
#include <cassert>
#include <random>

using namespace std;


string generarSecuenciaAleatoria(int longitud, char minimo, char maximo, unsigned int semilla) {
    string secuencia(longitud, ' ');

    mt19937 gen(semilla);
    uniform_int_distribution<> dist(minimo, maximo);

    for (int i = 0; i < longitud; ++i) {
        secuencia[i] = (char)dist(gen);
    }

    cout<<"Secuencia generada: "<<secuencia<<endl;

    return secuencia;
}
int main() {
    unsigned int semilla = 42;
    char minimo = 'a';
    char maximo = 'z';
    char C = 'c';
    int m;
    
    vector<int> longitudes = {5, 10, 20, 50, 100, 1000};

    for (size_t i = 0; i < longitudes.size(); ++i) {
        int longitud = longitudes[i];
        m = min(12, longitud/3);
        string secuencia = generarSecuenciaAleatoria(longitud, minimo, maximo, semilla + i);
        Solucion dyvOutput = rachasSubstringDyV(secuencia, 0, secuencia.length() - 1, m, C);
        Solucion resultadoIterativo = rachasSubstringIterativo(secuencia, secuencia.length(), m, C);
        
        cout << "Longitud de la secuencia: " << longitud << endl;
        cout << "Resultado DyV: " << dyvOutput << endl;
        cout << "Resultado Iterativo: " << resultadoIterativo << endl;
        assert(dyvOutput == resultadoIterativo);
    }

    return 0;
}