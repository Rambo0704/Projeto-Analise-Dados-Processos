#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
int separacampo(char *linha, char *campos[], int max_campos) { //criei uma função para facilitar a leitura e escrita de atributos multivalorados do arquivo csv, onde ela separa os campos e armazena em um vetor de strings.(dica do professor)
    int campo_atual = 0;
    int dentro_aspas = 0, dentro_chaves = 0;
    char *inicio = linha;
    for (char *p = linha; *p != '\0' && campo_atual < max_campos; p++) {
        if (*p == '"') dentro_aspas = !dentro_aspas;
        else if (*p == '{') dentro_chaves++;
        else if (*p == '}') dentro_chaves--;
        else if (*p == ',' && !dentro_aspas && dentro_chaves == 0) {
            *p = '\0';
            campos[campo_atual++] = inicio;
            inicio = p + 1;
        }
    }
    if (campo_atual < max_campos) {
        campos[campo_atual++] = inicio;
    }
    return campo_atual;
}
void ordprocessid() { //ordenar os processos por id.
    // Criei uma função para ordenar os processos por id, onde ela lê o arquivo csv e armazena os dados em um vetor de estruturas, depois ordena o vetor e escreve em um novo arquivo csv. (dica do professor)
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo processos[2000];
    int cont = 0;
    char linha[5000];
    char cabecalho[5000];
    fgets(cabecalho, sizeof(cabecalho), arquivo); 
    while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) {
        char *campos[6]; 
        int num_campos = separacampo(linha, campos, 6);
        if (num_campos < 6) continue;
        processos[cont].id = strtol(campos[0], NULL, 10);
        char *num = campos[1];
        if (*num == ' ') num++;
        if (*num == '"') num++;
        char *aspas = strchr(num, '"');
        if (aspas) *aspas = '\0';
        strcpy(processos[cont].num, num);
        strcpy(processos[cont].data, campos[2]);
        strcpy(processos[cont].id_classe, campos[3]);
        strcpy(processos[cont].id_assunto, campos[4]);
        processos[cont].ano_eleicao = atoi(campos[5]);
        cont++;
    }
    fechararq(arquivo);
    for (int i = 0; i < cont - 1; i++) { //utilizei o bobble sort para ordenar, não é o mais eficiente mas é o que faz sentido na minha cabeça :).
        for (int j = 0; j < cont - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
    FILE *arquivo_saida = abrirarq("processo_043_202409032338_ordenado.csv", "w");
    fprintf(arquivo_saida, "%s", cabecalho); 
    for (int y = 0; y < cont; y++) { //escrevendo os dados no arquivo csv ordenado.
        fprintf(arquivo_saida, "%ld, \"%s\", %s, %s, %s, %d\n",
                processos[y].id,
                processos[y].num,
                processos[y].data,
                processos[y].id_classe,
                processos[y].id_assunto,
                processos[y].ano_eleicao);
    }
    printf("Arquivo ordenado com sucesso!\n");
    fechararq(arquivo_saida);
}
void contidclass(int idobtido) {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[1000];
    int cont = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *p = strchr(linha, '{'); //procurei o caractere '{' na linha. (usei essa funçao que esta contida na biblioteca string.h,indicado pelo professor)
        if (p && atoi(p + 1) == idobtido) //transformo o caractere em inteiro e comparo com o id obtido.
            cont++;
    }
    printf("ID:%d encontrados: %d\n",idobtido,cont);
    fechararq(arquivo);
}
void calcular_dias_tramitacao(int idprocura) {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[5000];
    struct tm t = {0};
    time_t now = time(NULL);
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        Processo p;
        sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%[^}]},{%[^}]},%d",
                   &p.id, 
                   p.num, 
                   p.data, 
                   p.id_classe, 
                   p.id_assunto, 
                   &p.ano_eleicao);
            if (idprocura == p.id) {
                int ano, mes, dia;
                if (sscanf(p.data, "%d-%d-%d", &ano, &mes, &dia) == 3) {
                    t.tm_year = ano - 1900;
                    t.tm_mon = mes - 1;
                    t.tm_mday = dia;
                    time_t data_processo = mktime(&t);
                    if (data_processo != -1) {
                        int dias = difftime(now, data_processo) / 86400;
                        printf("ID: %ld - %d dias em tramitacao\n", p.id, dias);
                break; 
            }
        }
    }
    }
}
void contar_assuntos_distintos() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo processos[2000];
    int total = 0;
    char linha[5000];

    while (fgets(linha, sizeof(linha), arquivo) && total < 2000) {
        sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%d},{%d},%d",
               &processos[total].id,
               processos[total].num,
               processos[total].data,
               &processos[total].id_classe,
               &processos[total].id_assunto,
               &processos[total].ano_eleicao);
        total++;
    }
    fechararq(arquivo);

    int distintos[2000];
    int count_distintos = 0;

    for (int i = 0; i < total; i++) {
        int ja_existe = 0;
        for (int j = 0; j < count_distintos; j++) {
            if (atoi(processos[i].id_assunto) == distintos[j]) {
                ja_existe = 1;
                break;
            }
        }
        if (!ja_existe) {
            distintos[count_distintos++] = atoi(processos[i].id_assunto);
        }
    }

    printf("Quantidade de id_assunto distintos: %d\n", count_distintos);
}
void processassunt() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[5000];
    Processo processos[2000];
    int total = 0;
    fgets(linha, sizeof(linha), arquivo); 
    while (fgets(linha, sizeof(linha), arquivo) && total < 2000) {
        if (sscanf(linha, "%ld,\"%[^\"]\",%[^,],{%[^}]},{%[^}]},%d",
                   &processos[total].id,
                   processos[total].num,
                   processos[total].data,
                   processos[total].id_classe,
                   processos[total].id_assunto,
                   &processos[total].ano_eleicao) == 6) {
            if (processos[total].id_assunto[0] == '"') {
                printf("%ld,\"%s\",%s,{%s},{%s},%d\n",
                       processos[total].id,
                       processos[total].num,
                       processos[total].data,
                       processos[total].id_classe,
                       processos[total].id_assunto,
                       processos[total].ano_eleicao);
            }

            total++;
        }
    }

    fechararq(arquivo);
}
void ordprocessodata() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo processos[2000];
    int cont = 0;
    char linha[5000];
    char cabecalho[5000];
    fgets(cabecalho, sizeof(cabecalho), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) && cont < 2000) {
        char *campos[6];
        int num_campos = separacampo(linha, campos, 6);
        if (num_campos < 6) continue;

        processos[cont].id = strtol(campos[0], NULL, 10);
        char *num = campos[1];
        if (*num == ' ') num++;
        if (*num == '"') num++;
        char *aspas = strchr(num, '"');
        if (aspas) *aspas = '\0';                             
        strcpy(processos[cont].num, num);
        strcpy(processos[cont].data, campos[2]);
        strcpy(processos[cont].id_classe, campos[3]);
        strcpy(processos[cont].id_assunto, campos[4]);
        processos[cont].ano_eleicao = atoi(campos[5]);
        cont++;
    }
    fechararq(arquivo);
    // Ordena por data_ajuizamento (ordem decrescente)
    for (int i = 0; i < cont - 1; i++) {
        for (int j = 0; j < cont - i - 1; j++) {
            if (strcmp(processos[j].data, processos[j + 1].data) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
    FILE *saida = abrirarq("processo_043_202409032338_data.csv", "w");
    fprintf(saida, "%s", cabecalho);
    for (int i = 0; i < cont; i++) {
        fprintf(saida, "%ld, \"%s\", %s, %s, %s, %d\n",
                processos[i].id,
                processos[i].num,
                processos[i].data,
                processos[i].id_classe,
                processos[i].id_assunto,
                processos[i].ano_eleicao);
    }
    fechararq(saida);
    printf("Arquivo ordenado por data_ajuizamento (decrescente) salvo com sucesso!\n");
}