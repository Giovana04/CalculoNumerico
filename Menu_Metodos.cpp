#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <stack>
#include <cctype>
#include <map>
#include <functional>
using namespace std;

// Lógica de string
bool ehOperador(char c);
int precedencia(char op);
double aplicarOperacao(double a, double b, char op);
double avaliar(const string &expressao, const map<string, double> &variaveis);
// Lógica de armazenar as funções dos exercicios
function<void()> inicia();
function<void()> iniciaFI();
function<void()> iniciaDEV();
// Lógica dos modulos
double moduloUM(double a);
double moduloDois(double a, double b);
// Onde é armazenada a função
double funcao(double valor);
double funcaofi(double valor);
double funcaoDEV(double valor);

// Variáveis globais para guardar a expressão e as variáveis associadas
string expressaoGlobal, expressaoFI, expressaoDEV, continuar;
map<string, double> variaveisGlobais;

int main(void)
{
    int escolha;
    double precisao, b, a, k = 0, n, finicio, meio, fmeio, x1, x0, fxlinha, fx, raiz;

    cout << ("\n\nDefina a funcao:\n\nPara a relacoes trigonometricas:\ncosseno = cos(x)\nseno = sen(x)\ntangente = tg(x)\ncosecante = cosec(x)\nsecante = sec(x)\ncotangente = cotg(x)\n\n");
    // Obter a função do usuário
    function<void()> definirFuncao = inicia();
    function<void()> definirFuncaofi;
    function<void()> definirFuncaoDEV;

    definirFuncao(); // Configura a expressão e o valor de 'x' para as variáveis globais

    do
    {

        system("cls");
        cout << ("\n\nMenu de Metodos:\n\n");
        cout << ("1 - Bissexcao\n");
        cout << ("2 - MIL\n");
        cout << ("3 - Newton\n");
        cout << ("4 - Regula Falsi\n");
        cout << ("5 - Secante\n");
        cout << ("6 - Alterar funcao\n");
        cout << ("7 - Mostrar funcoes definidas\n");
        cout << ("10 - sair\n");

        cin >> escolha;

        system("cls");

        switch (escolha)
        {
        case 1:
            k = 0;
            cout << "Qual o primeiro valor? ";
            cin >> a;
            cout << "\n\nQual o segundo valor? ";
            cin >> b;
            cout << "\n\nQual a precisao? ";
            cin >> precisao;
            cout << "\n\nQual o numero maximo de interacoes? ";
            cin >> n;

            if (moduloDois(a, b) > precisao)
            {
                while (moduloDois(a, b) > precisao && k < n)
                {
                    k++;
                    finicio = funcao(a);
                    meio = (a + b) / 2;
                    fmeio = funcao(meio);
                    if (finicio * fmeio < 0)
                    {
                        b = meio;
                    }
                    else
                    {
                        a = meio;
                    }
                }
            }
            cout << "Valor final de 'a': " << a << "\nValor final de 'b': " << b << "\nValor final da raiz: " << meio;
            cout << "\nNumero total de interacoes: " << k;
            cout << "\n\nqualquer letra p/ voltar menu: ";
            cin >> continuar;
            break;

        case 2:
        {
            k = 1; // Inicializa contador de iterações
            definirFuncaofi = iniciaFI();
            definirFuncaofi(); // Chama a função de definição da função fi
            cout << "Qual a aproximacao inicial? ";
            cin >> x0;
            cout << "\n\nQual a precisao? ";
            cin >> precisao;
            cout << "\n\nQual o numero maximo de interacoes? ";
            cin >> n;

            x1 = x0;
            if (moduloUM(funcao(x0)) > precisao)
            {
                x1 = funcaofi(x0);
                while (moduloUM(funcao(x1)) > precisao && k < n && moduloDois(funcao(x0), funcao(x1)) > precisao)
                {
                    x0 = x1;
                    x1 = funcaofi(x0);
                    k++;
                }
            }

            cout << "Valor final de 'Xk': " << x1 << "\nValor de 'Xk-1': " << x0 << "\nValor final da raiz: " << funcaofi(x1);
            cout << "\nNumero total de interacoes: " << k;
            cout << "\n\nqualquer letra p/ voltar menu: ";
            cin >> continuar;
        }
        break;

        case 3:
            k = 1;
            definirFuncaoDEV = iniciaDEV();
            definirFuncaoDEV(); // Chama a função de definição da função fi
            cout << "Qual a aproximacao inicial? ";
            cin >> x0;
            cout << "\n\nQual a precisao? ";
            cin >> precisao;
            cout << "\n\nQual o numero maximo de interacoes? ";
            cin >> n;

            fx = funcao(x0);

            if (moduloUM(fx) > precisao)
            {
                fxlinha = funcaoDEV(x0);
                x1 = x0 - (fx / fxlinha);
                fx = funcao(x1);
                while (moduloUM(fx) > precisao && k <= n && moduloDois(x1, x0) > precisao)
                {
                    k++;
                    x0 = x1;
                    fxlinha = funcaoDEV(x0);
                    x1 = x0 - (fx / fxlinha);
                    fx = funcao(x1);
                }
                raiz = x1;
            }
            else
            {
                raiz = x0;
            }
            cout << "\nValor final da raiz: " << raiz;
            cout << "\nNumero total de interacoes: " << k;
            break;

        case 4:

            break;

        case 5:

            break;

        case 6:
            cout << ("\n\nDefina a funcao:\n\nPara a relacoes trigonometricas:\ncosseno = cos(x)\nseno = sen(x)\ntangente = tg(x)\ncosecante = cosec(x)\nsecante = sec(x)\ncotangente = cotg(x)\n\n");
            definirFuncao = inicia();
            definirFuncao(); // Configura a expressão e o valor de 'x' para as variáveis globais
            expressaoDEV.clear();
            expressaoFI.clear();
            cout << "\nAs funções interativa e derivada foram redefinidas.\n"
                 << endl;
            system("pause");
            break;

        case 7:
            if (!expressaoGlobal.empty())
                cout << "Funcao original: " << expressaoGlobal << endl;
            else
                cout << "Funcao original nao definida." << endl;
            if (!expressaoFI.empty())
                cout << "Funcao iterativa fi(x): " << expressaoFI << endl;
            else
                cout << "Funcao iterativa fi(x) nao definida." << endl;
            if (!expressaoDEV.empty())
                cout << "Funcao derivada: " << expressaoDEV << endl;
            else
                cout << "Funcao derivada nao definida." << endl;
            system("pause");
            break;

        case 10:
            exit(0);
            break;
        };
    } while (a != 10);
}

