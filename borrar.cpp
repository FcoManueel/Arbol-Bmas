#include <iostream>
#include "arbol_b.h"
#include "tipos.h"
#include "auxiliares.h"

bool Arbol::borrar(int k)
{
    Info info = buscar(k);

    bool encontrado = info.encontrado;
    Nodo *n = info.donde;
    int i = info.indice;
    
    if(!encontrado) return false;

    if(nodo_a_mitad(n) && n != raiz){
        switch(se_puede_rotar_al_borrar(n)){
        case 0: borrar_en_nodo_a_mitad(n, k, i); break;
        case 1: borrar_y_agarrar_del_izquierdo(n, k, i); break;
        case 2: borrar_y_agarrar_del_derecho(n, k, i); break;
        }
    }else{
        borrar_en_nodo_mediolleno(n, k, i);
    }
    return true;
}

void Arbol::borrar_en_nodo_mediolleno(Nodo *n, int k, int i)
{
    Registro *r = n->datos[i];

    desplazar_en_hoja_a_la_izquierda(n, i+1, n->cuantas_llaves-1, 1);
    --(n->cuantas_llaves);

    delete r;
}

int Arbol::se_puede_rotar_al_borrar(Nodo *n)
{
    Nodo *a = n->anterior;
    Nodo *s = n->siguiente;
    if(a != NULL && !(nodo_a_mitad(a)) && a->padre == n->padre){
        return 1;
    }else if(s != NULL && !(nodo_a_mitad(s)) && s->padre == n->padre){
        return 2;
    }else{
        return 0;
    }
}

void Arbol::borrar_en_nodo_a_mitad(Nodo *n, int k, int i)
{
    Nodo *p;
    bool parar;
    
    do{
        p = n->padre;
        if(n->es_hoja){
            parar = borrar_y_fusionar_hoja(n, k, i);
        }else{
            switch(se_puede_rotar_al_borrar(n)){
            case 0: parar = borrar_y_fusionar_intermedio(n, k, i); break;
            case 1: borrar_y_agarrar_del_izquierdo(n, k, i); parar = true; break;
            case 2: borrar_y_agarrar_del_derecho(n, k, i); parar = true; break;
            }
        }
        if(parar == false){
            n = p;
        }
    }while(parar == false);
}

bool Arbol::borrar_y_fusionar_hoja(Nodo *n, int k, int i)
{
    Nodo *p = n->padre;
    Nodo *a = n->anterior;
    Nodo *s = n->siguiente;
    int i_padre;
    
    bool parar = true;
    if(nodo_a_mitad(p) && p != raiz) parar = false;

    borrar_en_nodo_mediolleno(n, k, i);

    if(a != NULL && a->padre == p){
        i_padre = buscar_hijo_en_nodo(p, n->llaves[0])-1;
        copiar_hoja(n, a, 0, n->cuantas_llaves-1, a->cuantas_llaves);
        a->cuantas_llaves += n->cuantas_llaves;
        desplazar_en_intermedio_a_la_izquierda(p, i_padre+1, p->cuantas_llaves-1, 1);
        --(p->cuantas_llaves);
        a->siguiente = n->siguiente;
        if(s)
            s->anterior = a;
        else
            final = a;
        n->cuantas_llaves = 0;
        delete n;
        if(p == raiz && p->cuantas_llaves == 0){
            delete p;
            raiz = a;
            a->padre = NULL;
            parar = true;
        }
    }else{
        i_padre = buscar_hijo_en_nodo(p, s->llaves[0])-1;
        copiar_hoja(s, n, 0, s->cuantas_llaves-1, n->cuantas_llaves);
        n->cuantas_llaves += s->cuantas_llaves;
        desplazar_en_intermedio_a_la_izquierda(p, i_padre+1, p->cuantas_llaves-1, 1);
        --(p->cuantas_llaves);
        n->siguiente = s->siguiente;
        if(n->siguiente)
            n->siguiente->anterior = n;
        else
            final = n;
        s->cuantas_llaves = 0;
        delete s;
        if(p == raiz && p->cuantas_llaves == 0){
            delete p;
            raiz = n;
            n->padre = NULL;
            parar = true;
        }
    }
    return parar;
}

