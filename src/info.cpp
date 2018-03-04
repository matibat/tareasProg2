#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "../include/info.h"

struct rep_info {
  int num;
  char *frase;
};

info_t crear_info(int num, char *frase) {
  info_t nueva = new rep_info;
  nueva->num = num;
  nueva->frase = frase;
  return nueva;
}

info_t copia_info(info_t info) {
  info_t copia = new rep_info;
  copia->frase = new char[strlen(info->frase)+1];
  strcpy(copia->frase, info->frase);
  return copia;
}

void liberar_info(info_t &info) {
  delete[] info->frase;
  delete info;
}

bool es_valida_info(info_t info) {
  return (info->num != INT_MAX);
}

char *info_a_texto(info_t info) {
  char copia_num[11];
  sprintf(copia_num, "%d", info->num);
  char *texto = new char [strlen(copia_num) +
                          strlen(info->frase) +
                          4];
  strcpy(texto, "(");
  strcat(texto, copia_num);
  strcat(texto, ",");
  strcat(texto, info->frase);
  strcat(texto, ")");
  return texto;
}

info_t leer_info(int max) {
  info_t leido;
  int num;
  char *cadena = new char[max + 1];
  char simbolo;
  bool error = false;
  scanf(" %c", &simbolo);
  if(simbolo != '(')
    error = true;
  else {
    scanf("%d", &num);
    scanf(" %c", &simbolo);
    if(simbolo != ',')
      error = true;
    else {
      int pos = 0;
      int c = getchar();
      while((c != ')') && (c != '\n')) {
        cadena[pos] = c;
        pos++;
        c = getchar();
      }
      cadena[pos] = '\0';
      if(c != '\n') {
        error = true;
        ungetc('\n', stdin);
      }
    }
  }
  if(error)
    leido = crear_info(INT_MAX, '\0');
  else {
    char *frase = new char[strlen(cadena)+1];
    strcpy(frase, cadena);
    leido = crear_info(num, frase);
  }
  delete[] cadena;
  return leido;
}

bool es_vealida_info(info_t info) {
  return (info->num != INT_MAX);
}

int numero_info(info_t info) {
  return info->num;
}

char *frase_info(info_t info) {
  return info->frase;
}

bool son_iguales(info_t i1, info_t i2) {
  return (&i1->num == &i2->num && strcmp(i1->frase, i2->frase));
}

info_t combinar_info(info_t i1, info_t i2) {
  printf("combinar_info(i1, i2)");
  printf("i1: ->num: %d, frase: %s", i1->num, i1->frase);
  printf("i2: ->num: %d, frase: %s", i2->num, i2->frase);
  info_t combinacion = new rep_info;
  combinacion->frase = new char[strlen(i1->frase) +
                                strlen(i2->frase) +
                                1];
  combinacion->num = i1->num + i2->num;
  strcpy(combinacion->frase, i1->frase);
  strcat(combinacion->frase, i2->frase);
  strcat(combinacion->frase, "\0");
  return combinacion;
}

