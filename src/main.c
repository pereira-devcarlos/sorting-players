#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "algoritmos.h"

int main(int argc, char const *argv[]){
    // Testando a estrutura de dados Jogador

    Jogador jogador;
    Jogador jogador2;

    // Atribuindo valores aos campos da struct
    strcpy(jogador.nome, "Cristiano Ronaldo");
    strcpy(jogador.posicao, "Atacante");
    strcpy(jogador.naturalidade, "Portugal");
    strcpy(jogador.clube, "Manchester United"); 
    jogador.idade = 39;

    strcpy(jogador2.nome, "Lionel Messi");
    strcpy(jogador2.posicao, "Atacante");
    strcpy(jogador2.naturalidade, "Argentina");
    strcpy(jogador2.clube, "Paris Saint-Germain");
    jogador2.idade = 36;

    // Exibindo os valores atribuídos
    printf("Nome: %s\n", jogador.nome);
    printf("Posição: %s\n", jogador.posicao);
    printf("Naturalidade: %s\n", jogador.naturalidade);
    printf("Clube: %s\n", jogador.clube);
    printf("Idade: %d\n", jogador.idade);
    printf("\n");

    printf("Nome: %s\n", jogador2.nome);
    printf("Posição: %s\n", jogador2.posicao);
    printf("Naturalidade: %s\n", jogador2.naturalidade);
    printf("Clube: %s\n", jogador2.clube);
    printf("Idade: %d\n", jogador2.idade);
    printf("\n");

    return 0;
}
