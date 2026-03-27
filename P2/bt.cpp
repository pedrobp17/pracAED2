#include <iostream>
#include <vector>

using namespace std;
using Solucion=vector<int>;

vector<vector<int>> B;
vector<int> C;
int nw, nt;

void generar(int nivel, Solucion& s, int ben, vector<int>& asigT, vector<int>& asigW){

    s[nivel]+=1;

    if(s[nivel]==0){
        ben+= B[s[nivel]][nivel];
    }
    else{
        ben+= B[s[nivel]][nivel];
        ben-= B[s[nivel] - 1][nivel];
    }

    asigT[nivel]+=1;
    asigW[s[nivel]]+=1;

}

bool contiene(vector<int>& v, int valor){

    int L=v.size();

    for(int i=0; i<L; i++){
        if(v[i]==valor) return true;
    }


    return false;
}

void retroceder(int nivel, Solucion& s, int ben, vector<int>& asigW, vector<int>& asigT){
    ben-=B[s[nivel]][nivel];
    s[nivel]=-1;
    asigW[s[nivel]]--;
    asigT[nivel]--;
    nivel--;
}

bool criterio(int nivel, Solucion& s, vector<int>& asigW){

    return nivel < nt- 1 && s[nivel] < nw -1 && asigW[s[nivel]] < C[s[nivel]] && B[s[nivel]][nivel]!=0;

}

bool solucion(int nivel, Solucion& s, vector<int>& asigT){

    return nivel==nt - 1;

}

bool trabajadoresLibres(vector<int>& asig){
    
    int L=asig.size();
    for(int i=0; i<L; i++){
        if(asig[i]<C[i]) return true;
    }

    return false;

}

bool masHermanos(int nivel, Solucion& s, vector<int>& asigW){

    return s[nivel] < nw - 1 && trabajadoresLibres(asigW);

}

int main(){

    cin>>nw>>nt;

    C = vector<int>(nw);
    B = vector<vector<int>>(nw);
    vector<int> asignados_trabajos=vector<int>(nt, 0);
    vector<int> asignados_workers=vector<int>(nw, 0);
    
    for(int i=0; i<nw; i++){
        for(int j=0; j<nt; j++){
            cin>>B[i][j];
        }
    }

    for(int i=0; i<nw; i++){
        cin>>C[i];
    }

    Solucion solucion_maxima=vector<int>(nt, -1);
    int beneficio_maximo=0;
    Solucion solucion_actual=vector<int>(nt, -1);
    int beneficio_actual=0;

    int nivel=0;

    while(nivel!=-1){

        generar(nivel, solucion_actual, beneficio_actual, asignados_trabajos, asignados_workers);

        if(solucion(nivel, solucion_actual, asignados_trabajos)){
            if(beneficio_actual>=beneficio_maximo){
                beneficio_maximo=beneficio_actual;
                solucion_maxima=solucion_actual;
            }
        }

        if(criterio(nivel, solucion_actual, asignados_workers)){
            nivel++;
        }
        else{
            while(nivel>=0 && !masHermanos(nivel, solucion_actual, asignados_workers)){
                retroceder(nivel, solucion_actual, beneficio_actual, asignados_workers, asignados_trabajos);
            }
        }

    }

    cout<<beneficio_maximo<<endl;


    return 0;
}