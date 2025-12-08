#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "algoritmos.h"

#define MAX 256   // máx. valores de caracteres

// Função para mapear caracteres UTF-8 acentuados para suas versões sem acento
char ehAcentuado(unsigned char c1, unsigned char c2) {
    if (c1 == 0xC3) {
        switch (c2) {
            // Letras minúsculas
            case 0xA1: case 0xA0: case 0xA2: case 0xA3: return 'a';  // á à â ã
            case 0xA9: case 0xA8: case 0xAA: return 'e';             // é è ê
            case 0xAD: case 0xAC: case 0xAE: return 'i';             // í ì î
            case 0xB3: case 0xB2: case 0xB4: case 0xB5: return 'o';  // ó ò ô õ
            case 0xBA: case 0xB9: case 0xBB: return 'u';             // ú ù û
            case 0xA7: return 'c';                                   // ç

            // Letras maiúsculas
            case 0x81: case 0x80: case 0x82: case 0x83: return 'a';  // Á À Â Ã
            case 0x89: case 0x88: case 0x8A: return 'e';             // É È Ê
            case 0x8D: case 0x8C: case 0x8E: return 'i';             // Í Ì Î
            case 0x93: case 0x92: case 0x94: case 0x95: return 'o';  // Ó Ò Ô Õ
            case 0x9A: case 0x99: case 0x9B: return 'u';             // Ú Ù Û
            case 0x87: return 'c';                                   // Ç
        }
    }

    return 0; // Não é acentuado tratado
}

// Função para normalizar uma string (remover acentos, converter para minúsculas, remover não-alnum)
void normalizar(char *str) {
    char temp[256];
    int i = 0, j = 0;

    while (str[i]) {
        // Pega o caractere atual
        unsigned char c = str[i];

        if (c < 128) {
            // Caractere ASCII sem acentuação
            if (isalnum(c)) {
                temp[j++] = tolower(c);
            }
            i++;
        } else {
            // Provavelmente início de um caractere UTF-8 multibyte (acentuado)
            unsigned char c1 = str[i];
            unsigned char c2 = str[i + 1];

            char substituto = ehAcentuado(c1, c2);
            if (substituto) {
                temp[j++] = substituto;
            }
            i += 2; // Pular o caractere UTF-8
        }
    }

    // Finaliza a string normalizada 
    temp[j] = '\0';
    strcpy(str, temp);
}

// Counting Sort para ordenar jogadores pelo caractere de posição 'pos'
void countingSortChar(Jogador *v, int n, int pos, Metricas *m){
    int count[MAX] = {0};
    Jogador *saida = malloc(n * sizeof(Jogador));

    m->memoria += n * sizeof(Jogador);

    // Contagem de frequência
    for (int i = 0; i < n; i++) {
        unsigned char c;
        if (pos < strlen(v[i].nome_normalizado))
            c = (unsigned char)v[i].nome_normalizado[pos];
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
        if (pos < strlen(v[i].nome_normalizado))
            c = (unsigned char)v[i].nome_normalizado[pos];
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
        int len = strlen(v[i].nome_normalizado);
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