bool Arbol::borrar_y_fusionar_intermedio(Nodo *n, int k, int i)
{
    Nodo *p = n->padre;
    Nodo *a = n->anterior;
    Nodo *s = n->siguiente;
    int i_padre;
    
    bool parar = true;
    if(nodo_a_mitad(p) && p != raiz) parar = false;

    if(a != NULL && a->padre == p){
        i_padre = buscar_hijo_en_nodo(p, n->llaves[0])-1;
        a->llaves[a->cuantas_llaves] = p->llaves[i_padre];
        ++(a->cuantas_llaves);
        desplazar_en_intermedio_a_la_izquierda(p, i_padre+1, p->cuantas_llaves-1, 1);
        --(p->cuantas_llaves);
        copiar_intermedio(n, a, 0, n->cuantas_llaves-1, a->cuantas_llaves);
        for(int j=0; j <= n->cuantas_llaves; ++j) n->hijos[j]->padre = a;
        a->cuantas_llaves += n->cuantas_llaves;
        n->cuantas_llaves = 0;
        a->siguiente = s;
        if(s)
            s->anterior = a;
        delete n;
        if(p == raiz && p->cuantas_llaves == 0){
            delete p;
            raiz = a;
            a->padre = NULL;
            parar = true;
        }
    }else{
        i_padre = buscar_hijo_en_nodo(p, s->llaves[0])-1;
        n->llaves[n->cuantas_llaves] = p->llaves[i_padre];
        ++(n->cuantas_llaves);
        desplazar_en_intermedio_a_la_izquierda(p, i_padre+1, p->cuantas_llaves-1, 1);
        --(p->cuantas_llaves);
        copiar_intermedio(s, n, 0, s->cuantas_llaves-1, n->cuantas_llaves);
        for(int j=0; j <= s->cuantas_llaves; ++j) s->hijos[j]->padre = n;
        n->cuantas_llaves += s->cuantas_llaves;
        s->cuantas_llaves = 0;
        n->siguiente = s->siguiente;
        if(n->siguiente)
            n->siguiente->anterior = n;
        delete s;
        if(p == raiz && p->cuantas_llaves == 0){
            delete p;
            raiz = n;
            n->padre = NULL;
            parar = true;
        }
    }
    return parar;
}

void Arbol::borrar_y_agarrar_del_izquierdo(Nodo *n, int k, int i)
{
    Nodo *p = n->padre;
    Nodo *a = n->anterior;
    int i_padre = buscar_hijo_en_nodo(p, n->llaves[0])-1;
    if(n->es_hoja){
        borrar_en_nodo_mediolleno(n, k, i);
        desplazar_en_hoja_a_la_derecha(n, 0, n->cuantas_llaves-1, 1);
        n->llaves[0] = a->llaves[a->cuantas_llaves-1];
        n->datos[0] = a->datos[a->cuantas_llaves-1];
        p->llaves[i_padre] = n->llaves[0];
        --(a->cuantas_llaves);
        ++(n->cuantas_llaves);
    }else{
        desplazar_en_intermedio_a_la_derecha(n, 0, n->cuantas_llaves-1, 1);
        n->hijos[1] = n->hijos[0];
        n->llaves[0] = p->llaves[i_padre];
        n->hijos[0] = a->hijos[a->cuantas_llaves];
        n->hijos[0]->padre = n;
        p->llaves[i_padre] = a->llaves[a->cuantas_llaves-1];
        --(a->cuantas_llaves);
        ++(n->cuantas_llaves);
    }
}

void Arbol::borrar_y_agarrar_del_derecho(Nodo *n, int k, int i)
{
    Nodo *p = n->padre;
    Nodo *s = n->siguiente;
    int i_padre = buscar_hijo_en_nodo(p, s->llaves[0])-1;
    if(n->es_hoja){
        borrar_en_nodo_mediolleno(n, k, i);
        n->llaves[n->cuantas_llaves] = s->llaves[0];
        n->datos[n->cuantas_llaves]  = s->datos[0];
        desplazar_en_hoja_a_la_izquierda(s, 1, s->cuantas_llaves-1, 1);
        --(s->cuantas_llaves);
        ++(n->cuantas_llaves);
        p->llaves[i_padre] = s->llaves[0];
    }else{
        n->llaves[n->cuantas_llaves] = p->llaves[i_padre];
        n->hijos[n->cuantas_llaves+1] = s->hijos[0];
        s->hijos[0]->padre = n;
        p->llaves[i_padre] = s->llaves[0];
        s->hijos[0] = s->hijos[1];
        desplazar_en_intermedio_a_la_izquierda(s, 1, s->cuantas_llaves-1, 1);
        --(s->cuantas_llaves); 
        ++(n->cuantas_llaves);
    }
}
