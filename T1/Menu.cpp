#include <iostream>
#include "LeitorString.h"

using namespace std;

double moduloUM(double a);

double moduloDOIS(double a, double b);

void M_Bissexcao(string funcao);

void M_MIL(string funcao);

void M_Newton(string funcao);

void M_RegulaFalsi(string funcao);

void M_Secante(string funcao);

int main(){
    string funcao;
    cout << "Cosseno = cos\nSeno = sin\nTangente = tg\nCossecante = cosec\nSecante = sec\nCotangente = cotg\n\n";
    cout << "Digite a funcao (use 'x' como variavel): ";
    getline(cin, funcao);

    bool continua = true;
    int opcao;
    while(continua == true){
        cout << "\n\nQual metodo deseja aplicar? \n1-Bissexcao, 2-MIL, 3-Newton, 4-Regula Falsi, 5-Secante\n";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            M_Bissexcao(funcao);
            break;
        case 2:
            M_MIL(funcao);
            break;
        case 3:
            M_Newton(funcao);
            break;
        case 4:
            M_RegulaFalsi(funcao);
            break;
        case 5:
            M_Secante(funcao);
            break;    
        default:
            cout << "\n\nOpcao invalida, codigo será encerrado!";
            continua = false;
            break;
        }
    }

    return 0;
}

double moduloUM(double a)
{  
    if (a < 0)
    {
        return (a * (-1));
    }
    else
    {
        return a;
    }
}

double moduloDOIS(double a, double b)
{
    if (a - b < 0)
    {
        return ((a - b) * (-1));
    }
    else
    {
        return a - b;
    }
}

void M_Bissexcao(string funcao){
    double precisao, b, a, k = 0, n, finicio, meio, fmeio;
    cout << "Qual o primeiro valor? ";
    cin >> a;
    cout << "\n\nQual o segundo valor? ";
    cin >> b;
    cout << "\n\nQual a precisao? ";
    cin >> precisao;
    cout << "\n\nQual o numero maximo de interacoes? ";
    cin >> n;
    
    if (moduloDOIS(a,b) > precisao)
    {
        while (moduloDOIS(a,b) > precisao && k<n)
        {
            k++;
            finicio = avaliaFuncao(funcao, a);
            meio = (a+b)/2;
            fmeio = avaliaFuncao(funcao, meio);
            if (finicio*fmeio < 0)
            {
                b = meio;
            }
            else{
                a = meio;
            }
            cout << "\n\n\nValor de 'a': " << a << "\nValor de 'b': " << b << "\nValor da raiz: " << meio;
            cout << "\nNumero da interacao: " << k;
        }
    }
    cout << "\n\n\nValor final de 'a': " << a << "\nValor final de 'b': " << b << "\nValor final da raiz: " << meio;
    cout << "\nNumero total de interacoes: " << k;
}

void M_MIL(string funcao){
    string funcaofi;
    double precisao, x1 = 0.0, x0 = -1, k = 1, n;
    cout << "Qual a aproximacao inicial? ";
    cin >> x0;
    cout << "\n\nQual a precisao? ";
    cin >> precisao;
    cout << "\n\nQual o numero maximo de interacoes? ";
    cin >> n;
    cout << "\n\nDigite a funcao (use 'x' como variavel): ";
    cin.ignore();
    getline(cin, funcaofi);
    x1 = x0;
    if (moduloUM(avaliaFuncao(funcao, x0)) > precisao)
    {
        x1 = avaliaFuncao(funcaofi, x0);
        while (moduloUM(avaliaFuncao(funcao, x1)) > precisao && k<n && moduloDOIS(avaliaFuncao(funcao, x0), avaliaFuncao(funcao, x1)) > precisao)
        {
            x0 = x1;
            x1 = avaliaFuncao(funcaofi, x0);
            k++;
        }
    }
    cout << "Valor final de 'Xk': " << x1 << "\nValor de 'Xk-1': " << x0 << "\nValor final da raiz: " << avaliaFuncao(funcaofi, x1);
    cout << "\nNumero total de interacoes: " << k;
}

void M_Newton(string funcao){
    string funcaoDEV;
    double precisao, x1 = 0.0, x0, fx, fxlinha, raiz;
    int k = 1, n;
    cout << "Qual a aproximacao inicial? ";
    cin >> x0;
    cout << "\n\nQual a precisao? ";
    cin >> precisao;
    cout << "\n\nQual o numero maximo de interacoes? ";
    cin >> n;
    cout << "\n\nDigite a funcao (use 'x' como variavel): ";
    cin.ignore();
    getline(cin, funcaoDEV);

    fx = avaliaFuncao(funcao, x0);

    if (moduloUM(fx) > precisao)
    {
        fxlinha = avaliaFuncao(funcaoDEV, x0);
        x1 = x0 - (fx / fxlinha);
        cout << "\n\n\nValor raiz: " << x1;
        cout << "\nfuncao xk = " << fx << "      funcao xk-1 = " << fxlinha;
        cout << "\nNumero da interacoes: " << k;
        fx = avaliaFuncao(funcao, x1);
        while (moduloUM(avaliaFuncao(funcao, x1)) && k <= n && moduloDOIS(x1, x0) > precisao)
        {
            k++;
            x0 = x1;
            fxlinha = avaliaFuncao(funcaoDEV,x0);
            x1 = x0 - (fx / fxlinha);
            cout << "\n\n\nValor raiz: " << x1;
            cout << "\nfuncao xk = " << fx << "      funcao xk-1 = " << fxlinha;
            cout << "\nNumero da interacoes: " << k;
            fx = avaliaFuncao(funcao, x1);
        }
        raiz = x1;
    }
    else
    {
        raiz = x0;
    }
    cout << "\n\n\nValor final da raiz: " << raiz;
    cout << "\nNumero total de interacoes: " << k;
}

