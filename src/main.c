#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leitura.h"
#include "algoritmos.h"

int main(int argc, char const *argv[]){
    // Testando função de carregar jogadores
    Jogador *jogadores = NULL;
    int n = carregar_jogadores("data/jogadores.csv", &jogadores);

    Metricas m = {0, 0, 0};
    clock_t inicio = clock();
    bubbleSort(jogadores, n, &m);
    clock_t fim = clock();

    double tempo_ms = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    salvar_jogadores("data/jogadores_ordenados.csv", jogadores, n);

    for(int i = 0; i < n; i++){
        printf("%s, %s, %s, %s, %d\n", jogadores[i].nome, jogadores[i].posicao, jogadores[i].naturalidade, jogadores[i].clube, jogadores[i].idade);
    }

    printf("Tempo de execucao: %.2f(ms)\n", tempo_ms);
    printf("Comparacoes: %ld\n", m.comparacoes);
    printf("Trocas: %ld\n", m.trocas);
    printf("Memoria: %ld(bytes)\n", m.memoria);
    
    free(jogadores);

    return 0;
}
