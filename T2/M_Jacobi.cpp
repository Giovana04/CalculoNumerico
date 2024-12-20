#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

bool tornarDiagonalDominante(double** matriz, double* b, int n);
double* jacobi(double** matriz, double* b, int n, double e, int numIter);
double calcErro(double* a, double* b, int n);

int main() {
    int n;
    double e;
    int numIter;

    cout << "Digite o numero de variaveis (n): ";
    cin >> n;

    double** matriz = new double*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new double[n];
    }
    double* b = new double[n];

    cout << "Digite a matriz dos coeficientes (linha por linha):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];
        }
    }

    cout << "Digite o vetor b (resultados):\n";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    cout << "Digite o erro desejado (triangulinho): ";
    cin >> e;

    cout << "Digite o numero maximo de iteracoes: ";
    cin >> numIter;

    if (!tornarDiagonalDominante(matriz, b, n)) {
    cout << "A matriz nao pode ser tornada diagonal dominante. O metodo de Jacobi pode nao convergir." << endl;
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] b;
    return 1;
}


    double* resultado = jacobi(matriz, b, n, e, numIter);

    cout << "Resultado da solucao aproximada: \n";
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << resultado[i] << endl;
    }

    delete[] resultado;
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] b;

    return 0;
}

bool tornarDiagonalDominante(double** matriz, double* b, int n) {
    int* permutacao = new int[n];
    for (int i = 0; i < n; i++) {
        permutacao[i] = i; 
    }

    for (int i = 0; i < n; i++) {
        double maior = fabs(matriz[i][i]);
        int coluna_maior = i;

        for (int j = i + 1; j < n; j++) {
            if (fabs(matriz[i][j]) > maior) {
                maior = fabs(matriz[i][j]);
                coluna_maior = j;
            }
        }

        if (coluna_maior != i) {
            for (int k = 0; k < n; k++) {
                swap(matriz[k][i], matriz[k][coluna_maior]);
            }
            swap(permutacao[i], permutacao[coluna_maior]);
        }
    }

    bool diagonalDominante = true;
    for (int i = 0; i < n; i++) {
        double soma = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                soma += fabs(matriz[i][j]);
            }
        }
        if (fabs(matriz[i][i]) < soma) {
            diagonalDominante = false;
            break;
        }
    }

    delete[] permutacao;
    return diagonalDominante;
}


double* jacobi(double** matriz, double* b, int n, double e, int numIter) {
    double* x0 = new double[n];
    double* x = new double[n];
    double erro = 100.0; 
    int k = 0;

    for (int i = 0; i < n; i++) {
        x0[i] = 0.0;
    }

    while (erro >= e && k < numIter) {
        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    soma += matriz[i][j] * x0[j];
                }
            }
            x[i] = (b[i] - soma) / matriz[i][i];
        }

        erro = calcErro(x, x0, n);

        for (int i = 0; i < n; i++) {
            x0[i] = x[i];
        }

        k++;
    }

    delete[] x0;
    return x;
}

double calcErro(double* a, double* b, int n) {
    double maior = 0, diferenca;
    for (int i = 0; i < n; i++) {
        diferenca = fabs(a[i] - b[i]);
        if (diferenca > maior) {
            maior = diferenca;
        }
    }
    return maior;
}
