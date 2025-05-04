#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int raizes(float a, float b, float c, float *x1, float *x2)
{
    float delta = (b*b) - (4*a*c);
    if(delta < 0)
    {
        return 0; //retornando que nao ha raizes reais
    }

    b = b*-1;

    *x1 = (b + sqrt(delta))/(2*a);
    
    *x2 = (b - sqrt(delta))/(2*a);
   

    return 1; //retornando que operacao foi um sucesso
}

int main()
{
    float *x1 = malloc(sizeof(float));
    float *x2 = malloc(sizeof(float));
    float a = 2, b = -4, c = -6;

    if(!raizes(a, b, c, x1, x2))
    {
        printf("não há raízes reais!\n");
    }
    else
    {
        printf("x1 = %.2f,   ", *x1);
        printf("x2 = %.2f\n", *x2);
    }

    if(x1)
    {
        free(x1);
    }

    if(x2)
    {
        free(x2);
    }

    return 0;
}