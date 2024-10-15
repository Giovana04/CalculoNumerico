#include <iostream>
#include <math.h>
using namespace std;

double moduloDOIS(double a, double b);
double moduloUM(double a);
double funcao(double valor);
double funcaoDEV(double valor);

int main()
{
    double precisao, x1 = 0.0, x0, fx, fxlinha, raiz;
    int k = 1, n;
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
        cout << "\n\n\nValor raiz: " << x1;
        cout << "\nfuncao xk = " << fx << "      funcao xk-1 = " << fxlinha;
        cout << "\nNumero da interacoes: " << k;
        fx = funcao(x1);
        while (moduloUM(funcao(x1)) && k <= n && moduloDOIS(x1, x0) > precisao)
        {
            k++;
            x0 = x1;
            fxlinha = funcaoDEV(x0);
            x1 = x0 - (fx / fxlinha);
            cout << "\n\n\nValor raiz: " << x1;
            cout << "\nfuncao xk = " << fx << "      funcao xk-1 = " << fxlinha;
            cout << "\nNumero da interacoes: " << k;
            fx = funcao(x1);
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

double funcao(double valor)
{
    return (2 * (pow(valor, 3)) + 5 * (valor * valor) - sin(valor) - 30);
}

double funcaoDEV(double valor)
{
    return (6 * (valor * valor) + 10 * valor - cos(valor));
}