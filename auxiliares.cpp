#include "auxiliares.h"

bool Arbol::arbol_vacio(){
    return principio->cuantas_llaves <= 0;
}

bool nodo_lleno(Nodo *n)
{
    return n->cuantas_llaves >= n->max_llaves;
}

bool nodo_a_mitad(Nodo *n)
{
    return n->cuantas_llaves == (n->max_llaves/2);
}

int buscar_hijo_en_nodo(Nodo *n, int k)
{
    int i = 0;
    while(i < n->cuantas_llaves && k >= n->llaves[i])
        ++i;
    return i;
}

int buscar_llave_en_nodo(Nodo *n, int k)
{
    int i = 0;
    while(i < n->cuantas_llaves && k > n->llaves[i])
        ++i;
    return i;
}

void copiar_hoja(Nodo *origen, Nodo *destino, int desde, int hasta, int e)
{
    int j, k;
    for(j=desde, k = e; j <= hasta; ++j, ++k){
        destino->llaves[k] = origen->llaves[j];
        destino->datos[k]  = origen->datos[j];
    }
}

void copiar_intermedio(Nodo *origen, Nodo *destino, int desde, int hasta, int e)
{
    int j, k;
    for(j=desde, k = e; j <= hasta; ++j, ++k){
        destino->llaves[k] = origen->llaves[j];
        destino->hijos[k]  = origen->hijos[j];
    }
    destino->hijos[k] = origen->hijos[j];
}

Registro *crear_registro(int k)
{
    Registro *r = new Registro;
    r->valor = k;
    return r;
}

void desplazar_en_hoja_a_la_izquierda(Nodo *n, int desde, int hasta, int e)
{
    for(int j = desde-e; j<=hasta-e; ++j){
        n->llaves[j] = n->llaves[j+e];
        n->datos[j]  = n->datos[j+e];
    }
}

void desplazar_en_intermedio_a_la_izquierda(Nodo *n, int desde, int hasta, int e)
{
    for(int j = desde-e; j<=hasta-e; ++j){
        n->llaves[j]  = n->llaves[j+e];
        n->datos[j+1] = n->datos[j+e+1];
    }
}

void desplazar_en_hoja_a_la_derecha(Nodo *n, int desde, int hasta, int e)
{
    for(int j = hasta+e; j >= desde+e; --j){
        n->llaves[j] = n->llaves[j-e];
        n->datos[j]  = n->datos[j-e];
    }
}

void desplazar_en_intermedio_a_la_derecha(Nodo *n, int desde, int hasta, int e)
{
    for(int j = hasta+e; j >= desde+e; --j){
        n->llaves[j]  = n->llaves[j-e];
        n->hijos[j+1] = n->hijos[j-e+1];
    }
}

void eliminar_registros_en_nodo(Nodo *n)
{
    for(int i=0; i<n->cuantas_llaves; ++i)
        delete n->datos[i];
}

void inspeccionar_nodo(Nodo *n)
{
    std::cout<<"NODO:"<<n<<" ";
    if(n)
        pintar_nodo(n);
    std::cout<<"\n";
    std::cout<<"  padre:"<<n->padre<<" ";
    if(n->padre)
        pintar_nodo(n->padre);
    std::cout<<"\n";
    std::cout<<"  h_izq:"<<n->anterior<<" ";
    if(n->anterior)
        pintar_nodo(n->anterior);
    std::cout<<"\n";
    std::cout<<"  h_der:"<<n->siguiente<<" ";
    if(n->siguiente)
        pintar_nodo(n->siguiente);
    std::cout<<"\n";
    
    if(n->es_hoja){
        std::cout<<"  registros:";
        for(int i=0; i<n->cuantas_llaves; ++i)
            std::cout<<n->datos[i]->valor<<" ";
    }else{
        std::cout<<"  hijos:";
        for(int i=0; i<=n->cuantas_llaves; ++i)
            pintar_nodo(n->hijos[i]);
    }
    std::cout<<"\n";
}

void pintar_nodo(Nodo *n)
{
    if(n->es_hoja)
        std::cout<<"h";
    std::cout<<"( ";
    for(int j=0; j<n->cuantas_llaves; j=j+1)
        std::cout<<n->llaves[j]<<" ";
    std::cout<<") ";
}

void pintar_nodo_sin_formato(Nodo *n){
    for(int j=0; j<n->cuantas_llaves; ++j)
        std::cout<<n->llaves[j]<<" ";
}

