#include <iostream>
#include "arbol_b.h"
#include "tipos.h"
#include "auxiliares.h"

Info Arbol::buscar(int k)
{
    Info info;

    int i;
    bool encontrado;
    Nodo *n;
    
    n = buscar_hoja(raiz, k);
    i = buscar_llave_en_nodo(n, k);
    encontrado = (i < n->cuantas_llaves && k == n->llaves[i]);
        
    info.encontrado = encontrado;
    info.indice = i;
    info.donde = n;

    return info;
}

Nodo *Arbol::buscar_hoja(Nodo *n, int k)
{
    int i;
    while(n->es_hoja == false){
        i = buscar_hijo_en_nodo(n, k);
        n = n->hijos[i];
    }
    return n;
}
