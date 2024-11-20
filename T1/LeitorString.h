#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <cctype>

using namespace std;

bool ehOperador(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

int prioridade(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double aplicarOperacao(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double trigonometria(const string& funcao, double valor) {
    if (funcao == "cos") return cos(valor);
    if (funcao == "sin") return sin(valor);
    if (funcao == "tg") return tan(valor);
    if (funcao == "cosec") return 1.0 / sin(valor);
    if (funcao == "sec") return 1.0 / cos(valor);
    if (funcao == "cotg") return 1.0 / tan(valor);
    return 0;
}

void processarOperadores(stack<double>& valores, stack<char>& operadores) {
    double valor2 = valores.top(); valores.pop();
    double valor1 = valores.top(); valores.pop();
    char op = operadores.top(); operadores.pop();
    valores.push(aplicarOperacao(valor1, valor2, op));
}

double avaliaFuncao(string funcao, double x) {
    stack<double> valores;
    stack<char> operadores;
    size_t percorre = 0;

    while (percorre < funcao.length()) {
        if (isspace(funcao[percorre])) {
            percorre++;
            continue;
        }

        // Tratamento do sinal negativo
        if (funcao[percorre] == '-' && (percorre == 0 || funcao[percorre - 1] == '(' || ehOperador(funcao[percorre - 1]))) {
            operadores.push('~'); // Usamos ~ como marcador de negação unária
            percorre++;
            continue;
        }

        if (isdigit(funcao[percorre]) || funcao[percorre] == '.') {
            size_t j = percorre;
            while (j < funcao.length() && (isdigit(funcao[j]) || funcao[j] == '.')) j++;
            double valor = stod(funcao.substr(percorre, j - percorre));
            valores.push(valor);
            percorre = j;
            continue;
        }

        if (funcao[percorre] == 'x') {
            valores.push(x);
            percorre++;
            continue;
        }

        if (funcao[percorre] == '(') {
            int balance = 1;
            size_t start = percorre + 1;
            while (balance != 0 && ++percorre < funcao.length()) {
                if (funcao[percorre] == '(') balance++;
                if (funcao[percorre] == ')') balance--;
            }
            string exprInterna = funcao.substr(start, percorre - start);
            double valorInterno = avaliaFuncao(exprInterna, x);

            // Aplicar sinal negativo, se necessário
            if (!operadores.empty() && operadores.top() == '~') {
                valorInterno = -valorInterno;
                operadores.pop();
            }

            valores.push(valorInterno);
            percorre++;
            continue;
        }

        if (isalpha(funcao[percorre])) {
            string nomeFuncao;
            while (percorre < funcao.length() && isalpha(funcao[percorre])) {
                nomeFuncao += funcao[percorre];
                percorre++;
            }
            if (nomeFuncao == "e" && funcao[percorre] == '^') {
                percorre++;
                operadores.push('^');
                valores.push(M_E);
                continue;
            }
            if (funcao[percorre] == '(') {
                percorre++;
                int balance = 1;
                size_t start = percorre;
                while (balance != 0 && percorre < funcao.length()) {
                    if (funcao[percorre] == '(') balance++;
                    else if (funcao[percorre] == ')') balance--;
                    percorre++;
                }
                string exprInterna = funcao.substr(start, percorre - start - 1);
                double valorInterno = avaliaFuncao(exprInterna, x);
                double resultadoFuncao = trigonometria(nomeFuncao, valorInterno);
                valores.push(resultadoFuncao);
                continue;
            }
        }

        if (ehOperador(funcao[percorre])) {
            while (!operadores.empty() && prioridade(operadores.top()) >= prioridade(funcao[percorre]) && operadores.top() != '(') {
                processarOperadores(valores, operadores);
            }
            operadores.push(funcao[percorre]);
            percorre++;
        }
    }

    while (!operadores.empty()) {
        if (operadores.top() == '~') {
            double valor = valores.top(); valores.pop();
            valores.push(-valor);
            operadores.pop();
        } else {
            processarOperadores(valores, operadores);
        }
    }

    return valores.top();
}