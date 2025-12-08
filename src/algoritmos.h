#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "leitura.h"

// Estrutura para armazenar métricas de desempenho
typedef struct {
    long comparacoes;
    long trocas;
    long memoria;
} Metricas;

// Protótipos das funções de ordenação
char ehAcentuado(unsigned char c1, unsigned char c2);
void normalizar(char *str);
void countingSortChar(Jogador *v, int n, int pos, Metricas *m);
void radixSortNomes(Jogador *v, int n, Metricas *m);

#endif // ALGORITMOS_H
