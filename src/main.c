#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "algoritmos.h"

int main(int argc, char const *argv[]){
    // Testando função de carregar jogadores
    Jogador *jogadores = NULL;
    int n = carregar_jogadores("data/jogadores.csv", &jogadores);

    if (n <= 0) {
        printf("Erro ao carregar jogadores.\n");
        return 1;
    }

    
    for (int i = 0; i < n; i++) {
        printf("%s (%d)\n", jogadores[i].nome, jogadores[i].idade);
    }
    
    printf("Carregados %d jogadores.\n", n);
    
    free(jogadores);
    
    return 0;
}
