#include <iostream>
#include <math.h>
using namespace std;

double moduloDOIS(double a, double b);
double moduloUM(double a);
double funcao(double valor);

int main()
{
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

    if (moduloUM(funcao(a)) < precisao2 || moduloUM(funcao(b)) < precisao2 || moduloDOIS(b, a) < precisao1)
    {
        raiz = b;
    }
    else
    {
        m = funcao(a);
        x = (a * funcao(b) - b * funcao(a)) / (funcao(b) - funcao(a));
        while (moduloUM(funcao(x)) > precisao2 && k < n && moduloDOIS(b, a) > precisao1)
        {
            cout << "\n\n\nNumero da interacoes: " << k << "\nfuncao x = " << funcao(x) << "\nfuncao a = " << funcao(a) << "    funcao b = " << funcao(b);
            cout << "\na: " << a << "\nb: " << b << "\nm: " << m;
            k++;
            if (m * funcao(x) > 0)
            {
                cout << "\n\nsubstituiu a na interacao k=" << k-1;
                a = x;
            }
            else
            {
                cout << "\n\nsubstituiu b na interacao k=" << k-1;
                b = x;
            }
            m = funcao(a);
            x = (a * funcao(b) - b * funcao(a)) / (funcao(b) - funcao(a));
        }
        m = funcao(x);
        raiz = x;
    }

    cout << "\n\n\nValor final da raiz: " << raiz;
    cout << "\nNumero da interacoes: " << k << "\nfuncao x = " << funcao(x) << "\nfuncao a = " << funcao(a) << "    funcao b = " << funcao(b);
    cout << "\nNumero total de interacoes: " << k;
    cout << "\na: " << a << "\nb: " << b << "\nm: " << m;
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
