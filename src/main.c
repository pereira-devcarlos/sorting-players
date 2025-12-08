#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "algoritmos.h"

int main(int argc, char const *argv[]){
    // Testando função de carregar jogadores
    Jogador *jogadores = NULL;
    int n = carregar_jogadores("data/jogadores.csv", &jogadores);

    Metricas m;
    radixSortNomes(jogadores, n, &m);

    salvar_jogadores("data/saida.txt", jogadores, n);

    for(int i = 0; i < n; i++){
        printf("%s, %s, %s, %s, %d\n", jogadores[i].nome, jogadores[i].posicao, jogadores[i].naturalidade, jogadores[i].clube, jogadores[i].idade);
    }

    printf("Comparacoes: %ld\n", m.comparacoes);
    printf("Trocas: %ld\n", m.trocas);
    printf("Memoria: %ld\n", m.memoria);
    
    free(jogadores);

    return 0;
}
