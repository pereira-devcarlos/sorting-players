#include <string.h>
#include <stdlib.h>
#include "algoritmos.h"

#define MAX 256   // máx. valores de caracteres

// Counting Sort para ordenar jogadores pelo caractere de posição 'pos'
static void countingSortChar(Jogador *v, int n, int pos, Metricas *m){
    int count[MAX] = {0};
    Jogador *saida = malloc(n * sizeof(Jogador));

    m->memoria += n * sizeof(Jogador);

    // Contagem de frequência
    for (int i = 0; i < n; i++) {
        unsigned char c;
        if (pos < strlen(v[i].nome))
            c = (unsigned char)v[i].nome[pos];
        else
            c = 0; // strings menores recebem prioridade

        count[c]++;
        m->comparacoes++;
    }

    // Transformar count em prefix sum
    for (int i = 1; i < MAX; i++)
        count[i] += count[i - 1];

    // Construir saída (ordenação estável)
    for (int i = n - 1; i >= 0; i--) {
        unsigned char c;
        if (pos < strlen(v[i].nome))
            c = (unsigned char)v[i].nome[pos];
        else
            c = 0;

        count[c]--;
        saida[count[c]] = v[i];
        m->trocas++;
    }

    // Copiar de volta
    for (int i = 0; i < n; i++) {
        v[i] = saida[i];
    }

    free(saida);
}

// RADIX SORT — ordenando da direita para a esquerda
void radixSortNomes(Jogador *v, int n, Metricas *m)
{
    m->comparacoes = 0;
    m->trocas = 0;
    m->memoria = 0;

    // 1. Descobrir o maior tamanho de nome
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(v[i].nome);
        if (len > maxLen)
            maxLen = len;
        m->comparacoes++;
    }

    // 2. Rodar counting sort para cada posição de caractere
    // começando do último caractere
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortChar(v, n, pos, m);
    }
}
