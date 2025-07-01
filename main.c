#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include "functions.h"

int main() {
    int opcao;
    printf("Bem-vindo ao sistema de gerenciamento de dados!\n");
    printf("Escolha uma opcao:\n");
    printf("  1. Ordenar, em ordem crescente, o conjunto de dados a partir do atributo id\n");
    printf("  2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo 'data_ajuizamento'\n");
    printf("  3. Contar quantos processos estao vinculados a um determinado 'id_classe'\n");
    printf("  4. Listar todos os processos que estao vinculados a mais de um assunto\n");
    printf("  5. Indicar a quantos dias um processo esta em tramitacao na justica\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            ordprocessid();
            break;
        case 2:
            ordprocessodata();
            break;
        case 3: {
            int id_classe;
            printf("Digite o id_classe a procurar: ");
            scanf("%d", &id_classe);
            contidclass(id_classe);
            break;
        }
        case 4:
            processassunt();
            break;
        case 5: {
            int id_processo;
            printf("Digite o ID do processo: ");
            scanf("%d", &id_processo);
            calcular_dias_tramitacao(id_processo);
            break;
        }
        default:
            printf("Opcao invalida.\n");
    }

    return 0;
}
