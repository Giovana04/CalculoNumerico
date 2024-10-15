#include <iostream>
#include <math.h>
using namespace std;

double moduloDOIS(double a, double b);
double moduloUM(double a);
double funcao(double valor);
double funcaofi(double valor);

int main(){
    double precisao, x1 = 0.0, x0 = -1, k = 1, n;
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
        while (moduloUM(funcao(x1)) > precisao && k<n && moduloDOIS(funcao(x0), funcao(x1)) > precisao)
        {
            x0 = x1;
            x1 = funcaofi(x0);
            k++;
        }
    }
    cout << "Valor final de 'Xk': " << x1 << "\nValor de 'Xk-1': " << x0 << "\nValor final da raiz: " << funcaofi(x1);
    cout << "\nNumero total de interacoes: " << k;
}

double moduloUM(double a){
    if (a<0)
    {
        return (a*(-1));
    }
    else{
        return a;
    }
}

double moduloDOIS(double a, double b){
    if (a-b < 0)
    {
        return ((a-b)*(-1));
    }
    else{
        return a-b;
    }
}

double funcao(double valor){
    return(pow(valor, 2) - 0.9);
};

double funcaofi(double valor){
    return(pow(valor,2)+valor-0,9);
};