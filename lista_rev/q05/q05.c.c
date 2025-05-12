#include <stdio.h>
#include <stdlib.h>

#define GRAU_MAX 2

double avalia (double* poli, int grau, double x)
{
    int i;

    double result = 0;

    for(i = 0; i <= grau; i++)
    {
        if(i < 1)
        {
            result += poli[i];
        }
        else
        {
            result += poli[i]*x;
            x *= x;
        }
    }

    return result;
}

int main()
{
    double *poli = malloc(sizeof(double)*(GRAU_MAX+1)); // aumento mais 1 no grau pois o tamanho do vetor de coeficientes eh sempre o grau + 1;
    double x = 2;

    for(int i = 0; i <= GRAU_MAX; i++)
    {
        *(poli+i) = i + 1;
    }

    double rslt = avalia(poli, GRAU_MAX, x);;
    printf("resultado = %.2lf\n", rslt);

    free(poli);

    return 0;

}