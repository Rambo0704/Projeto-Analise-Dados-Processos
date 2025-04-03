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

int contid() {  //função base
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    int cont = 0;
    char linha[1000];

    while (fgets(linha, sizeof(linha), arquivo)) {
        cont++;
        printf("%s", linha);
    }

    fechararq(arquivo);
    return cont;
}

void ordprocessid() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo processos[2000]; // vetor para armazenar os processos
    int cont = 0;
    char linha[5000];
    while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) { //while para ler o arquivo e armazenar em processos.
      int resultado = sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%d},{%d},%d",
        &processos[cont].id,
        processos[cont].num,
        processos[cont].data,
        &processos[cont].id_classe,
        &processos[cont].id_assunto,
        &processos[cont].ano_eleicao);
        cont++;
    }
    fechararq(arquivo);
    for (int i = 0; i < cont - 1; i++) { // usando o bobble sort passado pelo professor para ordenar os processos.
        for (int j = 0; j < cont - i - 1; j++) { //optei pelo bubble sort pois fez mais sentido na minha cabeça talvez não seja o mais eficiente :)
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
}
