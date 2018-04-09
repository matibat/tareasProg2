/* 53677509 */

#include "uso_cadena.h"
#include "cadena.h"


bool pertenece(int i, cadena_t cad) {
  localizador_t iterador = inicio_cadena(cad);
  do {
    if (numero_info(info_cadena(iterador, cad)) == i)
      return true;
   iterador = siguiente(iterador); 
  } while (!es_final_cadena(iterador, cad));
  return false;
}

nat longitud(cadena_t cad) {
  if (es_vacia_cadena(cad))
  if (es_final_cadena(inicio_cadena(cad))) {
    return 1;
  }
  cadena_t subcadena;
  subcadena->inicio = siguiente(inicio_cadena(cad));
  subcadena->final = final_cadena(cad);
  return 1 + longitud(subcadena); 
}

bool son_iguales(cadena_t c1, cadena_t c2) {
  if (es_vacia_cadena(c1) && es_vacia_cadena(c2))
    return true;
  else {
    if (es_vacia_cadena(c1) || es_vacia_cadena(c2)) {
      return false;
    } else {
      cadena_t subc1, subc2;
      subc1->inicio = siguiente(inicio_cadena(c1));
      subc1->final = final_cadena(c1);
      subc2->inicial = siguiente(inicio_cadena(c2));
      subc2->final = final_cadena(c2);
      return (numero_info(info_cadena(inicio_cadena(c2), c2)) && son_iguales(subc1, subc2));
    }
  }
}

cadena_t concatenar(cadena_t c1, cadena_t c2) {
  cadena_t resultante = crear_cadena();
  if (!es_vacia_cadena(c2)) {
    if (!es_vacia_cadena(c1)) {
      cadena_t sigc1 = crear_cadena();
      sigc1->inicio = siguiente(inicio_cadena(c1));
      sigc1->final = final_cadena(c1);
      localizador_t nuevo_nodo;
      nuevo_nodo->dato = crear_info();
      nuevo_nodo->anterior = NULL;
      nuevo_nodo->siguiente = inicio_cadena(concatenar(resultante, sigc1));
    }
  } 
  return resultante;
}

