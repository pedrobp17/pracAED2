#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <string>
#include "bt.h"

using namespace std;

struct Caso {
    int nt;
    int nw;
    vector<vector<int>> B;
    vector<int> C;
};

Caso generarCasoAleatorio(int nt, double multMin, double multMax,
                          int benefMax, int capMax, mt19937& gen) {
    uniform_real_distribution<double> mult_dist(multMin, multMax);
    double mult = mult_dist(gen);

    int nw = (int)(nt * mult + 0.5);
    if (nw < 1) nw = 1;

    uniform_int_distribution<int> benefit_dist(0, benefMax);
    vector<vector<int>> B(nw, vector<int>(nt));
    for (int i = 0; i < nw; i++) {
        for (int j = 0; j < nt; j++) {
            B[i][j] = benefit_dist(gen);
        }
    }

    uniform_int_distribution<int> cap_dist(1, capMax);
    vector<int> C(nw);
    for (int i = 0; i < nw; i++) {
        C[i] = cap_dist(gen);
    }

    return {nt, nw, B, C};
}

double medirTiempo_poda(Caso& caso) {
    auto start = chrono::high_resolution_clock::now();
    bt_poda(caso.B, caso.C, caso.nt, caso.nw);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = end - start;
    return duracion.count();
}

double medirTiempo_sin_poda(Caso& caso) {
    auto start = chrono::high_resolution_clock::now();
    bt_sin_poda(caso.B, caso.C, caso.nt, caso.nw);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = end - start;
    return duracion.count();
}

