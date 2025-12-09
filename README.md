# Sorting Players

Projeto desenvolvido para o Trabalho Prático 3 da disciplina Algoritmos e Estruturas de Dados II (AEDS II), da Universidade Federal de Alfenas (UNIFAL-MG).

O objetivo deste projeto é implementar e comparar três algoritmos de ordenação aplicados a um conjunto de jogadores lidos a partir de um arquivo CSV. A ordenação é realizada exclusivamente pelo campo Nome presente na struct de cada jogador.

---

## Objetivo do Projeto

O programa implementa três algoritmos de ordenação:

1. Método simples de ordenação: Bubble Sort.

2. Método ótimo de ordenação: Merge Sort.

3. Método de ordenação em tempo linear: Radix Sort.

O programa também realiza a medição de desempenho, incluindo:

- Tempo de execução (ms)  
- Número de comparações  
- Número de trocas  
- Memória utilizada (bytes)

---

## Entrada: jogadores.csv

O arquivo jogadores.csv contém os seguintes campos:

- Nome  
- Posição  
- Naturalidade  
- Posição (campo repetido no arquivo original)  
- Idade  

Cada linha corresponde a um jogador e é convertida em uma struct dentro de um vetor. A ordenação é sempre baseada no campo Nome.

---

## Compilação e Execução

O projeto deve ser compilado utilizando o Makefile fornecido. Para compilar:

```bash
make all
````

Para executar o programa:

```bash
./programa <modo>
```

Onde `<modo>` pode ser:

* 1 para o método simples (Bubble Sort)
* 2 para o método ótimo (Merge Sort)
* 3 para o método de tempo linear (Radix Sort)

Exemplo:

```bash
./sorter 2
```
---

## Requisitos para Compilação
* GCC ou qualquer compilador compatível com C99
* Make

---

## Saída

Após ordenar o vetor de structs, o programa imprime:

1. A lista completa de jogadores ordenados, com todos os campos.
2. Resultados da medição de desempenho no seguinte formato:

```
<tempo_execucao_ms>
<numero_comparacoes>
<numero_trocas>
<memoria_utilizada_bytes>
```
---

## Estrutura do Repositório

```
sorting-players/
 ┣ data/
 │ ┣ jogadores.csv
 │ ┗ jogadores_ordenados.csv
 ┣ src/
 │ ┣ main.c
 │ ┣ leitura.c
 │ ┣ leitura.h
 │ ┣ algoritmos.c
 │ ┗ algoritmos.h
 ┣ .gitignore
 ┣ LICENSE
 ┣ makefile
 ┗ README.md
```

---

## Relatório

O projeto está acompanhado de um relatório contendo:

* Descrição do problema
* Estruturas de dados utilizadas
* Detalhamento dos algoritmos
* Análise de complexidade
* Resultados obtidos
* Considerações finais

---

## Autores

- [Carlos Eduardo Pereira dos Santos](https://github.com/pereira-devcarlos)
- [Marcos Felipe dos Reis Bento](https://github.com/MarcosBento06)
- [Guilherme de Oliveira Aredes](https://github.com/aredesog)
