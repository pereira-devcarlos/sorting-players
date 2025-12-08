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
void radixSortNomes(Jogador *v, int n, Metricas *m);

#endif // ALGORITMOS_H
