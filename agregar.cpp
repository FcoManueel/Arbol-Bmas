#include <iostream>
#include "arbol_b.h"
#include "tipos.h"
#include "auxiliares.h"

bool Arbol::agregar(int k)
{
    Info info = buscar(k);

    int i = info.indice;
    bool encontrado = info.encontrado;
    Nodo *n = info.donde;

    if(encontrado) return false;

    Registro *r = crear_registro(k);

    if(nodo_lleno(n)){
        switch(se_puede_rotar_al_agregar(n)){
        case 0: agregar_en_nodo_lleno(n, k, i, r); break;
        case 1: agregar_y_pasar_al_izquierdo(n, k, r); break;
        case 2: agregar_y_pasar_al_derecho(n, k, r); break;
        }
    }else{
        agregar_en_nodo_no_lleno(n, k, i, r);
    }
    return true;
}

void Arbol::agregar_en_nodo_no_lleno(Nodo *n, int k, int i, Registro *r)
{
    desplazar_en_hoja_a_la_derecha(n, i, n->cuantas_llaves-1, 1);
    n->llaves[i] = k;
    n->datos[i] = r;
    ++(n->cuantas_llaves);
}

int Arbol::se_puede_rotar_al_agregar(Nodo *n)
{
    Nodo *a = n->anterior;
    Nodo *s = n->siguiente;
    if(a != NULL && !(nodo_lleno(a)) && a->padre == n->padre){
        return 1;
    }else if(s != NULL && !(nodo_lleno(s)) && s->padre == n->padre){
        return 2;
    }else{
        return 0;
    }
}

void Arbol::agregar_en_nodo_lleno(Nodo *n, int k, int i, Registro *r)
{
    Nodo *p, *n_s;
    int k_s;
    bool parar;

    if(n == raiz){
        agregar_y_partir_raiz(n, k, i, r);
    }else{
        do{
            p = n->padre;
            if(n->es_hoja)
                parar = agregar_y_partir_hoja(n, k, i, r, n_s, k_s);
            else
                parar = agregar_y_partir_intermedio(n, n_s, k_s);
            n = p;
        }while(parar == false);
    }
}

void Arbol::agregar_y_partir_raiz(Nodo *n, int k, int i, Registro *r)
{
    Nodo *copia = new Nodo;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->datos = new Registro*[orden+1];
    copiar_hoja(n, copia, 0, orden-1, 0);
    desplazar_en_hoja_a_la_derecha(copia, i, orden-1, 1);
    copia->llaves[i] = k;
    copia->datos[i] = r;

    Nodo *hermano = new Nodo;
    hermano->llaves = new int[orden];
    hermano->datos = new Registro*[orden];

    int mitad = (orden+1)/2;
    copiar_hoja(copia, n, 0, mitad-1, 0);
    copiar_hoja(copia, hermano, mitad, orden, 0);
    n->cuantas_llaves = mitad;
    hermano->cuantas_llaves = orden+1 - mitad;

    hermano->siguiente = n->siguiente;
    n->siguiente = hermano;
    hermano->anterior = n;

    Nodo *nueva_raiz = new Nodo;
    nueva_raiz->es_hoja = false;
    nueva_raiz->llaves = new int[orden];
    nueva_raiz->hijos = new Nodo*[orden+1];

    nueva_raiz->llaves[0] = hermano->llaves[0];
    nueva_raiz->cuantas_llaves = 1;
    nueva_raiz->hijos[0] = n;
    nueva_raiz->hijos[1] = hermano;
    n->padre = nueva_raiz;
    hermano->padre = nueva_raiz;

    raiz = nueva_raiz;
    principio = n;
    final = hermano;

    delete copia;
}

bool Arbol::agregar_y_partir_hoja(Nodo *n,int k,int i,Registro *r,Nodo *&n_s,int &k_s)
{
    Nodo *p = n->padre;
    int i_padre = buscar_hijo_en_nodo(p, n->llaves[0]);
    Nodo *copia = new Nodo;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->datos = new Registro*[orden+1];
    copiar_hoja(n, copia, 0, orden-1, 0);
    desplazar_en_hoja_a_la_derecha(copia, i, orden-1, 1);
    copia->llaves[i] = k;
    copia->datos[i] = r;

    Nodo *hermano = new Nodo;
    hermano->llaves = new int[orden];
    hermano->datos = new Registro*[orden];

    int mitad = (orden+1)/2;
    copiar_hoja(copia, n, 0, mitad-1, 0);
    copiar_hoja(copia, hermano, mitad, orden, 0);
    n->cuantas_llaves = mitad;
    hermano->cuantas_llaves = orden+1 - mitad;

    hermano->siguiente = n->siguiente;
    n->siguiente = hermano;
    hermano->anterior = n;
    if(n == final)
        final = hermano;
    else
        hermano->siguiente->anterior = hermano;

    k_s = hermano->llaves[0];
    n_s = hermano;

    delete copia;

    if(!nodo_lleno(p)){
        desplazar_en_intermedio_a_la_derecha(p, i_padre, p->cuantas_llaves-1, 1);
        p->llaves[i_padre] = k_s;
        p->hijos[i_padre+1] = n_s;
        ++(p->cuantas_llaves);
        n_s->padre = p;
        return true;
    }
    return false;
}

