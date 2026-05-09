#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// ── Estructuras ──────────────────────────────────────────────

struct Nodo {
    int i;
    int j;
    int beneficio;
    Nodo(int i, int j, int beneficio) : i(i), j(j), beneficio(beneficio) {}
    Nodo() : i(0), j(0), beneficio(0) {}
};

struct Solucion {
    int resultado;
    vector<int> elegidos;
    Solucion(int resultado, vector<int> elegidos) : resultado(resultado), elegidos(elegidos) {}
    Solucion() : resultado(0), elegidos() {}
};

// ── Avance rápido ────────────────────────────────────────────

bool comparar(const Nodo& nodo1, const Nodo& nodo2) {
    return nodo1.beneficio > nodo2.beneficio;
}

void actualizar_beneficio(vector<int>& vec, int& beneficio, int indice, const vector<vector<int>>& distancias){
    int size = vec.size();
    for( int i = 0; i < size; i++){
            beneficio += distancias[indice][vec[i]];
            beneficio += distancias[vec[i]][indice];
    }
    vec.push_back(indice);
}

Solucion avance_rapido(int n, int m, const vector<vector<int>>& distancias) {
    vector<vector<Nodo>> poblacion(n, vector<Nodo>(n, Nodo()));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if( j >= i ){
                poblacion[i][j] = Nodo(i, j, distancias[i][j]);
            }else{
                poblacion[j][i].beneficio += distancias[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        sort(poblacion[i].begin(), poblacion[i].end(), comparar);
    }
    vector<int> elegidos(n, 0);
    vector<int> aux;
    vector<int> indices(n, 0);
    int subpoblacion = m;
    int beneficio = 0;

    while (subpoblacion > 0) {
        int max_beneficio = -1;
        int fila = -1;

        for (int i = 0; i < n; i++) {
            if (indices[i] < n - i) {
                if (poblacion[i][indices[i]].beneficio > max_beneficio) {
                    max_beneficio = poblacion[i][indices[i]].beneficio;
                    fila = i;
                }
            }
        }

        Nodo& actual = poblacion[fila][indices[fila]];

        if (elegidos[actual.i] < 1) {
            elegidos[actual.i] = 1;
            actualizar_beneficio(aux, beneficio, actual.i, distancias);
            subpoblacion--;
        }

        if (subpoblacion > 0 && elegidos[actual.j] < 1) {
            elegidos[actual.j] = 1;
            actualizar_beneficio(aux, beneficio, actual.j, distancias);
            subpoblacion--;
        }

        indices[fila]++;
    }

    return Solucion(beneficio, elegidos);
}

// ── Exacto ───────────────────────────────────────────────────

int calcularDiversidad(const vector<int>& subset, const vector<vector<int>>& dist) {
    int total = 0;
    int sz = subset.size();
    for (int i = 0; i < sz; i++)
        for (int j = i + 1; j < sz; j++) {
            total += dist[subset[i]][subset[j]];
            total += dist[subset[j]][subset[i]];
        }
    return total;
}

void resolver(int inicio, vector<int>& actual, int n, int m, const vector<vector<int>>& dist,
              int& mejorBeneficio, vector<int>& mejorSubconjunto) {
    if ((int)actual.size() == m) {
        int val = calcularDiversidad(actual, dist);
        if (val > mejorBeneficio) {
            mejorBeneficio = val;
            mejorSubconjunto = actual;
        }
        return;
    }
    int restantes = n - inicio;
    int necesarios = m - (int)actual.size();
    if (restantes < necesarios) return;

    for (int i = inicio; i < n; i++) {
        actual.push_back(i);
        resolver(i + 1, actual, n, m, dist, mejorBeneficio, mejorSubconjunto);
        actual.pop_back();
    }
}

Solucion resolverExacto(int n, int m, const vector<vector<int>>& dist) {
    int mejorBeneficio = -1;
    vector<int> mejorSubconjunto;
    vector<int> actual;
    resolver(0, actual, n, m, dist, mejorBeneficio, mejorSubconjunto);

    vector<int> resultado(n, 0);
    for (int x : mejorSubconjunto) resultado[x] = 1;
    return Solucion(mejorBeneficio, resultado);
}

// ── Main ─────────────────────────────────────────────────────

int main(int argc, char* argv[]) {
    int semilla     = (argc > 1) ? atoi(argv[1]) : 42;
    int numTests    = (argc > 2) ? atoi(argv[2]) : 1000;
    int maxN        = (argc > 3) ? atoi(argv[3]) : 10;
    double maxMFrac = (argc > 4) ? atof(argv[4]) : 0.7;

    srand(semilla);

    int totalTests     = 0;
    int aciertos       = 0;
    int fallos         = 0;
    double sumaErrores = 0.0;
    double maxError    = 0.0;

    for (int t = 0; t < numTests; t++) {
        int n    = 3 + rand() % (maxN - 2);
        int mMin = 2;
        int mMax = max(mMin, (int)(n * maxMFrac));
        int m    = mMin + rand() % (mMax - mMin + 1);

        vector<vector<int>> dist(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    dist[i][j] = rand() % 101;

        Solucion exacto = resolverExacto(n, m, dist);
        Solucion voraz  = avance_rapido(n, m, dist);

        totalTests++;

        bool correcto = (voraz.resultado == exacto.resultado);
        if (correcto) {
            aciertos++;
        } else {
            fallos++;
            double errorRel = 0.0;
            if (exacto.resultado > 0)
                errorRel = (double)(exacto.resultado - voraz.resultado)
                           / (double)exacto.resultado;
            sumaErrores += errorRel;
            if (errorRel > maxError) maxError = errorRel;

            if (fallos <= 20) {
                cout << "FALLO #" << fallos
                     << " (test " << t + 1 << ") n=" << n << " m=" << m << "\n";
                cout << "  Optimo: " << exacto.resultado
                     << "  Voraz: " << voraz.resultado
                     << "  Error: " << (int)(errorRel * 100) << "%\n";
            }
        }
    }

    double mediaError = (fallos > 0) ? (sumaErrores / fallos) * 100.0 : 0.0;

    cout << "\nTotal pruebas    : " << totalTests << "\n";
    cout << "Correctas        : " << aciertos << " (" << (100 * aciertos / totalTests) << "%)\n";
    cout << "Fallos           : " << fallos   << " (" << (100 * fallos   / totalTests) << "%)\n";
    if (fallos > 0) {
        cout << "Error medio      : " << (int)mediaError << "%\n";
        cout << "Error maximo     : " << (int)(maxError * 100) << "%\n";
    }

    return 0;
}
