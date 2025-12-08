#ifndef LEITURA_H
#define LEITURA_H

// Definição da estrutura Jogador
typedef struct {
    char nome[100];
    char nome_normalizado[100];
    char posicao[50];
    char naturalidade[100];
    char clube[50];
    int idade;
} Jogador;

// Função para carregar jogadores a partir de um arquivo externo
int carregar_jogadores(const char *arquivo, Jogador **vetor);

// Função para salvar jogadores em um arquivo externo após ordenação
int salvar_jogadores(const char *arquivo, Jogador *vetor, int n);

#endif // LEITURA_H