bool Arbol::agregar_y_partir_intermedio(Nodo *n, Nodo *&n_s, int &k_s)
{
    Nodo *p = n->padre;
    int i_padre;
    Nodo *copia = new Nodo;
    copia->es_hoja = false;
    copia->cuantas_llaves = orden;
    copia->llaves = new int[orden+1];
    copia->hijos = new Nodo*[orden+2];
    copiar_intermedio(n, copia, 0, orden-1, 0);
    i_padre = buscar_hijo_en_nodo(copia, k_s);
    desplazar_en_intermedio_a_la_derecha(copia, i_padre, orden-1, 1);
    copia->llaves[i_padre] = k_s;
    copia->hijos[i_padre+1] = n_s;

    Nodo *hermano = new Nodo;
    hermano->es_hoja = false;
    hermano->llaves = new int[orden];
    hermano->hijos = new Nodo*[orden+1];

    int mitad = (orden+1)/2;
    copiar_intermedio(copia, n, 0, mitad-1, 0);
    copiar_intermedio(copia, hermano, mitad+1, orden, 0);
    n->cuantas_llaves = mitad;
    hermano->cuantas_llaves = orden - mitad;

    for(int j=0; j<=n->cuantas_llaves; ++j)
        n->hijos[j]->padre = n;
    for(int j=0; j<=hermano->cuantas_llaves; ++j)
        hermano->hijos[j]->padre = hermano;

    hermano->siguiente = n->siguiente;
    n->siguiente = hermano;
    hermano->anterior = n;

    if(hermano->siguiente != NULL)
        hermano->siguiente->anterior = hermano;
    n_s = hermano;
    k_s = copia->llaves[mitad];

    delete copia;

    if(p != NULL && !nodo_lleno(p)){
        i_padre = buscar_hijo_en_nodo(p, k_s);
        desplazar_en_intermedio_a_la_derecha(p, i_padre, p->cuantas_llaves-1, 1);
        p->llaves[i_padre] = k_s;
        p->hijos[i_padre+1] = n_s;
        n_s->padre = p;
        ++(p->cuantas_llaves);
        return true;
    }
    if(n == raiz){
        Nodo *nueva_raiz = new Nodo;
        nueva_raiz->es_hoja = false;
        nueva_raiz->llaves = new int[orden];
        nueva_raiz->hijos = new Nodo*[orden+1];

        nueva_raiz->llaves[0] = k_s;
        ++(nueva_raiz->cuantas_llaves);
        nueva_raiz->hijos[0] = n;
        nueva_raiz->hijos[1] = n_s;
        n->padre = nueva_raiz;
        n_s->padre = nueva_raiz;

        raiz = nueva_raiz;
        return true;
    }
    return false;
}

void Arbol::agregar_y_pasar_al_izquierdo(Nodo *n, int k, Registro *r)
{
    Nodo *p = n->padre;
    Nodo *a = n->anterior;
    int i_padre = buscar_hijo_en_nodo(p, n->llaves[0])-1;
    int i;

    if(k < n->llaves[0]){
        a->llaves[a->cuantas_llaves] = k;
        a->datos[a->cuantas_llaves]  = r;
        ++(a->cuantas_llaves);
        p->llaves[i_padre] = n->llaves[0];
    }else{
        a->llaves[a->cuantas_llaves] = n->llaves[0];
        a->datos[a->cuantas_llaves]  = n->datos[0];
        ++(a->cuantas_llaves);
        desplazar_en_hoja_a_la_izquierda(n, 1, n->cuantas_llaves-1, 1);
        --(n->cuantas_llaves);
        i = buscar_llave_en_nodo(n, k);
        agregar_en_nodo_no_lleno(n, k, i, r);
        p->llaves[i_padre] = n->llaves[0];
    }
}

void Arbol::agregar_y_pasar_al_derecho(Nodo *n, int k, Registro *r)
{
    Nodo *p = n->padre;
    Nodo *s = n->siguiente;
    int i_padre = buscar_hijo_en_nodo(p, s->llaves[0])-1;
    int i;

    if(k > n->llaves[n->cuantas_llaves-1]){
        desplazar_en_hoja_a_la_derecha(s, 0, s->cuantas_llaves-1, 1);
        s->llaves[0] = k;
        s->datos[0]  = r;
        ++(s->cuantas_llaves);
        p->llaves[i_padre] = k;
    }else{
        desplazar_en_hoja_a_la_derecha(s, 0, s->cuantas_llaves-1, 1);
        s->llaves[0] = n->llaves[n->cuantas_llaves-1];
        s->datos[0]  = n->datos[n->cuantas_llaves-1];
        ++(s->cuantas_llaves);
        --(n->cuantas_llaves);
        i = buscar_llave_en_nodo(n, k);
        agregar_en_nodo_no_lleno(n, k, i, r);
        p->llaves[i_padre] = s->llaves[0];
    }
}
