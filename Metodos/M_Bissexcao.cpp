#include <iostream>
#include <math.h>
using namespace std;

double modulo(double a, double b);
double funcao(double valor);

int main(){
    double precisao, b, a, k = 0, n, finicio, meio, fmeio;
    cout << "Qual o primeiro valor? ";
    cin >> a;
    cout << "\n\nQual o segundo valor? ";
    cin >> b;
    cout << "\n\nQual a precisao? ";
    cin >> precisao;
    cout << "\n\nQual o numero maximo de interacoes? ";
    cin >> n;
    
    if (modulo(a,b) > precisao)
    {
        while (modulo(a,b) > precisao && k<n)
        {
            k++;
            finicio = funcao(a);
            meio = (a+b)/2;
            fmeio = funcao(meio);
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

double modulo(double a, double b){
    if (b-a < 0)
    {
        return ((b-a)*(-1));
    }
    else{
        return b-a;
    }
}

double funcao(double valor)
{
    return (2 * (pow(valor, 3)) + 5 * (valor * valor) - sin(valor) - 30);
}
