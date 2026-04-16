#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Variables globales
vector<vector<int>> B;
vector<int> capacidadTrabajador;
vector<int> s;
int beneficio_actual = 0;
int num_tareas;      // Cambiado para claridad: nt
int num_trabajadores; // Cambiado para claridad: nw

// --- FUNCIÓN DE VISUALIZACIÓN ---
void imprimirPaso(int nivel, string accion) {
    // Imprime el nivel actual y la acción (GENERAR, CRITERIO OK, RETROCEDER)
    cout << "[Nivel " << nivel << "] " << accion << " -> Vector s: [";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == -1) cout << "_ ";
        else cout << s[i] << " ";
    }
    cout << "] | Beneficio Actual: " << beneficio_actual << endl;
}

// --- FUNCIONES DEL ALGORITMO ---

void leerMatriz(int trab, int tar){
    B.assign(trab, vector<int>(tar));
    for( int i = 0; i < trab; i++)
        for( int j = 0; j < tar; j++)
            cin >> B[i][j];
}

void leerCapacidades(int trab){
    capacidadTrabajador.assign(trab, 0);
    for( int i = 0; i < trab; i++)
        cin >> capacidadTrabajador[i]; 
}

void inicializar(){
    beneficio_actual = 0;
    if (!(cin >> num_trabajadores >> num_tareas)) return;
    leerMatriz(num_trabajadores, num_tareas);
    leerCapacidades(num_trabajadores);
    s.assign(num_tareas, -1); // Un espacio por cada tarea
}

void generar(int nivel) {
    // Si ya había un trabajador asignado en este nivel, restamos su beneficio antes de poner el nuevo
    if (s[nivel] != -1) {
        beneficio_actual -= B[s[nivel]][nivel];
    }
    
    s[nivel] += 1; // Probamos el siguiente trabajador
    
    // Si el nuevo trabajador es válido dentro del rango, sumamos su beneficio
    if (s[nivel] < num_trabajadores) {
        beneficio_actual += B[s[nivel]][nivel];
    }
    
    imprimirPaso(nivel, "GENERAR");
}

bool solucion(int nivel) {
    // Es solución si hemos asignado la última tarea
    return nivel == num_tareas - 1;
}

bool criterio(int nivel) {
    int trab_act = s[nivel];
    // Verificamos rango, capacidad y si sabe hacer la tarea
    bool ok = (trab_act < num_trabajadores && 
               capacidadTrabajador[trab_act] > 0 && 
               B[trab_act][nivel] > 0);
    
    if (ok) imprimirPaso(nivel, "CRITERIO OK (Avanzando)");
    return ok;
}

bool masHermanos(int nivel) {
    return s[nivel] < num_trabajadores - 1;
}

void retroceder(int &nivel) {
    // Antes de limpiar, restamos el beneficio del trabajador que ocupaba este nivel
    if (s[nivel] != -1 && s[nivel] < num_trabajadores) {
        beneficio_actual -= B[s[nivel]][nivel];
        // Si el criterio fue OK antes, le devolvemos su capacidad (esto depende de tu lógica de avance)
        // capacidadTrabajador[s[nivel]]++; 
    }
    
    imprimirPaso(nivel, "RETROCEDER");
    s[nivel] = -1;
    nivel--;
}

// --- ESQUEMA GENERAL ---

int backtracking_optimizacion_maximizar() {
    inicializar();
    int nivel = 0;
    int voa = -1;
    
    cout << "\n--- INICIO TRAZA ---" << endl;

    while (nivel != -1) {
        generar(nivel);

        if (criterio(nivel)) {
            // "MARCAR": Usamos la capacidad del trabajador
            capacidadTrabajador[s[nivel]]--;

            if (solucion(nivel)) {
                if (beneficio_actual > voa) {
                    voa = beneficio_actual;
                    cout << "   >>> NUEVA MEJOR SOLUCION: " << voa << endl;
                }
                // Como es solución, desmarcamos para seguir buscando hermanos en este nivel
                capacidadTrabajador[s[nivel]]++;
            } else {
                nivel++;
            }
        } else {
            // Si no cumple criterio, el beneficio se resta en la siguiente llamada a generar o retroceder
            while (nivel >= 0 && !masHermanos(nivel)) {
                retroceder(nivel);
            }
        }
    }
    return voa;
}

int main() {
    int casos;
    if (!(cin >> casos)) return 0;
    for( int i = 0; i < casos; i++){
        int resultado = backtracking_optimizacion_maximizar();
        cout << "\nRESULTADO FINAL CASO " << i+1 << ": " << (resultado == -1 ? 0 : resultado) << endl;
    }
    return 0;
}