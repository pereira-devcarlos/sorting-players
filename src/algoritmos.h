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
int compararNomes(const char *a, const char *b, Metricas *m);
void bubbleSort(Jogador *v, int n, Metricas *m);
void countingSortChar(Jogador *v, int n, int pos, Metricas *m);
void radixSortNomes(Jogador *v, int n, Metricas *m);

#endif // ALGORITMOS_H
