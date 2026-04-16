#include <iostream>
#include <vector>

using namespace std;

// Variables globales auxiliares
vector<vector<int>> B; // Matriz de Beneficios: B[trabajador][tarea]
vector<int> capacidadTrabajador;
vector<int> s;
int beneficio_actual = 0;
int tarea;
int trabajador;

// --- FUNCIONES DEL ALGORITMO ---

void leerMatriz(int trab, int tar){
    B.assign(trab, vector<int>(tar));
    
    for( int i = 0; i < trab; i++){
        for( int j = 0; j < tar; j++){
            cin >> B[i][j];
        }
    }
}

void leerCapacidades(int trab){
    capacidadTrabajador.assign(trab, 0);
    for( int i = 0; i < trab; i++){
        cin >> capacidadTrabajador[i]; 
    }
}
void inicializar(){
    B.clear();
    capacidadTrabajador.clear();
    s.clear();
    beneficio_actual = 0;
    cin >> trabajador >> tarea;
    leerMatriz(trabajador, tarea);
    leerCapacidades(trabajador);
    s.assign(trabajador, -1);
}
void generar(int nivel) {
    s[nivel] += 1;
    if ( s[nivel] == 0) {
        beneficio_actual += B[s[nivel]][nivel];
    } else {
        beneficio_actual += B[s[nivel]][nivel];
        beneficio_actual -= B[s[nivel] - 1][nivel];
    }
}
bool solucion(int nivel) {
    return nivel == trabajador - 1;
}

bool criterio(int nivel) {
    int trabajador_act = s[nivel];
    return trabajador_act < trabajador && capacidadTrabajador[trabajador_act] > 0 && B[trabajador_act][nivel] > 0 ;
}

bool masHermanos(int nivel) {
    return s[nivel] < trabajador - 1;
}

void retroceder(int &nivel) {
    beneficio_actual -= B[s[nivel]][nivel]; 
    capacidadTrabajador[s[nivel]]++;
    s[nivel] = -1;
    nivel--;
}

// --- ESQUEMA GENERAL ---

int backtracking_optimizacion_maximizar() {
    int nivel = 0;
    int voa = -1;
    inicializar();
    while (nivel != -1) {
        generar(nivel);

        if (solucion(nivel)) {
            if (beneficio_actual > voa) {
                voa = beneficio_actual;
            }
        }

        if (criterio(nivel)) {
            nivel++;
        } else {
            while (nivel >= 0 && !masHermanos(nivel)) {
                retroceder(nivel);
            }
        }
    }
    return voa;
}

int main() {
    int casos;
    cin >> casos;
    for( int i = 0; i < casos; i++){
        int resultado = backtracking_optimizacion_maximizar();
        if(resultado == -1){
            cout << 0 << endl;
        }else{
            cout << resultado << endl;
        }
    }
    return 0;
}