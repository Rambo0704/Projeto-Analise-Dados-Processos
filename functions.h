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
void contid(int idobtido);
void ordprocessid();
#endif