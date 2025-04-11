#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include "functions.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    SetConsoleOutputCP(65001);
    int op;
    printf(
        "Bem-vindo ao sistema de gerenciamento de dados!\n"
        "Escolha uma opção:\n"
        "  1. Ordenar, em ordem crescente, o conjunto de dados a partir do atributo id\n"
        "  2. Ordenar, em ordem decrescente, o conjunto de dados a partir do atributo 'data_ajuizamento'\n"
        "  3. Contar quantos processos estão vinculados a um determinado 'id_classe'\n"
        "  4. Identificar quantos 'id_assuntos' constam nos processos presentes na base de dados\n"
        "  5. Listar todos os processos que estao vinculados a mais de um assunto\n"
        "  6. Indicar a quantos dias um processo está em tramitacao na justica\n"
    );

    printf("Digite a opcao desejada: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            ordprocessid();
            break;
        case 2:
            ordprocessodata();
            break;
        case 3: {
            int id_classe;
            printf("Digite o id_classe: ");
            scanf("%d", &id_classe);
            contidclass(id_classe);
            break;
        }
        case 4:
            contar_assuntos_distintos();
            break;
        case 5:
            processassunt();
            break;
        case 6: {
            int id_processo;
            printf("Digite o id do processo: ");
            scanf("%d", &id_processo);
            calcular_dias_tramitacao(id_processo);
            break;
        }
        default:
            printf("Opção inválida!\nOpções de 1 a 6.\n");
            break;
    }

    return 0;
}
