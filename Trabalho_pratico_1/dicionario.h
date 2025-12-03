#define TAMANHO_MAX_PALAVRA 200

typedef struct ocorrencia
{
    int linha;
    int qtd_linha;
    struct ocorrencia *prox_linha;
} Ocorrencia;

typedef struct palavra_dicionario
{
    char palavra[TAMANHO_MAX_PALAVRA];
    Ocorrencia *ocorrencia;
} Palavra_dicionario;

typedef struct dicionario
{
    Palavra_dicionario *vetor_palavra;
    int tamanho_usado;
    int tamanho_alocado;
} Dicionario;

Dicionario *cria_dicionario();

void inserir_dicionario(Dicionario *, char *, int);

void redimensionar_dicionario(Dicionario *);

void atualizar_ocorrencia(Palavra_dicionario *, int);

void imprimir_dicionario(Dicionario *);
