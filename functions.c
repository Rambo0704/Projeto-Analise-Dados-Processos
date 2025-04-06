#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

FILE *abrirarq(char *texto, char *modo) { 
    FILE *arq;
    arq = fopen(texto, modo);
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    return arq;
}
void fechararq(FILE *arq) { 
    if (arq) {
        fclose(arq);
    }
}
void ordprocessid() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo processos[2000]; // vetor para armazenar os processos
    int cont = 0;
    char linha[5000];
    char cabecalho[5000];
    fgets(cabecalho, sizeof(cabecalho), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) { //while para ler o arquivo e armazenar em processos.
      int resultado = sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%d},{%d},%d", //apos pesquisar na biblioteca stdio,econtei essa funçao que le e aramzena nos vetores,que parece ser mais adequado que o fscanf para essa situação.
        &processos[cont].id,  //tratando o dado linha como uma string, e armazenando os dados em variaveis diferentes.
        processos[cont].num,  
        processos[cont].data,
        &processos[cont].id_classe,
        &processos[cont].id_assunto,
        &processos[cont].ano_eleicao);
        cont++;
    }
    fechararq(arquivo);
    for (int i = 0; i < cont - 1; i++) { // usando o bobble sort passado pelo professor para ordenar os processos.
        for (int j = 0; j < cont - i - 1; j++) { //optei pelo bubble sort pois fez mais sentido na minha cabeça, talvez não seja o mais eficiente :)
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < cont; i++) {
        printf("%ld, \"%s\", %s, {%d}, {%d}, %d\n",
               processos[i].id,
               processos[i].num,
               processos[i].data,
               processos[i].id_classe,
               processos[i].id_assunto,
               processos[i].ano_eleicao);
        }
  FILE *arquivo_saida = abrirarq("processo_043_202409032338_ordenado.csv", "a"); //abri o arquivo para escrever os dados ordenados.
  fprintf(arquivo_saida, "%s", cabecalho);
  for (int y = 0; y < cont; y++){ //for para escrever os dados ordenados no arquivo.
        fprintf(arquivo_saida, "%ld, \"%s\", %s, {%d}, {%d}, %d\n",
                processos[y].id,
                processos[y].num,
                processos[y].data,
                processos[y].id_classe,
                processos[y].id_assunto,
                processos[y].ano_eleicao);
    }
        fechararq(arquivo_saida); //fechei o arquivo de saida.
}
void contid(int idobtido) {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[1000];
    int cont = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *p = strchr(linha, '{'); //procurei o caractere '{' na linha. (usei essa funçao que esta contida na biblioteca string.h,indicado pelo professor)
        if (p && atoi(p + 1) == idobtido) //transformo o caractere em inteiro e comparo com o id obtido.
            cont++;
    }
    printf("IDS encontrados: %d\n",cont);
    fechararq(arquivo);
}