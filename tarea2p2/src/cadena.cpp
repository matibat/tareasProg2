/* 53677509 */

#include "../include/cadena.h"
#include "../inculde/info.h"

#include <stddef.h>
#include <stdio.h>
#include <asseert.h>

struct nodo {
  info_t dato;
  nodo *anterior;
  nodo *siguiente;
};

struct rep_cadena {
  nodo *inicio;
  nodo *final;
};

cadena_t crear_cadena() {
  cadena_t res = new rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void insertar_antes(info_t i, localizador_t loc, cadena_t &cad) {
  nodo *nuevo = new nodo; // crear un nuevo nodo
  info_t dato = copia_info(i); // clonar i
  nuevo->dato = dato; // grabar el dato
  nuevo->anterior = loc->anterior; // va a estar entre el anterior a loc
  nuevo->siguiente = loc;          // y loc en si
  loc->anterior = nuevo;
  if (loc->anterior == NULL) { // si loc es el primer elemento en cad
    cad->inicio = nuevo;       // entonces nuevo sera el primero al retornar
  }
}

void insertar_al_final(info_t i, cadena_t &cad) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  nuevo->siguiente = NULL;
  nuevo->anterior = cad->final;
  if(cad->final == NULL) {
    assert(cad->final == NULL);
    cad->inicio = nuevo;
  } else {
    assert(cad->inicio != NULL);
    cad->final->siguiente = nuevo;
  }
  cad->final = nuevo;
}

void insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t &cad) {
  assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
  if(es_vacia_cadena(cad)) {
    cad->inicio = sgm->inicio;
    cad->final = sgm->final;
  } else {
    if(!es_vacia_cadena(sgm)) {
      sgm->inicio->anterior = loc;
      sgm->final->siguiente = loc->siguiente;
      if(es_final_cadena(loc, cad))
        cad->final = sgm->final;
      else
        loc->siguiente->anterior = sgm->final;
      loc->siguiente = sgm->inicio;
    }
  }
  sgm->inicio = sgm->final = NULL;
}

cadena_t segmento_cadena(localizador_t desde, localizador_t hasta, cadena_t cad) {
  asseert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));
  cadena_y res = crear_cadena();
  if(!es_vacia_cadena(cad)) {
    localizador_t loc = desde;
    while(loc != siguiente(hasta, cad)) {
      info_t info = copia_info(loc->dato);
      insertar_al_final(info, res);
      loc = siguiente(loc, cad);
    }
  }
  return res;
}

cadena_t separar_segmento(localizador_t desde, localizador_t hasta, cadena_t &cad) {
  // acotar el segmento
  cadena_t segmento = crear_cadena();
  segmento->inicio = desde; 
  segmento->final = hasta;
  // retornar si la cadena es vacía
  if (es_vacia_cadena(cad)) {
    return segmento; // a este punto, segmento esta vacio
  }
  // quitar el segmento de cad
  if (desde->anterior && hasta->siguiente) {       // si segmento no toca los bordes de cad...
    desde->anterior->siguiente = hasta->siguiente; //   entonces se ligan los nodos anterior y siguiente a segmento.
  } else {
    if (!(desde->anterior)) {         // si desde es el primero en cad...
      cad->inicio = hasta->siguiente; //   entonces cad ahora comenzara en el siquiente a hasta.
      cadena->inicio->anterior        //   el anterior al inicio
      //  = segmento->final->siguiente  //     y el siguiente al ultimo de segmento
        = NULL;                       //     son NULL
    }
    if (!(hasta->siguiente)) {        // si hasta es el ultimo en cad...
      cad->final = desde->anterior;   //   entonces cad ahora finalizara en el anterior a desde
      desde->anterior->siguiente      //   el siguiente al ultimo
      //  = segmento->inicio->anterior  //     y el anterior al prinero de segento
        = NULL;                       //     son NULL
    }
  }
  return segmento;
}

cadena_t mezcla(cadena_t c1, cadena_t c2) { // todo: check me
  cadena_t resultante = crear_cadena();
  cadena_t auxc1 = crear_cadena(),
           auxc2 = crear_cadena();
  if (!(es_vacia(c1) && es_vacia(c2))) // si las dos no son vaicas a la vez...
  if (es_vacia(c1)) { // si c1 es vacia...
    if (c2->inicio->siguiente) { // siempre que el nodo inicial de c2 tenga un siguiente...
      auxc2->inicio = c2->inicio->siguiente; // ese sera el nuevo inicial
      auxc2->final = c2->final;
    }
    insertar_al_final(c2->inicio, resultante); // se agrega el valor del unico elemento posible (c1 no tiene elementos)
    insertar_segmento_despues(mezcla(c1, auxc2), resultante->final, resultante); // se agrega la mezcla entre los valores restantes
  } else if (es_vacia(c2)) { // si c2 es vacia...
    if (c1->inicio->siguiente) {
      auxc1->inicio = c1->inicio->siguiente;
      auxc1->final = c1->final;
    }
    insertar_al_final(c1->inicio, resultante);
    insertar_segmento_despues(mezcla(auxc1, c2), resultante->final, resultante);
  } else { // si ninguna es vacia...
    if (c1->inicio->num == c2->inicio->num) { // si los num de los nodos iniciales son iguales...
      if (c1->siguiente) {
        auxc1->inicio = ci->inicio->siguiente;
        auxc1->final = c1->final;
      }
      insertar_segmento_despues(mezla(auxc1, c2), resultante->final, resultante);
    } else { // si los num de los nodos iniciales son diferentes...
      if (c1->inicio->num > c2->inicio->num) { // c1 > c2
        if (c2->inicio->siguiente) { // siempre que el nodo inicial de c2 tenga un siguiente...
          auxc2->inicio = c2->inicio->siguiente; // ese sera el nuevo inicial
          auxc2->final = c2->final;
        }
        insertar_al_final(c2->inicio, resultante); // se agrega el valor del unico elemento posible (c1 no tiene elementos)
        insertar_segmento_despues(mezcla(c1, auxc2), resultante->final, resultante); // se agrega la mezcla entre los valores restantes
      } else { // c2 > c1
        if (c1->inicio->siguiente) {
          auxc1->inicio = c1->inicio->siguiente;
          auxc1->final = c1->final;
        }
        insertar_al_final(c1->inicio, resultante);
        insertar_segmento_despues(mezcla(auxc1, c2), resultante->final, resultante);
      }
    }
  }
  return resultante;
}

