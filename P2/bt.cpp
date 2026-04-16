#include <iostream>
#include <vector>

using namespace std;
using Solucion=vector<int>;

vector<vector<int>> B;
vector<int> C;
int T;
int nw, nt;
int libres;

// NIVEL es el número de trabajo, s[NIVEL] el trabajador asignado a ese trabajo

void generar(int &nivel, Solucion& s, int &ben, vector<int>& asigW){

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

void retroceder(int &nivel, Solucion& s, int &ben, vector<int>& asigW){
    ben-=B[s[nivel]][nivel];
    asigW[s[nivel]]--;
    libres++;
    s[nivel]=-1;
    nivel--;
}

int cotaSuperior(int nivel, int ben, vector<int>& asigW) {
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

bool criterio(int &nivel, Solucion& s, vector<int>& asigW, int ba, int bm){

    return nivel < nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0 &&
        !(cotaSuperior(nivel, ba, asigW) <= bm);

}

bool solucion(int &nivel, Solucion& s, vector<int>& asigW){ //necesario para comprobar que la solucion es finalmente válida

    return nivel == nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0;

}

bool trabajadoresLibres(vector<int>& asig){
    
    int L=asig.size();
    for(int i=0; i<L; i++){
        if(asig[i]<C[i]) return true;
    }

    return false;

}

bool masHermanos(int &nivel, Solucion& s){

    return s[nivel] < nw - 1 && libres!=0;

}

int main(){

    cin>>T;

    for(int k=0; k<T; k++){

        cin>>nw>>nt;

        C = vector<int>(nw);
        B = vector<vector<int>>(nw, vector<int>(nt));
        vector<int> asignados_workers=vector<int>(nw, 0);
        
        for(int i=0; i<nw; i++){
            for(int j=0; j<nt; j++){
                cin>>B[i][j];
            }
        }

        for(int i=0; i<nw; i++){
            cin>>C[i];
        }

        libres=0;
        for (int i = 0; i < nw; i++) libres += C[i];

        Solucion solucion_maxima=vector<int>(nt, -1);
        int beneficio_maximo=0;
        Solucion solucion_actual=vector<int>(nt, -1);
        int beneficio_actual=0;

        int nivel=0;

        while(nivel!=-1){

            generar(nivel, solucion_actual, beneficio_actual, asignados_workers);

            if(solucion(nivel, solucion_actual, asignados_workers)){ //Podria ser que almacenara soluciones innecesaria

                if(beneficio_actual>=beneficio_maximo){
                    beneficio_maximo=beneficio_actual;
                    solucion_maxima=solucion_actual;
                }
            }

            if(criterio(nivel, solucion_actual, asignados_workers, beneficio_actual, beneficio_maximo)){ 
                nivel++;
            }
            else{
                while(nivel>=0 && !masHermanos(nivel, solucion_actual)){
                    retroceder(nivel, solucion_actual, beneficio_actual, asignados_workers);
                }
            }

        }

        cout<<beneficio_maximo<<endl;
    }

    return 0;
}