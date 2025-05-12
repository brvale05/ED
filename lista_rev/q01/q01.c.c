#include <stdio.h>
#include <stdlib.h>
#define PI 3.14

void calc_esfera(float r, float *area, float *volume)
{
    *volume = (4*PI*r*r*r)/(float)3;
    *area = 4*PI*r*r;

    printf("\narea = %.2f     ", *(area));
    printf("volume = %.2f\n", *(volume));
}

int main()
{
    float *area = malloc(sizeof(float));
    float *volume = malloc(sizeof(float));

    float r = 10;

    calc_esfera(r, area, volume);

    if(area)
    {
        free(area);
    }
    
    if(volume)
    {
        free(volume);
    }

    return 0;
    
}