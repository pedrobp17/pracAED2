#include <iostream>
#include <vector>
#include <cassert>
#include "bt.h"

using namespace std; // Para evitar poner std:: en vector y cout

void testMooshak1() {
    int nt = 5;
    int nw = 5;
    vector<vector<int>> B = {{0, 2, 0, 0, 0},
                             {0, 0, 0, 2, 0},
                             {0, 0, 1, 0, 0}, 
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 1}};
    vector<int> C = {1, 2, 2, 2, 1};
    
    auto resultado1 = bt_poda(B, C, nt, nw);    
    assert(resultado1 == 0); 
    
    auto resultado2 = bt_sin_poda(B, C, nt, nw);   
    assert(resultado2 == 0); 
}

void testMooshak2() {
    int nt = 8;
    int nw = 6;
    // CORREGIDO: Se añaden comas entre los números
    vector<vector<int>> B = {
        {4, 0, 0, 0, 0, 0}, 
        {4, 5, 0, 0, 0, 0},
        {0, 4, 0, 0, 0, 0}, 
        {2, 0, 0, 3, 2, 0},
        {0, 0, 0, 4, 2, 0}, 
        {5, 5, 2, 0, 2, 3}, 
        {0, 0, 2, 2, 2, 2},
        {0, 2, 0, 0, 2, 5}
    };
    vector<int> C = {1, 1, 1, 1, 1, 1, 1, 1};
    
    auto resultado = bt_poda(B, C, nt, nw);    
    assert(resultado == 23); 
    
    // CORREGIDO: Se quita 'auto' y 'double' para no redefinir variables
    resultado = bt_sin_poda(B, C, nt, nw);  
    assert(resultado == 23); 
}

void testMooshak3() {
    int nt = 6;
    int nw = 8;
    vector<vector<int>> B = {
        {4, 0, 0, 0, 0, 0, 4, 5}, 
        {0, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 2, 0, 0, 3, 2, 0}, 
        {0, 0, 0, 4, 2, 0, 5, 5}, 
        {2, 0, 2, 3, 0, 0, 2, 2}, 
        {2, 2, 0, 2, 0, 0, 2, 5}
    }; 

    vector<int> C = {1, 1, 1, 1, 1, 1};
    
    auto resultado = bt_poda(B, C, nt, nw);    
    assert(resultado == 0); 
    
    resultado = bt_sin_poda(B, C, nt, nw);  
    assert(resultado == 0); 
}

void testMooshak4() {
    int nt = 6;
    int nw = 8;
    vector<vector<int>> B = {
        {4, 0, 0, 0, 0, 0, 4, 5}, 
        {0, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 2, 0, 0, 3, 2, 0}, 
        {0, 0, 0, 4, 2, 0, 5, 5}, 
        {2, 0, 2, 3, 0, 0, 2, 2}, 
        {2, 2, 0, 2, 0, 0, 2, 5}
    }; 

    vector<int> C = {2, 2, 2, 2, 2, 2};
    
    auto resultado = bt_poda(B, C, nt, nw);    
    assert(resultado == 27); 
    
    resultado = bt_sin_poda(B, C, nt, nw);  
    assert(resultado == 27); 
}
/* 
void testTodosEntranJustos() {
    //int n = 4;
    int M = 10;
    vector<int> B = {2, 3, 4, 5};
    vector<int> P = {1, 2, 3, 4};
    auto resultado = Mochila_01_BTpodaFO(B, P, M);    double beneficio = resultado.voa;    assert(beneficio == 14); 
    auto resultado = Mochila_01_BTnopodaFO(B, P, M);  double beneficio = resultado.voa;    assert(beneficio == 14); 
}


void testSobraMochila() {
    //int n = 4;
    int M = 20;
    vector<int> B = {2, 3, 4, 5};
    vector<int> P = {1, 2, 3, 4};
    auto resultado = Mochila_01_BT(B, P, M);    
    auto resultado = Mochila_01_BTpodaFO(B, P, M);    double beneficio = resultado.voa;    assert(beneficio == 14); 
    auto resultado = Mochila_01_BTnopodaFO(B, P, M);  double beneficio = resultado.voa;    assert(beneficio == 14); 
}

void testSolucionesEmpatadas() {
    //int n = 4;
    int M = 4;
    vector<int> B = {2, 2, 2, 2};
    vector<int> P = {1, 1, 1, 1};
    auto resultado = Mochila_01_BTpodaFO(B, P, M);    double beneficio = resultado.voa;    assert(beneficio == 8); 
    auto resultado = Mochila_01_BTnopodaFO(B, P, M);  double beneficio = resultado.voa;    assert(beneficio == 8); 
}

void testObjetosFinales() {
    //int n = 4;
    int M = 4;
    vector<int> B = {2, 2, 9, 9};
    vector<int> P = {1, 1, 2, 2};
    auto resultado = Mochila_01_BTpodaFO(B, P, M);    double beneficio = resultado.voa;    assert(beneficio == 18); 
    auto resultado = Mochila_01_BTnopodaFO(B, P, M);  double beneficio = resultado.voa;    assert(beneficio == 18); 
}

void testSoloUno() {
    //int n = 4;
    int M = 3;
    vector<int> B = {1, 2, 10,  4};
    vector<int> P = {1, 1, 3, 2};
    auto resultado = Mochila_01_BTpodaFO(B, P, M);    double beneficio = resultado.voa;    assert(beneficio == 10); 
    auto resultado = Mochila_01_BTnopodaFO(B, P, M);  double beneficio = resultado.voa;    assert(beneficio == 10); 
}*/

int main() {
    testMooshak1();
    testMooshak2();
    testMooshak3();
    testMooshak4();
    cout << "Todos los tests pasaron!" << endl;
    return 0;
}