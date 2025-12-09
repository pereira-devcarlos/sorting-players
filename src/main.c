#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leitura.h"
#include "algoritmos.h"

int main(int argc, char const *argv[]){
    // Verifica se o argumento de opção foi fornecido
    if (argc != 2) {
        printf("Uso correto: sorter.exe <opcao>\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Merge Sort\n");
        printf("3 - Radix Sort\n");
        return 1;
    }

    // Lê a opção do usuário
    int escolha = atoi(argv[1]);
    if (escolha < 1 || escolha > 3) {
        printf("Opcao invalida. Escolha:\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Merge Sort\n");
        printf("3 - Radix Sort\n");
        return 1;
    }
    
    // Carregar jogadores do arquivo
    Jogador *jogadores = NULL;
    int n = carregar_jogadores("data/jogadores.csv", &jogadores);
    if (n < 0) {
        printf("Erro ao carregar jogadores do arquivo.\n");
        return 1;
    }

    // Inicializar métricas
    Metricas m = {0, 0, 0};
    // Medir tempo de execução
    clock_t inicio = clock();

    switch (escolha) {
        case 1:
            // Bubble Sort - Ordenação Simples
            printf("Executando Bubble Sort...\n");
            bubbleSort(jogadores, n, &m);
            break;
        case 2:
            // Merge Sort - Ordenação Eficiente
            printf("Executando Merge Sort...\n");
            mergeSort(jogadores, 0, n - 1, &m);
            break;
        case 3:
            // Radix Sort - Ordenação Linear
            printf("Executando Radix Sort...\n");
            radixSortNomes(jogadores, n, &m);
            break;
        default:
            printf("Opcao invalida.\n");
            free(jogadores);
            return 1;
    }
    // Finalizar medição de tempo
    clock_t fim = clock();
    // Calcular tempo em milissegundos
    double tempo_ms = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    // Salvar jogadores ordenados em arquivo
    salvar_jogadores("data/jogadores_ordenados.csv", jogadores, n);

    const char *nomes[3] = {"Bubble Sort", "Merge Sort", "Radix Sort"};

    // Exibir jogadores ordenados
    printf("Jogadores ordenados por %s:\n", nomes[escolha - 1]);
    for(int i = 0; i < n; i++){
        printf("%s, %s, %s, %s, %d\n", jogadores[i].nome, jogadores[i].posicao, jogadores[i].naturalidade, jogadores[i].clube, jogadores[i].idade);
    }

    // Exibir métricas
    printf("\nMetricas de desempenho utilizando %s:\n", nomes[escolha - 1]);
    printf("Tempo de execucao: %.2f(ms)\n", tempo_ms);
    printf("Comparacoes: %ld\n", m.comparacoes);
    printf("Trocas: %ld\n", m.trocas);
    printf("Memoria: %ld(bytes)\n", m.memoria);
    
    // Liberar memória
    free(jogadores);
    return 0;
}
