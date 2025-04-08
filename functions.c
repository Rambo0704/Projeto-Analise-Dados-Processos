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
    Processo processos[2000];
    int cont = 0;
    char linha[5000];
    char cabecalho[5000];
    fgets(cabecalho, sizeof(cabecalho), arquivo); //Fazendo primeiro o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) {
        char *p = linha;
        processos[cont].id = strtol(p, &p, 10);
        while (*p == ',' || *p == ' ') p++;

        if (*p == '"') p++;
        char *q = strchr(p, '"');
        if (!q) continue;
        *q = '\0';
        strcpy(processos[cont].num, p);
        p = q + 1;
        while (*p == ',' || *p == ' ') p++;

        q = strchr(p, ',');
        if (!q) continue;
        *q = '\0';
        strcpy(processos[cont].data, p);
        p = q + 1;

        while (*p != '{' && *p != '\0') p++; 
        if (*p != '{') continue;
        q = strchr(p, '}');
        if (!q) continue;
        q++; 
        int len = q - p;
        strncpy(processos[cont].id_classe, p, len);
        processos[cont].id_classe[len] = '\0';
        p = q;
        while (*p == ',' || *p == ' ') p++;

        while (*p != '{' && *p != '\0') p++;
        if (*p != '{') continue;
        q = strchr(p, '}');
        if (!q) continue;
        q++;
        len = q - p;
        strncpy(processos[cont].id_assunto, p, len);
        processos[cont].id_assunto[len] = '\0';
        p = q;
        while (*p == ',' || *p == ' ') p++;

        processos[cont].ano_eleicao = atoi(p);

        cont++;
    }

    fechararq(arquivo);

    for (int i = 0; i < cont - 1; i++) {
        for (int j = 0; j < cont - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < cont; i++) {
        printf("%ld, \"%s\", %s, %s, %s, %d\n",
               processos[i].id,
               processos[i].num,
               processos[i].data,
               processos[i].id_classe,
               processos[i].id_assunto,
               processos[i].ano_eleicao);
    }

    FILE *arquivo_saida = abrirarq("processo_043_202409032338_ordenado.csv", "w");
    fprintf(arquivo_saida, "%s", cabecalho);
    for (int y = 0; y < cont; y++) {
        fprintf(arquivo_saida, "%ld, \"%s\", %s, %s, %s, %d\n",
                processos[y].id,
                processos[y].num,
                processos[y].data,
                processos[y].id_classe,
                processos[y].id_assunto,
                processos[y].ano_eleicao);
    }
    fechararq(arquivo_saida);
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