#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct{
  long id;
  char num[30];
  char data[60];
  char id_classe[60];
  char id_assunto[60];
  int ano_eleicao;
}Processo;
 
FILE *abrirarq(char *texto,char *modo);
void fechararq(FILE *arq);
void contidclass(int idobtido);
int separacampo(char *linha, char *campos[], int max_campos) ;
void ordprocessid();
void calcular_dias_tramitacao(int idprocura);
void contar_assuntos_distintos();
void processassunt();
#endif