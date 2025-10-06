#include <stdio.h>
#include <stdlib.h>

typedef struct ponto
{
    float x;
    float y;
} ponto;

ponto ler_estrutura(ponto *p)
{
    printf("Digite as coordenadas do ponto\n");
    scanf("%f %f", &p->x, &p->y);
}

void imprimir_ponto(ponto *p)
{
    printf("Ponto no plano cartesiano: (%.2f,%.2f)\n", p->x, p->y);
}

int main(void)
{
    ponto p;
    ler_estrutura(&p); // Usando & temos um ponteiro que aponta para o endereço de memória do ponto p
    imprimir_ponto(&p);
    return 0;
}