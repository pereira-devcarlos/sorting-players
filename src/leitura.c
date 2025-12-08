#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "algoritmos.h"

int carregar_jogadores(const char *arquivo, Jogador **vetor) {
    // Abre o arquivo para leitura
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return -1;
    }

    char linha[256];
    int contador = 0;

    // Pula a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), fp);

    // Conta quantas linhas existem
    while (fgets(linha, sizeof(linha), fp)) {
        contador++;
    }

    // Volta para o começo (logo após o cabeçalho)
    fseek(fp, 0, SEEK_SET);
    fgets(linha, sizeof(linha), fp); // pula cabeçalho novamente

    // Aloca memória para o vetor
    *vetor = malloc(sizeof(Jogador) * contador);
    // Se não conseguiu alocar memória
    if (!(*vetor)) {
        printf("Erro ao alocar memoria\n");
        fclose(fp);
        return -1;
    }

    int i = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0; // remove o \n

        // Divide a linha em tokens separados por vírgula
        char *token = strtok(linha, ",");

        // Copia os dados para a estrutura Jogador
        strcpy((*vetor)[i].nome, token);
        strcpy((*vetor)[i].nome_normalizado, token); // copia o nome para normalizado
        normalizar((*vetor)[i].nome_normalizado);
        token = strtok(NULL, ",");

        strcpy((*vetor)[i].posicao, token);
        token = strtok(NULL, ",");

        strcpy((*vetor)[i].naturalidade, token);
        token = strtok(NULL, ",");

        strcpy((*vetor)[i].clube, token);
        token = strtok(NULL, ",");

        // Converte a idade de string para inteiro
        (*vetor)[i].idade = atoi(token);

        i++;
    }

    fclose(fp);
    return contador;
}

int salvar_jogadores(const char *arquivo, Jogador *vetor, int n) {
    FILE *fp = fopen(arquivo, "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s para escrita\n", arquivo);
        return -1;
    }

    // Escreve o cabeçalho
    fprintf(fp, "nome,posicao,naturalidade,clube,idade\n");

    // Escreve os dados dos jogadores
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s,%s,%s,%s,%d\n", vetor[i].nome, vetor[i].posicao, vetor[i].naturalidade, vetor[i].clube, vetor[i].idade);
    }

    fclose(fp);
    return 0;
}