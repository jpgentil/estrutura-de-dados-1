#include <stdio.h>
#include <math.h>

typedef struct ponto
{
    float x;
    float y;
} Ponto;

typedef struct circulo
{
    Ponto centro;
    float raio;

} Circulo;

int ponto_no_circulo(Ponto p, Circulo c)
{
    float distancia = sqrt((p.x - c.centro.x) * (p.x - c.centro.x) + (p.y - c.centro.y) * (p.y - c.centro.y));
    return distancia <= c.raio;
}

int main()
{
    Ponto p = {2, 3};
    Circulo c = {{0, 0}, 5};

    if (ponto_no_circulo)
        printf("O ponto esta no circulo");
    else
        printf("O ponto nao esta no circulo");
}   