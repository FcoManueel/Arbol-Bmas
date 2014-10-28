#include <iostream>
#include "tipos.h"
#include "arbol_b.h"
#include "auxiliares.h"

int Nodo::max_llaves;

// Construccion info
Info::Info()
{
    encontrado = false;
    donde = NULL;
    indice = -1;
}

// Destruccion info
Info::~Info()
{
    donde = NULL;
}

// Construccion nodo
Nodo::Nodo()
{
    cuantas_llaves = 0;
    es_hoja = true;
    padre = siguiente = anterior = NULL;
}
Nodo::Nodo(int o)
{
    cuantas_llaves = 0;
    es_hoja = true;
    padre = siguiente = anterior = NULL;
    max_llaves = o;
}

// Destruccion nodo
Nodo::~Nodo()
{
    delete[] llaves;
    if(es_hoja)
        delete[] datos;
    else
        delete[] hijos;
    padre = siguiente = anterior = NULL;
}

// Construccion arbol
void Arbol::inicializar()
{
    raiz = new Nodo(orden);
    raiz->llaves = new int[orden];
    raiz->datos  = new Registro*[orden];
    principio = final = raiz;
}
Arbol::Arbol(int o)
{
    orden = o;
    inicializar();
}

// Destruccion arbol
void Arbol::borrar_nivel(Nodo *n)
{
    Nodo *aux;
    while(n){
        aux = n->siguiente;
        if(n->es_hoja)
            eliminar_registros_en_nodo(n);
        delete n;
        n = aux;
    }
}
Arbol::~Arbol()
{
    Nodo *aux;
    Nodo *n = raiz;
    while(n->es_hoja == false){
        aux = n->hijos[0];
        borrar_nivel(n);
        n = aux;
    }
    borrar_nivel(n);
    principio = final = raiz = NULL;
}