double calcularMediana(vector<double> v) {
    if (v.empty()) return 0.0;
    sort(v.begin(), v.end());
    int n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

double calcularMedia(vector<double> v) {
    if (v.empty()) return 0.0;
    double s = 0;
    for (int i = 0; i < (int)v.size(); i++) s += v[i];
    return s / v.size();
}

double calcularMin(vector<double> v) {
    if (v.empty()) return 0.0;
    double m = v[0];
    for (int i = 1; i < (int)v.size(); i++) if (v[i] < m) m = v[i];
    return m;
}

double calcularMax(vector<double> v) {
    if (v.empty()) return 0.0;
    double m = v[0];
    for (int i = 1; i < (int)v.size(); i++) if (v[i] > m) m = v[i];
    return m;
}

int main() {
    int nt = 7;
    double multMin = 0.5;
    double multMax = 1.5;
    int benefMax = 9;
    int capMax = 5;
    int num_casos = 50;
    int repeticiones = 3;

    random_device rd;
    mt19937 gen(rd());

    int casos_poda_mejor = 0;
    int casos_poda_peor = 0;
    int casos_iguales = 0;

    vector<double> mejoras_pct;
    vector<double> empeoramientos_pct;
    vector<double> ratios_mejora;
    vector<double> ratios_empeora;

    ofstream csv("comparacion_BT.csv");
    csv << "Caso,nt,nw,Tiempo_Sin_Poda,Tiempo_Con_Poda,Diferencia_Absoluta,Diferencia_Porcentual,Ratio,Resultado\n";

    cout << "Comparacion BT con/sin poda - casos aleatorios" << endl;
    cout << "  nt = " << nt << endl;
    cout << "  multiplicador en [" << multMin << ", " << multMax << "]" << endl;
    cout << "  beneficios en [0, " << benefMax << "]" << endl;
    cout << "  capacidades en [1, " << capMax << "]" << endl;
    cout << "  numero de casos = " << num_casos << endl;
    cout << "  repeticiones por caso = " << repeticiones << endl << endl;

    for (int i = 0; i < num_casos; i++) {
        Caso caso = generarCasoAleatorio(nt, multMin, multMax, benefMax, capMax, gen);

        vector<double> tiempos_sin;
        vector<double> tiempos_con;
        for (int j = 0; j < repeticiones; j++) {
            tiempos_sin.push_back(medirTiempo_sin_poda(caso));
            tiempos_con.push_back(medirTiempo_poda(caso));
        }

        double medSin = calcularMediana(tiempos_sin);
        double medCon = calcularMediana(tiempos_con);

        double diff_pct = 0.0;
        if (medSin > 0) diff_pct = (medSin - medCon) / medSin * 100.0;

        string resultado;
        if (medCon < medSin) {
            casos_poda_mejor++;
            if (medSin > 0) mejoras_pct.push_back(diff_pct);
            if (medCon > 0) ratios_mejora.push_back(medSin / medCon);
            resultado = "ConPoda mejor";
        } else if (medCon > medSin) {
            casos_poda_peor++;
            if (medSin > 0) {
                empeoramientos_pct.push_back(-diff_pct);
                ratios_empeora.push_back(medCon / medSin);
            }
            resultado = "ConPoda peor";
        } else {
            casos_iguales++;
            resultado = "Igual";
        }

        csv << i + 1 << "," << caso.nt << "," << caso.nw << ","
            << medSin << "," << medCon << ","
            << (medSin - medCon) << "," << diff_pct << ","
            << ((medCon > 0) ? (medSin / medCon) : 0.0) << ","
            << resultado << "\n";

        cout << "Caso " << i + 1 << "/" << num_casos
             << " | nw=" << caso.nw
             << " | sin=" << medSin << "ms"
             << " | con=" << medCon << "ms"
             << " | dif=" << diff_pct << "%"
             << " | " << resultado << endl;
    }

    csv.close();

    cout << endl << "RESUMEN" << endl;
    cout << "Total de casos: " << num_casos << endl;
    cout << "  Con poda MEJOR: " << casos_poda_mejor
         << " (" << 100.0 * casos_poda_mejor / num_casos << "%)" << endl;
    cout << "  Con poda PEOR:  " << casos_poda_peor
         << " (" << 100.0 * casos_poda_peor / num_casos << "%)" << endl;
    cout << "  Empate:         " << casos_iguales
         << " (" << 100.0 * casos_iguales / num_casos << "%)" << endl;
    cout << endl;

    if (!mejoras_pct.empty()) {
        cout << "Cuando CON PODA es MEJOR:" << endl;
        cout << "  Mejora porcentual:" << endl;
        cout << "    media   = " << calcularMedia(mejoras_pct) << "%" << endl;
        cout << "    mediana = " << calcularMediana(mejoras_pct) << "%" << endl;
        cout << "    min     = " << calcularMin(mejoras_pct) << "%" << endl;
        cout << "    max     = " << calcularMax(mejoras_pct) << "%" << endl;
        cout << "  Speedup (sin/con):" << endl;
        cout << "    media   = " << calcularMedia(ratios_mejora) << "x" << endl;
        cout << "    mediana = " << calcularMediana(ratios_mejora) << "x" << endl;
        cout << "    max     = " << calcularMax(ratios_mejora) << "x" << endl;
    } else {
        cout << "No hay casos donde con poda sea mejor." << endl;
    }

    cout << endl;

    if (!empeoramientos_pct.empty()) {
        cout << "Cuando CON PODA es PEOR:" << endl;
        cout << "  Empeoramiento porcentual:" << endl;
        cout << "    media   = " << calcularMedia(empeoramientos_pct) << "%" << endl;
        cout << "    mediana = " << calcularMediana(empeoramientos_pct) << "%" << endl;
        cout << "    min     = " << calcularMin(empeoramientos_pct) << "%" << endl;
        cout << "    max     = " << calcularMax(empeoramientos_pct) << "%" << endl;
        cout << "  Slowdown (con/sin):" << endl;
        cout << "    media   = " << calcularMedia(ratios_empeora) << "x" << endl;
        cout << "    mediana = " << calcularMediana(ratios_empeora) << "x" << endl;
        cout << "    max     = " << calcularMax(ratios_empeora) << "x" << endl;
    } else {
        cout << "No hay casos donde con poda sea peor." << endl;
    }

    cout << endl << "Resultados guardados en comparacion_BT.csv" << endl;

    return 0;
}