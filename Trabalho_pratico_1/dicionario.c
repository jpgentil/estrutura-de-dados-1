#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dicionario *cria_dicionario()
{
    Dicionario *d = (Dicionario *)malloc(sizeof(Dicionario));
    d->tamanho_usado = 0;
    d->tamanho_alocado = 10;
    d->vetor_palavra = (Palavra_dicionario *)calloc(d->tamanho_alocado, sizeof(Palavra_dicionario));
    return d;
}

void inserir_dicionario(Dicionario *d, char *palavra, int num_linha)
{
    int i;
    int comparacao;

    for (i = 0; i < d->tamanho_usado; i++)
    {
        comparacao = strcmp(palavra, d->vetor_palavra[i].palavra);

        if (comparacao == 0)
        {
            atualizar_ocorrencia(&(d->vetor_palavra[i]), num_linha);
            return;
        }
        else if (comparacao < 0)
        {
            break;
        }
    }

    redimensionar_dicionario(d);

    for (int j = d->tamanho_usado; j > i; j--)
    {
        d->vetor_palavra[j] = d->vetor_palavra[j - 1];
    }

    strcpy(d->vetor_palavra[i].palavra, palavra);

    d->vetor_palavra[i].ocorrencia = NULL;

    atualizar_ocorrencia(&(d->vetor_palavra[i]), num_linha);

    d->tamanho_usado++;
}

void atualizar_ocorrencia(Palavra_dicionario *palavra, int num_linha)
{
    Ocorrencia *atual = palavra->ocorrencia;
    Ocorrencia *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->linha == num_linha)
        {
            atual->qtd_linha++;
            return;
        }

        anterior = atual;
        atual = atual->prox_linha;
    }

    Ocorrencia *novo_no = (Ocorrencia *)malloc(sizeof(Ocorrencia));
    if (novo_no == NULL)
    {
        printf("Erro: falha ao alocar memoria para Ocorrencia.\n");
        exit(EXIT_FAILURE);
    }

    novo_no->linha = num_linha;
    novo_no->qtd_linha = 1;
    novo_no->prox_linha = NULL;
    if (anterior == NULL)
    {
        palavra->ocorrencia = novo_no;
    }
    else
    {
        anterior->prox_linha = novo_no;
    }
}

void redimensionar_dicionario(Dicionario *d)
{
    if (d->tamanho_usado == d->tamanho_alocado)
    {
        int novo_tamanho = d->tamanho_alocado * 2;

        Palavra_dicionario *novo_vetor = (Palavra_dicionario *)realloc(
            d->vetor_palavra,
            novo_tamanho * sizeof(Palavra_dicionario));

        if (novo_vetor == NULL)
        {
            printf("Erro: falha ao realocar memoria para o Dicionario.\n");
            exit(EXIT_FAILURE);
        }

        d->vetor_palavra = novo_vetor;
        d->tamanho_alocado = novo_tamanho;
    }
}

void imprimir_dicionario(Dicionario *d)
{
    for (int i = 0; i < d->tamanho_usado; i++)
    {
        printf("%s : ", d->vetor_palavra[i].palavra);

        Ocorrencia *aux = d->vetor_palavra[i].ocorrencia;
        while (aux != NULL)
        {
            printf("(%d, %d)", aux->linha, aux->qtd_linha);

            if (aux->prox_linha != NULL)
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