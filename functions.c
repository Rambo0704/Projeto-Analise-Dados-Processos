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

int separacampo(char *linha, char *campos[], int max_campos) {
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

void ordprocessid() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    Processo *processos = NULL;
    int capacidade = 1000;
    int cont = 0;
    processos = malloc(capacidade * sizeof(Processo));
    char linha[5000];
    char cabecalho[5000];
    fgets(cabecalho, sizeof(cabecalho), arquivo); 
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (cont >= capacidade) {
            capacidade *= 2;
            processos = realloc(processos, capacidade * sizeof(Processo));
            if (!processos) {
                printf("Erro ao realocar memória\n");
                exit(1);
            }
        }
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
    for (int i = 0; i < cont - 1; i++) {
        for (int j = 0; j < cont - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
    for(int x = 0; x < cont; x++){
        printf("%ld, \"%s\", %s, %s, %s, %d\n",
               processos[x].id,
               processos[x].num,
               processos[x].data,
               processos[x].id_classe,
               processos[x].id_assunto,
               processos[x].ano_eleicao);
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
    printf("Arquivo ordenado com sucesso!Salvo como 'processo_043_202409032338_ordenado.csv'\n");
    fechararq(arquivo_saida);
    free(processos);
}

void contidclass(int idobtido) {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[1000];
    int cont = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *p = strchr(linha, '{');
        if (p && atoi(p + 1) == idobtido)
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
    Processo *processos;

    int total = 0;
    char linha[5000];
    char cabecalho[5000];

    fgets(cabecalho, sizeof(cabecalho), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) && total < 20000) {
        char *campos[6];
        int num_campos = separacampo(linha, campos, 6);
        if (num_campos < 6) {
            printf("Linha com menos de 6 campos: %s\n", linha);
            continue;
        }

        strcpy(processos[total].id_assunto, campos[4]);

        char id_limpo[100];
        strncpy(id_limpo, processos[total].id_assunto, sizeof(id_limpo));
        id_limpo[strcspn(id_limpo, "\r\n")] = '\0';
        if (id_limpo[0] == '{') memmove(id_limpo, id_limpo + 1, strlen(id_limpo));
        char *fecha = strchr(id_limpo, '}');
        if (fecha) *fecha = '\0';

        printf("Campo bruto: %s | Campo limpo: %s\n", processos[total].id_assunto, id_limpo);

        strcpy(processos[total].id_assunto, id_limpo);
        total++;
    }
    fechararq(arquivo);

    int distintos[20000];
    int count_distintos = 0;

    for (int i = 0; i < total; i++) {
        int valor = atoi(processos[i].id_assunto);
        if (valor == 0) {
            printf("Ignorando id_assunto inválido: '%s'\n", processos[i].id_assunto);
            continue;
        }

        int ja_existe = 0;
        for (int j = 0; j < count_distintos; j++) {
            if (valor == distintos[j]) {
                ja_existe = 1;
                break;
            }
        }

        if (!ja_existe) {
            distintos[count_distintos++] = valor;
        }
    }

    printf("Quantidade de id_assunto distintos: %d\n", count_distintos);
}

void processassunt() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    char linha[5000];
    Processo p;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *campos[6];
        int n = separacampo(linha, campos, 6);
        p.id = strtol(campos[0], NULL, 10);
        strcpy(p.num, campos[1]);
        strcpy(p.data, campos[2]);
        strcpy(p.id_classe, campos[3]);
        strcpy(p.id_assunto, campos[4]);
        p.ano_eleicao = atoi(campos[5]);
        if (strchr(p.id_assunto, ',')) {
            printf("%ld, \"%s\", %s, %s, %s, %d\n",
                   p.id,
                   p.num,
                   p.data,
                   p.id_classe,
                   p.id_assunto,
                   p.ano_eleicao);
        }
    }
    fechararq(arquivo);
}

void ordprocessodata() {
    FILE *arquivo = abrirarq("processo_043_202409032338.csv", "r");
    int capacidade = 1000;
    int cont = 0;
    char linha[5000];
    char cabecalho[5000];

    Processo *processos = malloc(capacidade * sizeof(Processo));
    if (processos == NULL) {
        printf("Erro ao alocar memória.\n");
        fechararq(arquivo);
        return;
    }
    if (!fgets(cabecalho, sizeof(cabecalho), arquivo)) {
        printf("Erro ao ler cabeçalho.\n");
        free(processos);
        fechararq(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *campos[6];
        int num_campos = separacampo(linha, campos, 6);

        if (num_campos != 6) {
            continue;
        }

        if (cont >= capacidade) {
            capacidade *= 2;
            Processo *temp = realloc(processos, capacidade * sizeof(Processo));
            if (temp == NULL) {
                printf("Erro ao realocar memória.\n");
                free(processos);
                fechararq(arquivo);
                return;
            }
            processos = temp;
        }

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
    if (!saida) {
        printf("Erro ao abrir arquivo de saída.\n");
        free(processos);
        return;
    }

    fprintf(saida, "%s", cabecalho);
    for (int i = 0; i < cont; i++) {
        fprintf(saida, "%ld, \"%s\", %s, %s, %s, %d\n",
                processos[i].id,
                processos[i].num,
                processos[i].data,
                processos[i].id_classe,
                processos[i].id_assunto,
                processos[i].ano_eleicao);
        printf("%ld, \"%s\", %s, %s, %s, %d\n",
               processos[i].id,
               processos[i].num,
               processos[i].data,
               processos[i].id_classe,
               processos[i].id_assunto,
               processos[i].ano_eleicao);
    }
    fechararq(saida);
    free(processos);

    printf("\nArquivo ordenado salvo como 'processo_043_202409032338_data.csv'.");
}