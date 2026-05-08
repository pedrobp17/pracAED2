#include <iostream>
#include <vector>
#include "bt.h"
using namespace std;

// NIVEL es el número de trabajo, s[NIVEL] el trabajador asignado a ese trabajo

void generar(int &nivel, Solucion& s, int &ben, vector<int>& asigW,const vector<vector<int>>& B, int libres){

        s[nivel]+=1;

        if(s[nivel]==0){
            ben+= B[s[nivel]][nivel];
            asigW[s[nivel]]+=1;
            libres--;
        }
        else{
            ben+= B[s[nivel]][nivel];
            asigW[s[nivel]]+=1;
            ben-= B[s[nivel] - 1][nivel];
            asigW[s[nivel] - 1]-=1;
        }

        
}

bool contiene(vector<int>& v, int valor){

    int L=v.size();

    for(int i=0; i<L; i++){
        if(v[i]==valor) return true;
    }


    return false;
}

void retroceder(int &nivel, Solucion& s, int &ben, vector<int>& asigW,const vector<vector<int>>& B, int libres){
    ben-=B[s[nivel]][nivel];
    asigW[s[nivel]]--;
    libres++;
    s[nivel]=-1;
    nivel--;
}

int cotaSuperior(int &nivel, int &ben, vector<int>& asigW,const vector<vector<int>>& B,const vector<int>& C, int nt, int nw) {
    int cota = ben;
    for (int j = nivel + 1; j < nt; j++) {
        int maxB = 0;
        for (int i = 0; i < nw; i++) {
            if (asigW[i] < C[i] && B[i][j] > maxB)
                maxB = B[i][j];
        }
        cota += maxB;
    }
    return cota;
}

bool criterio(int &nivel, Solucion& s, vector<int>& asigW, int ba, int bm,const vector<vector<int>>& B,const vector<int>& C, int nt, int nw){

    return nivel < nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0 &&
        !(cotaSuperior(nivel, ba, asigW, B, C, nt, nw) <= bm);

}

bool solucion(int &nivel, Solucion& s, vector<int>& asigW, const vector<vector<int>>& B, const vector<int>& C, int nt){ //necesario para comprobar que la solucion es finalmente válida

    return nivel == nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0;

}

bool trabajadoresLibres(vector<int>& asig,const vector<int>& C){
    
    int L=asig.size();
    for(int i=0; i<L; i++){
        if(asig[i]<C[i]) return true;
    }

    return false;

}

bool masHermanos(int &nivel, Solucion& s, int nw, int libres){

    return s[nivel] < nw - 1 && libres!=0;

}


int bt_poda(const vector<vector<int>>& B, const vector<int>& C, int nt, int nw){

    vector<int> asignados_workers=vector<int>(nw, 0);

    int libres=0;
    for (int i = 0; i < nw; i++) libres += C[i];

    Solucion solucion_maxima=vector<int>(nt, -1);
    int beneficio_maximo=0;
    Solucion solucion_actual=vector<int>(nt, -1);
    int beneficio_actual=0;

    int nivel=0;

    while(nivel!=-1){

        generar(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);

        if(solucion(nivel, solucion_actual, asignados_workers, B, C, nt)){ //Podria ser que almacenara soluciones innecesaria

            if(beneficio_actual>=beneficio_maximo){
                beneficio_maximo=beneficio_actual;
                solucion_maxima=solucion_actual;
            }
        }

        if(criterio(nivel, solucion_actual, asignados_workers, beneficio_actual, beneficio_maximo, B, C, nt, nw)){ 
            nivel++;
        }
        else{
            while(nivel>=0 && !masHermanos(nivel, solucion_actual, nw, libres)){
                retroceder(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);
            }
        }

    }

    return beneficio_maximo;     
}

bool criterio1(int &nivel, Solucion& s, vector<int>& asigW, int ba, int bm,const vector<vector<int>>& B,const vector<int>& C, int nt, int nw){

    return nivel < nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0;
       // !(cotaSuperior(nivel, ba, asigW, B, C, nt, nw) <= bm);

}
int bt_sin_poda(const vector<vector<int>>& B, const vector<int>& C, int nt, int nw){

    vector<int> asignados_workers=vector<int>(nw, 0);

    int libres=0;
    for (int i = 0; i < nw; i++) libres += C[i];

    Solucion solucion_maxima=vector<int>(nt, -1);
    int beneficio_maximo=0;
    Solucion solucion_actual=vector<int>(nt, -1);
    int beneficio_actual=0;

    int nivel=0;

    while(nivel!=-1){

        generar(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);

        if(solucion(nivel, solucion_actual, asignados_workers, B, C, nt)){ //Podria ser que almacenara soluciones innecesaria

            if(beneficio_actual>=beneficio_maximo){
                beneficio_maximo=beneficio_actual;
                solucion_maxima=solucion_actual;
            }
        }

        if(criterio1(nivel, solucion_actual, asignados_workers, beneficio_actual, beneficio_maximo, B, C, nt, nw)){ 
            nivel++;
        }
        else{
            while(nivel>=0 && !masHermanos(nivel, solucion_actual, nw, libres)){
                retroceder(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);
            }
        }

    }

    return beneficio_maximo;     
}