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
FILE *fechararq(FILE *arq) {
  if (arq != NULL) {
      fclose(arq);
      arq = NULL;  
  }
  return arq;
}