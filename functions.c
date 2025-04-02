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
  int contid() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    int cont = 0;
    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo)) {
            cont++;
            printf("Linha %d: %s", cont, linha);
    }
    printf("Processos com ID assuntos lidos: %d\n", cont);
    fechararq(arquivo);
    return cont;
  }