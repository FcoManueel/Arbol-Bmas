#include <iostream>
#include "arbol.h"

Informacion Arbol::buscar(int llave)
{
    Informacion info;
    /* info.encontrado :: true/false
     * info.donde      :: Nodo* hoja
     * info.indice     :: int no negativo
     */
    Nodo* x; // Apuntador que recorre el arbol
    int   i; // Indice del elemento

    x = raiz_;
    while(true){
        i = 0;
        
        // Búsqueda lineal sobre las llaves de x
        while((i < x->cuantas_llaves_) && (llave > x->llaves_[i])){
            i++;
        }

        // Revisar si la llave se encuentra en el arbol
        if((i < x->cuantas_llaves_) && (llave == x->llaves_[i])){
            info.encontrado = true;
        }

        // Revisar si el nodo es hoja
        if(x->es_hoja_ == true){
            info.donde      = x;
            info.indice     = i;
            return info;
        }else{
            if(llave == x->llaves_[i])
                i++; // Las llaves se encuentran en el hijo derecho
            x = x->hijos_[i];
       }
    }
}

bool Arbol::agregar(int llave)
{
    
    Informacion info = buscar(llave);
    
    if(info.encontrado){
        std::cout<<"llave "<<llave<<" ya existe\n";
        return false;
    }
    
    Nodo* x = info.donde;
    if(x->esta_lleno()){
        std::cout<<"el nodo esta lleno\n";
        return false;
        // Acomodar el arbol para que el nodo donde
        // se tiene que insertar no este lleno.
    }
    insert_nonfull(x,llave,info.indice);
    x->pintar();

    return true;
}

void Arbol::insert_nonfull(Nodo* x, int k, int i)
{
    // inserta en el nodo x la llave k en el indice i,
    // se considera a x como un nodo hoja no-lleno.
    Registro* r = new Registro;
    r->llave = k;
    
    for(int j=x->cuantas_llaves_; j>i; --j){
        x->llaves_[j] = x->llaves_[j-1];
        x->datos_[j] = x->datos_[j-1];
    }
    
    x->llaves_[i] = k;
    x->datos_[i] = r;
    ++(x->cuantas_llaves_);
}


void Arbol::split_child(Nodo* x, int i)
{
    // En esta funcion x es un nodo no-hoja no-lleno
    // que cumple con x->hijos_[i] es un nodo lleno
    
    Nodo* z = new Nodo;     // z sera hermano de y
    Nodo* y = x->hijos_[i]; // y es un nodo lleno
    int   t = maximo_llaves_por_nodo - maximo_llaves_por_nodo/2;

    // se pasa la segunda mitad de y a la primer mitad de z
    for(int j=0; j<t; ++j){
        z->llaves_[j] = y->llaves_[j+t];
    }
    // se pasa la segunda mitad de los hijos/datos de y a z
    if(y->es_hoja_){
        for(int j=0; j<t; ++j)
            z->datos_[j] = y->datos_[j+t];
    }else{
        for(int j=0; j<=t; ++j)
            z->hijos_[j] = y->hijos_[j+t];
    }

    y->cuantas_llaves_ = maximo_llaves_por_nodo/2;
    z->cuantas_llaves_ = t;

    for(int j=x->cuantas_llaves_+1; j > i+1; --j){
        x->hijos_[j] = x->hijos_[j-1];
    }
    x->hijos_[i+1] = z;

    for(int j=x->cuantas_llaves_; j > i; --j){
        x->llaves_[j] = x->llaves_[j-1];
    }
    x->llaves_[i] = z->llaves_[0];
    ++(x->cuantas_llaves_); 
}
