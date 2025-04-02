#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct{
  long id;
  char num[21];
  char data;
  int id_classe;
  int id_assunto;
  int ano_eleicao;
}Processo;
 
FILE *abrirarq(char *texto,char *modo);
void fechararq(FILE *arq);
int contid();

#endif