#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dicionario *cria_dicionario()
{
    Dicionario *d = malloc(sizeof(Dicionario));
    d->tamanho_usado = 0;
    d->tamanho_alocado = 10;
    d->vetor_palavra = calloc(d->tamanho_alocado, sizeof(Palavra_dicionario));
    return d;
}

void redimensionar_dicionario(Dicionario *d)
{
    if (d->tamanho_usado == d->tamanho_alocado)
    {
        d->tamanho_alocado *= 2;
        d->vetor_palavra = realloc(d->vetor_palavra,
                                   d->tamanho_alocado * sizeof(Palavra_dicionario));
        if (!d->vetor_palavra)
        {
            printf("Erro ao realocar memoria\n");
            exit(1);
        }
    }
}

void atualizar_ocorrencia(Palavra_dicionario *p, int num_linha)
{
    Ocorrencia *at = p->ocorrencia;
    Ocorrencia *ant = NULL;

    while (at)
    {
        if (at->linha == num_linha)
        {
            at->qtd_linha++;
            return;
        }
        ant = at;
        at = at->prox_linha;
    }

    Ocorrencia *novo = malloc(sizeof(Ocorrencia));
    novo->linha = num_linha;
    novo->qtd_linha = 1;
    novo->prox_linha = NULL;

    if (!ant)
        p->ocorrencia = novo;
    else
        ant->prox_linha = novo;
}

void inserir_dicionario(Dicionario *d, char *palavra, int num_linha)
{
    int i;
    for (i = 0; i < d->tamanho_usado; i++)
    {
        int cmp = strcmp(palavra, d->vetor_palavra[i].palavra);
        if (cmp == 0)
        {
            atualizar_ocorrencia(&d->vetor_palavra[i], num_linha);
            return;
        }
        if (cmp < 0)
            break;
    }

    redimensionar_dicionario(d);

    for (int j = d->tamanho_usado; j > i; j--)
        d->vetor_palavra[j] = d->vetor_palavra[j - 1];

    strcpy(d->vetor_palavra[i].palavra, palavra);
    d->vetor_palavra[i].ocorrencia = NULL;
    atualizar_ocorrencia(&d->vetor_palavra[i], num_linha);
    d->tamanho_usado++;
}

void imprimir_dicionario(Dicionario *d)
{
    for (int i = 0; i < d->tamanho_usado; i++)
    {
        printf("%s : ", d->vetor_palavra[i].palavra);

        Ocorrencia *aux = d->vetor_palavra[i].ocorrencia;
        while (aux)
        {
            printf("(%d, %d)", aux->linha, aux->qtd_linha);
            if (aux->prox_linha)
                printf(", ");
            aux = aux->prox_linha;
        }
        printf("\n");
    }
}

Palavra_dicionario *buscar_palavra(Dicionario *d, char *palavra)
{
    int ini = 0, fim = d->tamanho_usado - 1;

    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(palavra, d->vetor_palavra[meio].palavra);

        if (cmp == 0)
            return &d->vetor_palavra[meio];
        if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return NULL;
}

void remover_palavra(Dicionario *d, char *palavra)
{
    int i;
    for (i = 0; i < d->tamanho_usado; i++)
    {
        if (strcmp(d->vetor_palavra[i].palavra, palavra) == 0)
            break;
    }
    if (i == d->tamanho_usado)
    {
        printf("Palavra nao encontrada.\n");
        return;
    }

    Ocorrencia *aux = d->vetor_palavra[i].ocorrencia;
    while (aux)
    {
        Ocorrencia *del = aux;
        aux = aux->prox_linha;
        free(del);
    }

    for (int j = i; j < d->tamanho_usado - 1; j++)
        d->vetor_palavra[j] = d->vetor_palavra[j + 1];

    d->tamanho_usado--;

    printf("Palavra '%s' removida.\n", palavra);
}

char *palavra_mais_frequente(Dicionario *d)
{
    int max = 0;
    char *res = NULL;

    for (int i = 0; i < d->tamanho_usado; i++)
    {
        int soma = 0;
        Ocorrencia *aux = d->vetor_palavra[i].ocorrencia;
        while (aux)
        {
            soma += aux->qtd_linha;
            aux = aux->prox_linha;
        }
        if (soma > max)
        {
            max = soma;
            res = d->vetor_palavra[i].palavra;
        }
    }
    return res;
}

void liberar_dicionario(Dicionario *d)
{
    for (int i = 0; i < d->tamanho_usado; i++)
    {
        Ocorrencia *aux = d->vetor_palavra[i].ocorrencia;
        while (aux)
        {
            Ocorrencia *tmp = aux;
            aux = aux->prox_linha;
            free(tmp);
        }
    }
    free(d->vetor_palavra);
    free(d);
}