void pintar_nivel(Nodo *n)
{
    while(n){
        pintar_nodo(n);
        n = n->siguiente;
    }
    std::cout<<"\n";
}
void pintar_nivel_detalle(Nodo *n)
{
    while(n){
        inspeccionar_nodo(n);
        n = n->siguiente;
    }
    std::cout<<"\n";
}
void Arbol::pintar(bool detalle)
{
    Nodo *n = raiz;
    if(raiz->cuantas_llaves == 0){
        std::cout<<"\nEl arbol esta vacio.\n";
        return;
    }
    while(!(n->es_hoja)){
        if(detalle)
            pintar_nivel_detalle(n);
        else
            pintar_nivel(n);
        n = n->hijos[0];
    }
    if(detalle)
        pintar_nivel_detalle(principio);
    else
        pintar_nivel(principio);
    std::cout<<"\n";
}

// Funciones auxiliares para busquedas
bool Arbol::se_encuentra(int k){
    Info i;
    i = buscar(k);
    return i.encontrado;
}

void Arbol::buscar_rango(int rango_i, int rango_f){
    if(rango_i > rango_f){
        rango_i ^= rango_f;
        rango_f ^= rango_i;
        rango_i ^= rango_f;
    }

    Nodo* n;
    int i;
    n = buscar_hoja(raiz, rango_i);
    i = buscar_llave_en_nodo(n, rango_i);

    if(arbol_vacio() || (i<n->cuantas_llaves && n->llaves[i]>rango_f) || principio->llaves[0]>rango_f){
        std::cout<<"\t~No se encontro ningun elemento en el rango dado~\n";
        return;
    }

    if(i >= n->cuantas_llaves ){ // también funciona con ==
        if(n->siguiente){
            n = n->siguiente;
            i = 0;
        }else{
            std::cout<<"\t~No se encontro ningun elemento en el rango dado~\n";
        }
    }

    std::cout<<"( ";
    for(int j=i; j<n->cuantas_llaves; ++j){
        if(n->llaves[j]<=rango_f){
            std::cout<<n->llaves[j]<<" ";
        }else{
            std::cout<<") ";
            return;
        }
    }

    while(n->siguiente){
        n = n->siguiente;
        for(int j=0; j<n->cuantas_llaves; ++j)
        if(n->llaves[j]<=rango_f){
            std::cout<<n->llaves[j]<<" ";
        }else{
            std::cout<<") ";
            return;
        }
    }
    std::cout<<") ";
}

void Arbol::mayores_a(int k){
    Nodo* n;
    int i;
    n = buscar_hoja(raiz, k);
    i = buscar_llave_en_nodo(n, k);

    if(i >= n->cuantas_llaves ){ // también funciona con ==
        if(n->siguiente){
            n = n->siguiente;
            i = 0;
        }else{
            std::cout<<"\t~No se encontro ningun elemento mayor a "<<k<<"~\n";
        }
    }

    std::cout<<"( ";
    for(int j=i; j<n->cuantas_llaves; ++j)
        std::cout<<n->llaves[j]<<" ";

    while(n->siguiente){
        n = n->siguiente;
        pintar_nodo_sin_formato(n);
    }
    std::cout<<")\n";
}

void Arbol::menores_a(int k){
    Nodo *n, *nodo_actual;
    int i;
    n = buscar_hoja(raiz, k);
    i = buscar_llave_en_nodo(n, k);
    
    if(i>=n->cuantas_llaves || n->llaves[i] > k){
        std::cout<<"\t~No se encontro ningun elemento menor a "<<k<<"~\n";
        return;
    }
        
    nodo_actual = principio;
    std::cout<<"( ";
    while(nodo_actual != n){
        pintar_nodo_sin_formato(nodo_actual);
        nodo_actual = nodo_actual->siguiente;
    }

    for(int j=0; j<i; ++j)
        std::cout<<n->llaves[j]<<" ";
    if(i<n->cuantas_llaves)
        std::cout<<n->llaves[i]<<" ";
    
    std::cout<<")\n";
}

int Arbol::elemento_mayor(){
    return arbol_vacio() ? final->llaves[final->cuantas_llaves-1] : 999999;
}

int Arbol::elemento_menor(){
    return arbol_vacio() ? principio->llaves[0] : -999999;
}