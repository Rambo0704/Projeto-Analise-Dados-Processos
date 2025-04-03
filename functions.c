#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

FILE *abrirarq(char *texto,char *modo){ 
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
  int contid() { //funçao base.
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    int cont = 0;
    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo)) {
      cont++;
      printf("%s",linha);
      }
    fechararq(arquivo);
    return cont;
    }
    void ordprocessid() {
        FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
        Processo processos[2000]; //criando um vetor de processor para armazenar em memoria os dados do arquivo.
        int cont = 0;
        char linha[1000];
        while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) { //ler linha por linha o arquivo.
          int resultado = sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%d},{%d},%d", //salvar os dados do arquivo no vetor de processos.
           &processos[cont].id,
            processos[cont].num,
            processos[cont].data,
            &processos[cont].id_classe,
            &processos[cont].id_assunto,
            &processos[cont].ano_eleicao);
              cont++;
          } 
        fechararq(arquivo);
        for (int i = 0; i < cont - 1; i++) { //for para ordenar usando o bubble sort passado pelo professor/ usei o bubble sort pois foi o que mais fez sentido na minha cabeça :)
            for (int j = 0; j < cont - i - 1; j++) {
                if (processos[j].id > processos[j + 1].id) {
                    Processo temp = processos[j];
                    processos[j] = processos[j + 1];
                    processos[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < cont; i++) { //for para imprimir os dados do vetor.
            printf("%ld, \"%s\", %s, {%d}, {%d}, %d\n",
                   processos[i].id,
                   processos[i].num,
                   processos[i].data,
                   processos[i].id_classe,
                   processos[i].id_assunto,
                   processos[i].ano_eleicao);
        }
    }
    