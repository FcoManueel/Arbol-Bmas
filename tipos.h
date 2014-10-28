/**
 * NOMBRE_DE_ARCHIVO:
 *   tipos.h
 * DESCRIPCION:
 *   Cabecera de los tipos de datos utilizados en el Arbol B+.
 * AUTORES:
 *   Acuña Yeomans Eduardo
 *   Valle Ruiz Francisco Manuel
 */

#ifndef TIPOS_H_
#define TIPOS_H_

struct Registro{
    int valor;
};

struct Nodo
{
    Nodo *padre;
    Nodo *siguiente;
    Nodo *anterior;
    
    static int max_llaves;
    int  cuantas_llaves;
    bool es_hoja;

    int *llaves;
    union {
        Registro **datos;
        Nodo **hijos;
    };

    Nodo();
    Nodo(int o);
    ~Nodo();
};

struct Info
{
    bool encontrado;
    Nodo *donde;
    int indice;

    Info();
    ~Info();
};

#endif  // TIPOS_H_
