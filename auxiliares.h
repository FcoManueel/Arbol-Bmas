/**
 * NOMBRE_DE_ARCHIVO:
 *   auxiliares.h
 *
 * DESCRIPCION:
 *   Funciones auxiliares del Arbol B+.
 *
 * AUTORES:
 *   Acuña Yeomans Eduardo
 *   Valle Ruiz Francisco Manuel
 */

#ifndef AUXILIARES_H_
#define AUXILIARES_H_

#include <iostream>
#include "tipos.h"
#include "arbol_b.h"

bool nodo_lleno(Nodo *n);
bool nodo_a_mitad(Nodo *n);

int buscar_hijo_en_nodo(Nodo *n, int k);
int buscar_llave_en_nodo(Nodo *n, int k);
Nodo *buscar_hoja(Nodo *n, int k);

Registro *crear_registro(int k);

void desplazar_en_hoja_a_la_izquierda(Nodo *n, int desde, int hasta, int e);
void desplazar_en_intermedio_a_la_izquierda(Nodo *n, int desde, int hasta, int e);
void desplazar_en_hoja_a_la_derecha(Nodo *n, int desde, int hasta, int e);
void desplazar_en_intermedio_a_la_derecha(Nodo *n, int desde, int hasta, int e);

void copiar_hoja(Nodo *origen, Nodo *destino, int desde, int hasta, int e);
void copiar_intermedio(Nodo *origen, Nodo *destino, int desde, int hasta, int e);

void eliminar_registros_en_nodo(Nodo *n);

void pintar_nodo(Nodo *n);
void pintar_nodo_sin_formato(Nodo *n);
void pintar_nivel(Nodo *n);
void pintar_nivel_detalle(Nodo *n);
void inspeccionar_nodo(Nodo *n);

#endif  // AUXILIARES_H_
