#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <cctype>

using namespace std;

//Verifica se é operador
bool ehOperador(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

//Define a prioridade dos operadores
int prioridade(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

//Aplica as operações
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

//Faz as partes que tem letra
double trigonometria(const string& funcao, double valor) {
    if (funcao == "cos") return cos(valor);
    if (funcao == "sin") return sin(valor);
    if (funcao == "tg") return tan(valor);
    if (funcao == "cosec") return 1.0 / sin(valor);
    if (funcao == "sec") return 1.0 / cos(valor);
    if (funcao == "cotg") return 1.0 / tan(valor);
    if (funcao == "log") return log10(valor);
    if (funcao == "ln") return log(valor);
    return 0;
}

//Deixa pronto para aplicar a operação
void processarOperadores(stack<double>& valores, stack<char>& operadores) {
    double valor2 = valores.top(); valores.pop();
    double valor1 = valores.top(); valores.pop();
    char op = operadores.top(); operadores.pop();
    valores.push(aplicarOperacao(valor1, valor2, op));
}

//Define funcionamento da transformação da função
double avaliaFuncao(string funcao, double x) {
    stack<double> valores;
    stack<char> operadores;
    size_t percorre = 0;

    while (percorre < funcao.length()) {
        
        //Ignora espaço em branco
        if (isspace(funcao[percorre])) {
            percorre++;
            continue;
        }

        // Tratamento do sinal negativo
        if (funcao[percorre] == '-' && (percorre == 0 || funcao[percorre - 1] == '(' || ehOperador(funcao[percorre - 1]))) {
            operadores.push('~'); // ~ Como marcador de negação
            percorre++;
            continue;
        }

        //Análisa o número por inteiro
        if (isdigit(funcao[percorre]) || funcao[percorre] == '.') {
            size_t j = percorre;
            while (j < funcao.length() && (isdigit(funcao[j]) || funcao[j] == '.')) j++;
            double valor = stod(funcao.substr(percorre, j - percorre));
            valores.push(valor);
            percorre = j;
            continue;
        }

        //Acha a variável
        if (funcao[percorre] == 'x') {
            valores.push(x);
            percorre++;
            continue;
        }

        //Tratamento recursivo de parênteses
        if (funcao[percorre] == '(') {
            int balanciar = 1;
            size_t ini = percorre + 1;
            while (balanciar != 0 && ++percorre < funcao.length()) {
                if (funcao[percorre] == '(') balanciar++;
                if (funcao[percorre] == ')') balanciar--;
            }
            string exprInterna = funcao.substr(ini, percorre - ini);
            double valorInterno = avaliaFuncao(exprInterna, x);

            // Aplica sinal negativo
            if (!operadores.empty() && operadores.top() == '~') {
                valorInterno = -valorInterno;
                operadores.pop();
            }

            valores.push(valorInterno);
            percorre++;
            continue;
        }
        
        //Vê se é um alfabeto (se é cos, sen, e, ln ... etc)
        if (isalpha(funcao[percorre])) {
            string nomeFuncao;
            while (percorre < funcao.length() && isalpha(funcao[percorre])) {
                nomeFuncao += funcao[percorre];
                percorre++;
            }
            if (nomeFuncao == "e" && funcao[percorre] == '^') {
                percorre++;
                operadores.push('^');
                valores.push(M_E); // Juro que não da problema (juro mesmo)
                continue;
            }
            if (funcao[percorre] == '(') {
                percorre++;
                int balanciar = 1;
                size_t ini = percorre;
                while (balanciar != 0 && percorre < funcao.length()) {
                    if (funcao[percorre] == '(') balanciar++;
                    else if (funcao[percorre] == ')') balanciar--;
                    percorre++;
                }
                string exprInterna = funcao.substr(ini, percorre - ini - 1);
                double valorInterno = avaliaFuncao(exprInterna, x);
                double resultadoFuncao = trigonometria(nomeFuncao, valorInterno);
                valores.push(resultadoFuncao);
                continue;
            }
        }

        //Organiza a pilha de operadores
        if (ehOperador(funcao[percorre])) {
            while (!operadores.empty() && prioridade(operadores.top()) >= prioridade(funcao[percorre]) && operadores.top() != '(') {
                processarOperadores(valores, operadores);
            }
            operadores.push(funcao[percorre]);
            percorre++;
        }
    }

    //Aplica as operações    
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