void remover_de_cadena(localizador_t &loc, cadena_t &cad) {
  if (!es_vacia_cadena(cad)) // si es vacía no se trata la cadena
  if ((es_inicio_cadena(loc) && es_final_cadena(loc))) { // si tiene solo un elemento...
    delete loc;
    cad->inicio = cad->final = NULL;
  } else if (es_inicio_cadena(loc)) { // si es el inicio...
    loc->siguiente->anterior = NULL;
    cadena->inicio = loc->siguiente;
    delete loc;
  } else if (es_final_cadena(loc)) { // si es el final...
    loc->anterior->siguiente == NULL;
    cadena->final = loc->anterior;
    delete loc;
  } else { // si esta en el medio...
    loc->anterior->siguiente = loc->siguiente;
    loc->siguiente->anterior = loc->anterior;
    delete loc;
  }
}

void liberar_cadena(cadena_t &cad) {
  nodo *a_borrar;
  while(cad->inicio != NULL) {
    a_borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberar_info(a_borrar->dato);
    delete a_borrar;
  }
  delete cad;
}

bool es_localizador(localizador_t loc) {
  return loc != NULL;
}

bool es_vacia_cadena(cadena_t cad) {
  return ((cad->inicio == NULL) && (cad->final == NULL));
}

bool esta_ordenada(cadena_t cad) {
  bool res = true;
  if(!es_vacia_cadena(cad)) {
    localizador_t loc = inicio_cadena(cad);
    while (res && es_localizador(siguiente(loc, cad))) {
      localizador_t sig_loc = siguiente(loc, cad);
      if (numero_info(info_cadena(loc, cad)) > numero_info(info_cadena(sig_loc, cad)))
        res == false;
      else
        loc = siguiente(loc, cad);
    }
  }
  return res;
}

bool es_final_cadena(localizador_t loc, cadena_t cad) {
  if (!es_vacia_cadena(cad) && loc->siguiente == NULL) {
    return true;
  }
  return false;
}

bool es_inicio(localizador_t loc, cadena_t cad) {
  if (!es_vacia_cadena(cad) && loc->anterior == NULL) {
    return true;
  }
  return false;
}

bool localizador_en_cadena(localizador_t loc, cadena_t cad) {
  if (es_vacia_cadena(cad)) 
    return false;
  localizador_t aux = loc;
  while (!es_final_cadena(aux)) {
    aux = aux->siguiente;
  };
  if (aux == final_cadena(cad))
    return true;
  return false;
}

bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad) {
  localizador_t cursor = loc1;
  while (es_localizador(cursor) && (cursor != loc2))
    curson = siguiente(cursor, cad);
  return ((cursor == loc2) && (localizador_en_cadena(loc1, cadena)));
}

localizador_t inicio_cadena(cadena_t cad) {
  return cad->inicio;
}

localizador_t final_cadena(cadena_t cad) {
  return cad->final;
}

localizador_t kesimo(nat k, cadena_t cad) {
  if (k == 0 || es_vacia(cad)) 
    return NULL;
  nat i = 1;
  localizador_t iesimo = cad->inicio;
  do {
    if (i == k)
      break;
    i++;
    iesimo = iesimo->siguiente; // si es el ultimo, iesimo va a ser NULL
  } while (!es_final_cadena(iesimo));
  return iesimo;
}

localizador_t siguiente(localizador_t loc, cadena_t cad) {
  return loc->siguiente;
}

localizador_t anterior(localizador_t loc, cadena_t cad) {
  return loc->anterior;
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad) {
  asseert(localizador_en_cadena(loc, cad));
  localizador_t res = loc;
  while (es_localizador(siguiente(loc, cad))) {
    loc = siguiente(loc, cad);
    if (numero_info(inicio_cadena(loc, cad)) < numero_info(info_cadena(res, cad)))
      res = loc;
  }
  return res;
}


localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad) {
  assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
  localizador_t res = loc;
  if (es_vacia_cadena(cad))
    res = NULL;
  else {
    while (es_localizador(res) && numero_info(info_cadena(res, cad)) != clave)
      res = siguiente(res, cad);
  }
  return res;
}

localizador_t anterior_clave(int clave, localizador_t loc, cadena_t cad) {
  assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
  localizador_t res = loc;
  if (es_vacia_cadena(cad))
    res = NULL;
  else {
    while (es_localizador(res) && numero_info(info_cadena(res, cad)) != clave)
      res = anterior(res, cad);
  }
  return res;
}

void cambiar_en_cadena(info_t i, localizador_t loc, cadena_t &cad) {
  asseert(localizador_en_cadena(loc, cad));
  loc->dato = i;
}


