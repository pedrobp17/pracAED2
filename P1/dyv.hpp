#include <string>
#include <iostream>

using namespace std; 

struct Solucion {

    int indice;
    int racha;

    Solucion(): indice(-1), racha(-1){};

    Solucion(int i, int n): indice(i), racha(n){};

    bool operator< (const Solucion& otro) const{
        
        if (racha != otro.racha){
            return racha < otro.racha;
        }

        return indice < otro.indice;
    }
    bool operator==( const Solucion& otro) const{
        return indice == otro.indice && racha == otro.racha;
    }
    friend ostream& operator<<(ostream& os, const Solucion& sol){
        os << "( indice: " << sol.indice << ", racha: " << sol.racha << " )";
        return os;
    }
};

Solucion rachasSubstringDyV( const string& A, int indice_inicio, int indice_final, int m, char C );
Solucion rachasSubstringIterativo(const string& A, int n, int m, char C);
 