// Lógica de modulos
double moduloDois(double a, double b)
{
    return fabs(b - a);
}

double moduloUM(double valor)
{
    return fabs(valor);
}

// Função que avalia a expressão definida pela função original
double funcao(double valor)
{
    variaveisGlobais["x"] = valor;                          // Atualiza o valor de "x"
    cout << "Calculando função para x = " << valor << endl; // Debugging
    return avaliar(expressaoGlobal, variaveisGlobais);      // Faz a avaliação
}

double funcaofi(double valor)
{
    variaveisGlobais["x"] = valor;                            // Atualiza o valor de "x"
    cout << "Calculando funçãoFI para x = " << valor << endl; // Debugging
    return avaliar(expressaoFI, variaveisGlobais);            // Faz a avaliação
}

double funcaoDEV(double valor)
{
    variaveisGlobais["x"] = valor;                             // Atualiza o valor de "x"
    cout << "Calculando funçãoDEV para x = " << valor << endl; // Debugging
    return avaliar(expressaoDEV, variaveisGlobais);            // Faz a avaliação
}

// Função para salvar a função matemática
function<void()> inicia()
{
    cout << "Digite a expressao (use 'x' como variavel): ";
    getline(cin >> ws, expressaoGlobal); // Armazena a função

    double x;
    variaveisGlobais["x"] = x;   // define "x"
    variaveisGlobais["e"] = M_E; // Constante de Euler

    return []()
    {
        cout << "Expressão definida com sucesso!" << endl;
        cout << "\nqualquer letra p/ voltar menu: ";
        cin >> continuar;
    };
}

