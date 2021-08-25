#include <iostream>
#include <list>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Termo
{
private:
    double constante;
    int expoente;

public:
    // Constructor
    Termo(double aValue, int expValue)
    {
        constante = aValue;
        expoente = expValue;
    }

    // Imprime no terminal o formato do Termo constantex^{expoente}
    void mostraTermo()
    {
        cout << constante << "x^" << expoente;
    }

    // Retorna o valor privado expoente
    int getExpoente()
    {
        return expoente;
    }

    // Soma a constante de um termo sendo adicionado ao polinomio
    void somaConstante(double a)
    {
        constante += a;
    }

    // Retorna o valor do termo sendo calculado
    long long calculaTermo(int value)
    {
        return (constante * (pow(value, expoente)));
    }

    // Operador que sera usado na funcao <list>.sort
    bool operator<(const Termo &t) const
    {
        return expoente < t.expoente;
    }
};

class Polinomio
{
private:
    int grauMaximo;
    list<Termo> pValues;

public:
    // Constructor
    Polinomio(int grauMaximoValue)
    {
        grauMaximo = grauMaximoValue;
    }

    void Mostra();
    long long Calcula(int value);
    int Add(double aValue, int expValue);
};

// Imprime na tela todo o polinomio, termo a termo.
void Polinomio::Mostra()
{

    cout << "P(x) = ";
    list<Termo>::iterator it;
    for (it = pValues.begin(); it != pValues.end(); ++it)
    {
        it->mostraTermo();
        if (next(it) != pValues.end())
            cout << " + ";
    }
    cout << endl
         << endl;
}

// Calcula o resultado do polinomio para um certo valor.
long long Polinomio::Calcula(int value)
{
    long long result = 0.0;

    list<Termo>::iterator it;
    for (it = pValues.begin(); it != pValues.end(); ++it)
    {
        result += it->calculaTermo(value);
    }

    return result;
}

/* 
Adiciona um novo termo ao polinomio. 
    . Se o termo ja existe suas constantes são somadas. 
    . Se o expoente do novo termo a ser adicionado for maior que o grauMaximo a 
    funcao termina. 
*/
int Polinomio::Add(double aValue, int expValue)
{

    // Checa se expValue eh maior que grauMaximo.
    if (expValue > grauMaximo)
        return 1;

    // Itera pela lista procurando por um termo com o valor do expoente igual ao de expValue.
    list<Termo>::iterator it;
    for (it = pValues.begin(); it != pValues.end(); ++it)
    {

        if (it->getExpoente() == expValue)
        {
            // Se encontrou um valor ele soma as constantes para esse termo.
            it->somaConstante(aValue);
            return 0;
        }
    }

    // Nao encontrou nenhum termo com o expoente igual a expValue, insere ele.
    pValues.push_back(Termo(aValue, expValue));

    // Organiza a lista de maneira crescente pelos valores dos expoentes
    pValues.sort();

    return 0;
}

int main()
{

    int maxRand = 100;
    int maxExpRand = 10;
    int maxCalculatorRand = 50;

    srand(time(NULL));

    // Criando um polinomio aleatorio
    int grauMaximo = 5;
    Polinomio p(grauMaximo);
    p.Mostra();

    // Tenta inserir 10 elementos no polinomio
    for (int i = 1; i < 10; i++)
    {
        int constantToBeAdded = (rand() % maxRand + 1);
        int expoenteToBeAdded = (rand() % maxExpRand + 1);

        cout << "Adicionando o termo " << constantToBeAdded << "x^" << expoenteToBeAdded << " no polinomio" << endl
             << endl;

        if (!p.Add(constantToBeAdded, expoenteToBeAdded))
            p.Mostra();
        else
            cout << "\tO Valor do expoente a ser adicionado (" << expoenteToBeAdded << ") eh maior que o permitido (" << grauMaximo << ")" << endl
                 << endl;
    }

    // Calcula o restulado para um valor x no polinomio
    int valueToBeCalculated = (rand() % maxCalculatorRand + 1);

    long long _valueCalculated = p.Calcula(valueToBeCalculated);
    p.Mostra();
    cout << "O valor de P(" << valueToBeCalculated << ") eh igual a: " << _valueCalculated << endl;

    return 0;
}
