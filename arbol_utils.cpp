#include <iostream>
#include "arbol.h"

Arbol::Arbol()
{
    maximo_hijos_por_nodo = 5;
    maximo_llaves_por_nodo = 4;
    minimo_llaves_por_nodo = 2;
    llenado_minimo = .5;
    raiz_ = new Nodo;
    principio_ = raiz_;
    final_ = raiz_;

}

Nodo::Nodo()
{
    std::cout<<"raiz="<<this<<"\n";
    llaves_ = new int[maximo_llaves_por_nodo];
    datos_  = new Registro*[maximo_hijos_por_nodo];
    
    cuantas_llaves_ = 0;
    es_hoja_        = true;
    padre_          = NULL;
    siguiente_      = NULL;
    anterior_       = NULL;
}

Informacion::Informacion()
{
    encontrado = false;
    donde      = NULL;
    indice     = 0;
}

bool Nodo::esta_lleno()
{
    return this->cuantas_llaves_ >= maximo_llaves_por_nodo;
}

void Nodo::pintar()
{
    std::cout<<"Nodo{"<<this<<"} n="<<this->cuantas_llaves_<<"\n";
    std::cout<<"[";
    for(int i=0; i<this->cuantas_llaves_;i++){
        std::cout<<this->llaves_[i]<<"|";
    }
    std::cout<<"\b]\n";
    if(this->es_hoja_){
        std::cout<<"[";
        for(int i=0; i<this->cuantas_llaves_;i++){
            std::cout<<this->datos_[i]->llave<<"|";
        }
        std::cout<<"\b]\n";
    }
}

void Nodo::pintar_dir()
{
    std::cout<<"Nodo{"<<this<<"}\n";
    std::cout<<"[";
    for(int i=0; i<this->cuantas_llaves_;i++){
       std::cout<<this->llaves_[i]<<"|";
    }
    std::cout<<"\b]\n";
    if(this->es_hoja_){
        std::cout<<"[";
        for(int i=0; i<this->cuantas_llaves_;i++){
            std::cout<<this->datos_[i]<<"|";
        }
        std::cout<<"\b]\n";
    }
}

void Nodo::pintar_all()
{
    std::cout<<"Nodo{"<<this<<"}\n";
    std::cout<<"[";
    for(int i=0; i<maximo_llaves_por_nodo;i++){
       std::cout<<this->llaves_[i]<<"|";
    }
    std::cout<<"\b]\n";
    if(this->es_hoja_){
        std::cout<<"[";
        for(int i=0; i<maximo_llaves_por_nodo;i++){
            std::cout<<this->datos_[i]<<"|";
        }
        std::cout<<"\b]\n";
    }
}
