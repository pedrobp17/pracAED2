#include <iostream>
#include <vector>
#include "bt.h"
using namespace std;

// NIVEL es el número de trabajo, s[NIVEL] el trabajador asignado a ese trabajo

// Función generar, análoga a la vista en teoría. Avanza al siguiente trabajador y actualiza las variables de control
// y optimización

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

// Función auxiliar
 
bool contiene(vector<int>& v, int valor){

    int L=v.size();

    for(int i=0; i<L; i++){
        if(v[i]==valor) return true;
    }


    return false;
}

//Función retroceder, vuelve al nivel anterior, actualizando las variables de control y de optimización

void retroceder(int &nivel, Solucion& s, int &ben, vector<int>& asigW,const vector<vector<int>>& B, int libres){
    ben-=B[s[nivel]][nivel];
    asigW[s[nivel]]--;
    libres++;
    s[nivel]=-1;
    nivel--;
}

// Función objetivo. Se usará en la poda, el funcionamiento es el siguiente: a partir del estado actual se recorre 
// nivel a nivel el árbol, seleccionando la mejor combinación posible de hermanos. La motivación de esta función es
// evitar recorrer todo un elenco combinatorio de soluciones válidas cuando ninguna nos va a servir

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

// Poda usando la cota superior como hemos descrito, por restricción de capacidad, por restricción de habilidad
// y si hemos llegado a un nodo hoja

bool criterio(int &nivel, Solucion& s, vector<int>& asigW, int ba, int bm,const vector<vector<int>>& B,const vector<int>& C, int nt, int nw){

    return nivel < nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0 &&
        !(cotaSuperior(nivel, ba, asigW, B, C, nt, nw) <= bm);

}

// Comprueba si estamos ante una solución válida. Solo verifica la última componente ya que si alguna anterior fuera
// errónea criterio ya la habría podado

bool solucion(int &nivel, Solucion& s, vector<int>& asigW, const vector<vector<int>>& B, const vector<int>& C, int nt){ //necesario para comprobar que la solucion es finalmente válida

    return nivel == nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0;

}

// Función auxiliar, se usaba antes de la inclusión de la variable libres

bool trabajadoresLibres(vector<int>& asig,const vector<int>& C){
    
    int L=asig.size();
    for(int i=0; i<L; i++){
        if(asig[i]<C[i]) return true;
    }

    return false;

}

// Determina si hay más hermanos disponibles en un determinado nivel, es decir, si quedan trabajadores
// no escogidos y si los que quedan tienen espacio libre

bool masHermanos(int &nivel, Solucion& s, int nw, int libres){

    return s[nivel] < nw - 1 && libres!=0;

}

// Implementación del esquema de optimización visto en teoría, usando el criterio que poda por cota superior

int bt_poda(const vector<vector<int>>& B, const vector<int>& C, int nt, int nw){

    // Vector que controla el número de trabajos asignados a cada trabajador

    vector<int> asignados_workers=vector<int>(nw, 0);

    // Variable que controla el número de pares (trabajador, tarea) disponibles, es decir, inicializa a 
    // la suma de las capacidades de todos los trabajadores

    int libres=0;
    for (int i = 0; i < nw; i++) libres += C[i];

    // Almacenan la mejor solución y la solución actual en cada instante de la ejecución

    Solucion solucion_maxima=vector<int>(nt, -1);
    int beneficio_maximo=0;
    Solucion solucion_actual=vector<int>(nt, -1);
    int beneficio_actual=0;

    int nivel=0;

    // Esquema visto en teoría

    while(nivel!=-1){

        generar(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);

        //Si es solución, y mejor que la ya guardada, actualizamos

        if(solucion(nivel, solucion_actual, asignados_workers, B, C, nt)){

            if(beneficio_actual>=beneficio_maximo){
                beneficio_maximo=beneficio_actual;
                solucion_maxima=solucion_actual;
            }
        }

        // Si nos renta bajar, bajamos

        if(criterio(nivel, solucion_actual, asignados_workers, beneficio_actual, beneficio_maximo, B, C, nt, nw)){ 
            nivel++;
        }
        else{ // Si no, en caso de que podamos y de que no queden más posibilidades, retrocedemos
            while(nivel>=0 && !masHermanos(nivel, solucion_actual, nw, libres)){
                retroceder(nivel, solucion_actual, beneficio_actual, asignados_workers, B, libres);
            }
        }

    }

    return beneficio_maximo;     
}

// Criterio de poda sin poda por cota superior

bool criterio1(int &nivel, Solucion& s, vector<int>& asigW, int ba, int bm,const vector<vector<int>>& B,const vector<int>& C, int nt, int nw){

    return nivel < nt - 1 && 
        asigW[s[nivel]] <= C[s[nivel]] && 
        B[s[nivel]][nivel]!=0;
       // !(cotaSuperior(nivel, ba, asigW, B, C, nt, nw) <= bm);

}

// Análogo a bt_poda, usando este último criterio

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