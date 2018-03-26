/** 53677509 **/

// incluir librerías estandar
#include <stdio.h>  // sprintf
#include <string.h> // strcpy, strlen, strcat
#include <limits.h> // INT_MAX

// header de info.cpp
#include "../include/info.h"

// definicion de rep_info
struct rep_info {
  int num;
  char *frase;
};

// crear_info crea una instancia de rep_info a partir de un int y un string, y retorna un info_t que lo apunta
info_t crear_info(int num, char *frase) {
  info_t nueva = new rep_info;
  nueva->num = num;
  nueva->frase = frase;
  return nueva;
}

// copia_info crea una copia de un rep_info a partir de otro apuntado por el info_t de entrada, retorna un info_t que lo apunta
info_t copia_info(info_t info) {
  info_t copia = new rep_info;
  copia->num = info->num;
  copia->frase = new char[strlen(info->frase)+1]; // +1 por el caracter nulo (-:
  strcpy(copia->frase, info->frase);
  return copia;
}

// liberar_info limpia el contenido del rep_info al cual apunta el info_t de la entrada
void liberar_info(info_t &info) {
  delete[] info->frase;
  delete info;
}

// es_valida_info chequea la integridad de el numero del rep_info apuntado por el info_t de entrada
bool es_valida_info(info_t info) {
  return (info->num != INT_MAX);
}

// info_a_texto devuelve una cadena con el formato "(num,frase)" donde num y frase son los atributos del rep_info apuntado por el info_t de entrada
char *info_a_texto(info_t info) {
  char copia_num[11];
  sprintf(copia_num, "%d", info->num);
  char *texto = new char [strlen(copia_num) +
                          strlen(info->frase) +
                          4]; // +4 por los dos parentesis, la coma y el nulo
  strcpy(texto, "(");
  strcat(texto, copia_num);
  strcat(texto, ",");
  strcat(texto, info->frase);
  strcat(texto, ")");
  return texto;
}

// leer_info toma max que determina el tamaño maximo de la cadena a ser leida, de la cual se extraen los valores del rep_info al que apuntara el info_t a ser retornado
info_t leer_info(int max) {
  info_t leido;
  int num; // auxiliar para leer el numero de la entrada
  char *cadena = new char[max + 1]; // +1 por el nulo
  char simbolo; // auxiliar para leer la coma (",") o los parentesis ("(" y ")") entre el numero y la frase
  bool error = false; // auxiliar para controlar la integridad de la entrada
  scanf(" %c", &simbolo);
  if(simbolo != '(') // el primer caracter tiene que ser un parentesis
    error = true;
  else {
    scanf("%d", &num); // le sigue un numero 
    scanf(" %c", &simbolo);
    if(simbolo != ',') // luego una coma 
      error = true;
    else {
      int pos = 0; // indice auxiliar para iterar la frase
      int c = getchar(); // auxiliar que contiene al caracter leido
      while((c != ')') && (c != '\n')) { // el fin de la frase esta determinado por el parentesis
        cadena[pos] = c;
        pos++;
        c = getchar();
      }
      cadena[pos] = '\0'; // se cierra la cadena con el caracter nulo
      if(c == '\n') { // la entrada si o si debe terminar con un parentesis
        error = true;
        ungetc('\n', stdin);
      }
    }
  }
  if(error) { // si hubo un error, se retorna como numero el maximo posible y como frase una string vacia
    char *nulo = new char[1];
    nulo[0] = '\0';
    leido = crear_info(INT_MAX, nulo);
  } else { // sino se guardan los datos y se retornan
    char *frase = new char[strlen(cadena)+1];
    strcpy(frase, cadena);
    leido = crear_info(num, frase);
  }
  delete[] cadena; // limpiar memoria
  return leido;
}

// es_vealida_info retorna verdadero si la instancia se creo sin errores
bool es_vealida_info(info_t info) {
  return (info->num != INT_MAX);
}

// numero_info retorna el numero del rep_info al que apunta el info_t de entrada
int numero_info(info_t info) {
  return info->num;
}

// frase_info retorna la frase del rep_info al que apunta el info_t de entrada
char *frase_info(info_t info) {
  return info->frase;
}

// son_iguales compara los dos rep_info apuntados por los info_t de entrada
bool son_iguales(info_t i1, info_t i2) {
  return (i1->num == i2->num && strcmp(i1->frase, i2->frase) == 0);
}

// combinar_info devuelve un info_t apuntando a un rep_info que contiene la suma de los numeros y la concatenacion de las strings en los rep_info apuntados por los info_t de entrada 
info_t combinar_info(info_t i1, info_t i2) {
  //printf("combinar_info(i1, i2)");
  //printf("i1: ->num: %d, frase: %s", i1->num, i1->frase);
  //printf("i2: ->num: %d, frase: %s", i2->num, i2->frase);
  info_t combinacion = new rep_info;
  combinacion->frase = new char[strlen(i1->frase) +
                                strlen(i2->frase) +
                                1]; // +1 por el nulo
  combinacion->num = i1->num + i2->num;
  strcpy(combinacion->frase, i1->frase);
  strcat(combinacion->frase, i2->frase);
  strcat(combinacion->frase, "\0");
  return combinacion;
}

