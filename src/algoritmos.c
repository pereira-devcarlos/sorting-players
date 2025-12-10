#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "algoritmos.h"

#define MAX 256 // máx. valores de caracteres para counting sort

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

// Compara nomes normalizando antes
int compararNomes(const char *a, const char *b, Metricas *m){
    char na[128], nb[128];
    strcpy(na, a);
    strcpy(nb, b);

    // Normaliza os nomes antes de comparar
    normalizar(na);
    normalizar(nb);

    // Contabiliza a comparação
    m->comparacoes++;
    return strcmp(na, nb);
}

// BUBBLE SORT — ordenação simples para comparação
void bubbleSort(Jogador *v, int n, Metricas *m) {
    // Memória usada para a variável temporária
    m->memoria += sizeof(Jogador);

    // Para sinalizar se houver troca
    int trocou = 1; // 1 = true

    for (int i = 0; i < n - 1 && trocou; i++) {
        trocou = 0; // 0 = false

        for (int j = 0; j < n - i - 1; j++) {
            // Comparar nomes dos jogadores e trocar se necessário
            if (compararNomes(v[j].nome, v[j + 1].nome, m) > 0) {
                Jogador tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;

                // Contabiliza a troca
                m->trocas++;
                trocou = 1;
            }
        }
    }
}

// Função auxiliar para o Merge Sort
void merge(Jogador *v, int l, int m, int r, Metricas *met) {
    // Tamanhos dos subarrays
    int n1 = m - l + 1;
    int n2 = r - m;

    // Atualiza uso de memória
    met->memoria += (n1 + n2) * sizeof(Jogador);

    // Alocar memória para os subarrays
    Jogador *L = malloc(n1 * sizeof(Jogador));
    Jogador *R = malloc(n2 * sizeof(Jogador));

    // Copiar dados para os subarrays
    for (int i = 0; i < n1; i++) L[i] = v[l + i];
    for (int j = 0; j < n2; j++) R[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Mesclar os subarrays de volta em v[l..r]
    while (i < n1 && j < n2) {
        // Comparar e copiar o menor elemento
        if (compararNomes(L[i].nome, R[j].nome, met) <= 0) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
        }
        // Contabiliza a troca
        met->trocas++;
    }

    // Copiar os elementos restantes de L[], se houver
    while (i < n1) {
        v[k++] = L[i++];
        met->trocas++;
    }

    // Copiar os elementos restantes de R[], se houver
    while (j < n2) {
        v[k++] = R[j++];
        met->trocas++;
    }

    // Liberar memória alocada
    free(L);
    free(R);
}

// MERGE SORT — ordenação eficiente para comparação
void mergeSort(Jogador *v, int l, int r, Metricas *met) {
    if (l < r) {
        // Dividir o vetor em duas metades
        int m = (l + r) / 2;

        // Ordenar as duas metades
        mergeSort(v, l, m, met);
        mergeSort(v, m + 1, r, met);

        // Mesclar as metades ordenadas
        merge(v, l, m, r, met);
    }
}

// Counting Sort para ordenar jogadores pelos caracteres
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

// RADIX SORT — ordenando linearmente pelos nomes dos jogadores
void radixSortNomes(Jogador *v, int n, Metricas *m){
    m->comparacoes = 0;
    m->trocas = 0;
    m->memoria = 0;

    // 1. Descobrir o maior tamanho de nome
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(v[i].nome_normalizado);
        if (len > maxLen)
            maxLen = len;
    }

    // 2. Rodar counting sort para cada posição de caractere
    // começando do último caractere
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortChar(v, n, pos, m);
    }
}