function<void()> iniciaFI()
{
    cout << "Digite a expressao fi(x) (use 'x' como variavel): ";
    getline(cin >> ws, expressaoFI); // Armazena a função iterativa fi(x)

    // Definições de variáveis
    variaveisGlobais["x"] = 0;   // Define 'x'
    variaveisGlobais["e"] = M_E; // Constante de Euler

    return []()
    {
        cout << "Expressão fi(x) definida com sucesso!" << endl;
        cout << "\nqualquer letra p/ voltar ao menu: ";
        cin >> continuar; // Espera por uma entrada para continuar
    };
}

function<void()> iniciaDEV()
{
    cout << "Digite a expressao derivada(x) (use 'x' como variavel): ";
    getline(cin >> ws, expressaoDEV); // Armazena a função iterativa fi(x)

    // Definições de variáveis
    variaveisGlobais["x"] = 0;   // Define 'x'
    variaveisGlobais["e"] = M_E; // Constante de Euler

    return []()
    {
        cout << "Expressão derivada(x) definida com sucesso!" << endl;
        cout << "\nqualquer letra p/ voltar ao menu: ";
        cin >> continuar; // Espera por uma entrada para continuar
    };
}

// Lógica de leitura de String

bool ehOperador(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int prioridade(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double aplicarOperacao(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            cout << "Erro: divisão por zero." << endl;
            return NAN; // Retorna em caso de divisão por zero
        }
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0; // não é pra acontecer kkkkk
    }
}

