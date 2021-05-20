#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10000
#define repeticoes 10

int mdc(int m, int n)
{
    int aux = 0;
    while(n>0)
    {
        aux = m%n;
        m=n;
        n=aux;
    }
    return(m);
}


int main()
{
	int m;
	int n;

	double somaTempo=0;
	clock_t tempoIni, tempoFim;

	for(int i=1000; i<TAM; i+=1000)
	{
		m = rand() % TAM;
		n = rand() % TAM;
		for(int j=0; j<repeticoes; j++)
		{
			tempoIni = clock();
			mdc( m , n );
			tempoFim = clock();

			somaTempo += (double)(tempoFim - tempoIni) / CLOCKS_PER_SEC;
		}
		printf("Mdc entre %d\te\t%d\teh:\t%0.10f\n", m,n,somaTempo);
	}

	return 0;
}
