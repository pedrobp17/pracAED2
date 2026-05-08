#include <iostream>
#include <cassert>
#include <string>
#include "dyv.hpp"

using namespace std;
int m = 3;
char C = 'c';

void testPrincipio() {
    string S = "ccaacdck";
    Solucion resultado = rachasSubstringDyV(S, 0, S.length() - 1, m, C);
    assert(resultado == Solucion(0,2)); 
}

void testFinal() {
    string S = "cgctbccacccc";
    Solucion resultado = rachasSubstringDyV(S, 0, S.length() - 1, m, C);
    assert(resultado == Solucion(9, 3)); 
}

void testMitad() {
    string S = "caabaccccopycc";
    Solucion resultado = rachasSubstringDyV(S, 0, S.length() - 1, m, C);
    assert(resultado == Solucion(6, 3));
}

//nuestro codigo siempre se queda con la solucion mas alta en caso de empate

void testNulo() {
    string S = "abbde";
    Solucion resultado = rachasSubstringDyV(S, 0, S.length() - 1, m, C);
    assert(resultado == Solucion(2,0)); 
}

void testConstante() {
    string S = "ccccc";
    Solucion resultado = rachasSubstringDyV(S, 0, S.length() - 1, m, C);
    assert(resultado == Solucion(2,3)); 
}

int main() {
    testPrincipio();
    testMitad();
    testFinal();
    testNulo();
    testConstante();
    cout << "Todos los tests pasaron!" << endl;
    return 0;
}