// Avalia a expressão matemática
double avaliar(const string &expressao, const map<string, double> &variaveis)
{
    stack<double> valores;  // Pilha para valores numéricos
    stack<char> operadores; // Pilha para operadores
    string func;            // Armazena o nome da função
    double valor;           // Armazena valores temporários
    size_t j, k;            // Índices auxiliares

    for (size_t i = 0; i < expressao.length(); i++)
    {
        if (isspace(expressao[i]))
        {
            continue; // Ignora espaços
        }

        // Lidar com números negativos ou números em geral
        if (expressao[i] == '-' && (i == 0 || ehOperador(expressao[i - 1]) || expressao[i - 1] == '('))
        {
            i++;
            if (isalpha(expressao[i]))
            { // Verifica se é um caracter (não número)
                j = i;
                while (j < expressao.length() && isalpha(expressao[j]))
                    j++;
                func = expressao.substr(i, j - i);
                cout << "Acessando a função: " << func << endl; // onde ta errado senhor cristo

                // Adiciona o valor negativo da função a pilha
                valores.push(-variaveis.at(func));
                i = j - 1;
            }
            else
            { // Verifica se é um número
                j = i;
                while (j < expressao.length() && (isdigit(expressao[j]) || expressao[j] == '.'))
                {
                    j++;
                }
                valor = stod(expressao.substr(i, j - i)) * -1; // Converte para double e aplica o sinal negativo
                valores.push(valor);
                i = j - 1;
            }
        }

        // Lidar com números
        else if (isdigit(expressao[i]) || expressao[i] == '.')
        {
            j = i;
            while (j < expressao.length() && (isdigit(expressao[j]) || expressao[j] == '.'))
            {
                j++;
            }
            valor = stod(expressao.substr(i, j - i));
            valores.push(valor);
            i = j - 1;
        }

        // Lida com funções
        else if (isalpha(expressao[i]))
            {
                j = i;
                while (j < expressao.length() && isalpha(expressao[j]))
                    j++;
                func = expressao.substr(i, j - i);

                // Verifica se é uma função válida
                if (func == "cos" || func == "sen" || func == "tg" || func == "sec" || func == "cosec" || func == "cotg" || func == "ln" || func == "log")
                {
                    i = j;
                    while (isspace(expressao[i]))
                        i++;
                    if (expressao[i] == '(')
                    {
                        int count = 1;
                        k = i + 1;
                        while (k < expressao.length() && count > 0)
                        {
                            if (expressao[k] == '(')
                                count++;
                            if (expressao[k] == ')')
                                count--;
                            k++;
                        }
                        double argumento = avaliar(expressao.substr(i + 1, k - i - 2), variaveis); // Avalia o argumento da função

                        // Verifica se o argumento é válido antes de chamar a função
                        if (func == "cos")
                            valores.push(cos(argumento));
                        else if (func == "sen")
                            valores.push(sin(argumento));
                        else if (func == "tg")
                            valores.push(tan(argumento));
                        else if (func == "sec")
                            valores.push(1 / cos(argumento));
                        else if (func == "cosec")
                        {
                            if (sin(argumento) == 0)
                            {
                                cout << "Erro: divisão por zero na função cosecante!" << endl;
                                return NAN;
                            }
                            valores.push(1 / sin(argumento));
                        }
                        else if (func == "cotg")
                        {
                            if (tan(argumento) == 0)
                            {
                                cout << "Erro: divisão por zero na função cotangente!" << endl;
                                return NAN;
                            }
                            valores.push(1 / tan(argumento));
                        }
                        else if (func == "ln")
                        {
                            if (argumento <= 0)
                            {
                                cout << "Erro: log de nnumero negativo!" << endl;
                                return NAN;
                            }
                            valores.push(log(argumento));
                        }
                        else if (func == "log")
                        {
                            if (argumento <= 0)
                            {
                                cout << "Erro: log de nnumero negativo!" << endl;
                                return NAN;
                            }
                            valores.push(log10(argumento));
                        }
                        i = k - 1;
                    }
                }
                else
                {
                    // Verifica se a variável está no mapa
                    cout << "Acessando a variável: " << func << endl; // Debug
                    if (variaveis.find(func) != variaveis.end())
                    {
                        valores.push(variaveis.at(func));
                    }
                    else
                    {
                        cout << "Erro: A variável " << func << " não está definida no mapa!" << endl;
                        return NAN; // Tratamento de erro
                    }
                    i = j - 1;
                }
            }

            // Empilha parênteses de abertura
            else if (expressao[i] == '(')
            {
                operadores.push(expressao[i]);
            }

            // Resolve operações até encontrar o parênteses de abertura
            else if (expressao[i] == ')')
            {
                while (!operadores.empty() && operadores.top() != '(')
                {
                    double valor2 = valores.top();
                    valores.pop();
                    double valor1 = valores.top();
                    valores.pop();
                    char op = operadores.top();
                    operadores.pop();
                    valores.push(aplicarOperacao(valor1, valor2, op));
                }
                operadores.pop(); // Remove o parênteses de abertura
            }

            // Lidar com operadores
            else if (ehOperador(expressao[i]))
            {
                while (!operadores.empty() && prioridade(operadores.top()) >= prioridade(expressao[i]))
                {
                    double valor2 = valores.top();
                    valores.pop();
                    double valor1 = valores.top();
                    valores.pop();
                    char op = operadores.top();
                    operadores.pop();
                    valores.push(aplicarOperacao(valor1, valor2, op));
                }
                operadores.push(expressao[i]); // Empilha o operador atual
            }
    }

    // Resolve todas as operações restantes (na teoria pelo menos)
    while (!operadores.empty())
    {
        double valor2 = valores.top();
        valores.pop();
        double valor1 = valores.top();
        valores.pop();
        char op = operadores.top();
        operadores.pop();
        valores.push(aplicarOperacao(valor1, valor2, op));
    }

    return valores.top(); // Retorna o resultado final (se tudo der certo amém)
}