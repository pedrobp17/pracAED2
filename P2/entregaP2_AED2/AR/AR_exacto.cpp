#include <iostream>
#include <vector>

using namespace std;

struct Solucion {
    int resultado;
    vector<int> elegidos;
    Solucion(int resultado, vector<int> elegidos) : resultado(resultado), elegidos(elegidos) {}
    Solucion() : resultado(0), elegidos() {}
};

int calcularDiversidad(vector<int>& subset, vector<vector<int>>& dist) {
    int total = 0;
    int sz = subset.size();
    for (int i = 0; i < sz; i++)
        for (int j = i + 1; j < sz; j++) {
            total += dist[subset[i]][subset[j]];
            total += dist[subset[j]][subset[i]];
        }
    return total;
}

void resolver(int inicio, vector<int>& actual, int n, int m, vector<vector<int>>& dist, int& mejorBeneficio, vector<int>& mejorSubconjunto) {
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

Solucion resolverExacto(int n, int m, vector<vector<int>>& dist) {
    int mejorBeneficio = -1;
    vector<int> mejorSubconjunto;
    vector<int> actual;
    resolver(0, actual, n, m, dist, mejorBeneficio, mejorSubconjunto);

    vector<int> resultado(n, 0);
    for (int x : mejorSubconjunto) {
        resultado[x] = 1;
    }
    return Solucion(mejorBeneficio, resultado);
}

int main() {
    int T;
    cin >> T;

    for(int i=0; i<T; i++) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> dist(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> dist[i][j];

        Solucion sol = resolverExacto(n, m, dist);

        cout << sol.resultado << "\n";
        for (int i = 0; i < n; i++) {
            cout << sol.elegidos[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
