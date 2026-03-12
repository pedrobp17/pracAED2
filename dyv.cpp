#include <iostream>
#include <string>
#include <algorithm>

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
};


int contarConsecutivas(const string& B, char C){

    int n=0;
    int L=B.length();

    int i=0;

    int max=0;

    while(i!=L){
        if(B[i]==C){
            n++;
            if(n>max){
                max=n;
            }

        }
        else{ 
            n=0;
        }

        i++;
    }

    return max;

}

Solucion rachasSubstringIterativo(const string& A, int n, int m, char C){
    int p=-1;
    int numApariciones=-1;

    int L=n-m;

    int aparicionesAux;
    string B;

    for(int i=0; i<=L; i++){
        B=A.substr(i, m);
        aparicionesAux=contarConsecutivas(B, C);

        if(aparicionesAux>=numApariciones){
            p=i;
            numApariciones=aparicionesAux;
        }

    }

    return Solucion(p, numApariciones);


}

//retorna un par con el indice donde empieza la cadena de consecutivos y su longitud

int contar_consecutivo(const string& B, char C, int indice_inicio, int indice_final){

    int n=0;

    int i=indice_inicio;

    int max=0;

    while(i<=indice_final){
        if(B[i]==C){
            n++;
            if(n>max){
                max=n;
            }

        }
        else{ 
            n=0;
        }

        i++;
    }

    return max;

}

bool esNula(Solucion sol){
    return sol.indice<0 || sol.racha<0;
}

Solucion combinar_soluciones(const string& A, Solucion sol1, Solucion sol2, int m, int indice_inicio, int indice_final, char C) {

    Solucion mejor=Solucion(-1, -1);
    if (!esNula(sol1)) mejor = sol1;
    if (!esNula(sol2) && mejor < sol2)
        mejor = sol2;

    int mitad = (indice_inicio + indice_final) / 2;

    int inicio = max(indice_inicio, (mitad + 1) - m + 1);
    int final = min(mitad, indice_final - m + 1);

    for (int i = inicio; i <= final; i++) {

        Solucion candidata(i, contar_consecutivo(A, C, i, i + m - 1));

        if (esNula(mejor) || mejor < candidata)
            mejor = candidata;
    }

    return mejor;
}

Solucion rachasSubstringDyV (const string& A, int indice_inicio, int indice_final, int m, char C ){

    int longitud = (indice_final - indice_inicio) + 1;

    Solucion aux;

    if(longitud<m){
        return Solucion(-1, -1);
    }

    if(longitud==m){
        return Solucion(indice_inicio, contar_consecutivo(A, C, indice_inicio, indice_final));
    }

    int mitad = (indice_inicio + indice_final) / 2;

    //no usamos substr, aumenta mucho la complejidad

    Solucion sol1 = rachasSubstringDyV(A, indice_inicio, mitad, m, C);
    Solucion sol2 = rachasSubstringDyV(A, mitad + 1, indice_final, m, C);

    return combinar_soluciones(A, sol1, sol2, m, indice_inicio, indice_final, C); //O(m)

}