void M_RegulaFalsi(string funcao){
    double precisao1, precisao2, b, a, raiz, x, m;
    int k = 1, n;
    cout << "Qual o valor de a? ";
    cin >> a;
    cout << "Qual o valor de b? ";
    cin >> b;
    cout << "Qual a precisao 1? ";
    cin >> precisao1;
    cout << "Qual a precisao 2? ";
    cin >> precisao2;
    cout << "Qual o numero maximo de interacoes? ";
    cin >> n;

    if (moduloUM(avaliaFuncao(funcao, a)) < precisao2 || moduloUM(avaliaFuncao(funcao, b)) < precisao2 || moduloDOIS(b, a) < precisao1)
    {
        raiz = b;
    }
    else
    {
        m = avaliaFuncao(funcao, a);
        x = (a * avaliaFuncao(funcao, b) - b * avaliaFuncao(funcao, a)) / (avaliaFuncao(funcao, b) - avaliaFuncao(funcao, a));
        while (moduloUM(avaliaFuncao(funcao, x)) > precisao2 && k < n && moduloDOIS(b, a) > precisao1)
        {
            cout << "\n\n\nNumero da interacoes: " << k << "\nfuncao x = " << avaliaFuncao(funcao, x) << "\nfuncao a = " << avaliaFuncao(funcao, a) << "    funcao b = " << avaliaFuncao(funcao, b);
            cout << "\na: " << a << "\nb: " << b << "\nm: " << m;
            k++;
            if (m * avaliaFuncao(funcao, x) > 0)
            {
                cout << "\n\nsubstituiu a na interacao k=" << k-1;
                a = x;
            }
            else
            {
                cout << "\n\nsubstituiu b na interacao k=" << k-1;
                b = x;
            }
            m = avaliaFuncao(funcao, a);
            x = (a * avaliaFuncao(funcao, b) - b * avaliaFuncao(funcao, a)) / (avaliaFuncao(funcao, b) - avaliaFuncao(funcao, a));
        }
        m = avaliaFuncao(funcao, x);
        raiz = x;
    }

    cout << "\n\n\nValor final da raiz: " << raiz;
    cout << "\nNumero da interacoes: " << k << "\nfuncao x = " << avaliaFuncao(funcao, x) << "\nfuncao a = " << avaliaFuncao(funcao, a) << "    funcao b = " << avaliaFuncao(funcao, b);
    cout << "\nNumero total de interacoes: " << k;
    cout << "\na: " << a << "\nb: " << b << "\nm: " << m;
}

void M_Secante(string funcao){
    double precisao, x1, x0, x2, raiz, funck, funckneg;
    int k = 0, n;
    cout << "Qual o valor de x0? ";
    cin >> x0;
    cout << "Qual o valor de x1? ";
    cin >> x1;
    cout << "Qual a precisao? ";
    cin >> precisao;
    cout << "Qual o numero maximo de interacoes? ";
    cin >> n;

    if (moduloUM(avaliaFuncao(funcao, x0)) > precisao)
    {
        if (moduloUM(avaliaFuncao(funcao, x1)) < precisao && moduloDOIS(x1, x0) < precisao)
        {
            raiz = x1;
        }
        else
        {
            while (moduloUM(avaliaFuncao(funcao, x1)) > precisao && k < n && moduloDOIS(x1, x0) > precisao)
            {
                k++;
                funck = avaliaFuncao(funcao, x1);
                funckneg = avaliaFuncao(funcao, x0);
                x2 = x1 - (avaliaFuncao(funcao, x1) * (x1 - x0)) / (avaliaFuncao(funcao, x1) - avaliaFuncao(funcao, x0));
                cout << "\n\n\nfuncao k: " << funck << "\nfuncao k-1: " << funckneg << "\n(k) - (k-1) = " << x1-x0;
                cout << "\nInteracao: " << k << "\nx0: " << x0 << "\nx1: " << x1 << "\nx2: " << x2;
                x0 = x1;
                x1 = x2;
            }
            raiz = x2;
        }
    }
    else
    {
        raiz = x0;
    }

    cout << "\n\n\nValor final da raiz: " << raiz;
    cout << "\nNumero total de interacoes: " << k;
    cout << "\nx0: " << x0 << "\nx1: " << x1 << "\nx2: " << x2;
}
