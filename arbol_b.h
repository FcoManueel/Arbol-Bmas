/**
 * NOMBRE_DE_ARCHIVO:
 *   arbol_b.h
 * DESCRIPCION:
 *   Cabecera de la clase del Arbol B+.
 * AUTORES:
 *   Acuña Yeomans Eduardo
 *   Valle Ruiz Francisco Manuel
 */

#ifndef ARBOL_B_H_
#define ARBOL_B_H_

#include "tipos.h"

class Arbol
{
    Nodo *raiz;
    Nodo *principio;
    Nodo *final;
    int orden;

public:
    Arbol(int o = 4);
    ~Arbol();

    Info buscar(int k);
    bool agregar(int k);
    bool borrar(int k);

    void pintar(bool detalle = false);
    bool se_encuentra(int k);
    void buscar_rango(int n_ini, int n_fin);
    void mayores_a(int k);
    void menores_a(int k);

    int elemento_mayor();
    int elemento_menor();

    Nodo *get_principio(){return principio;};

protected:
    Nodo *buscar_hoja(Nodo *n, int k);
    bool arbol_vacio();
    
    void agregar_en_nodo_lleno(Nodo *n, int k, int i, Registro *r);
    void agregar_en_nodo_no_lleno(Nodo *n, int k, int i, Registro *r);
    bool agregar_y_partir_hoja(Nodo *n, int k, int i, Registro *r,Nodo *&n_s,int &k_s);
    bool agregar_y_partir_intermedio(Nodo *n, Nodo *&n_s, int &k_s);
    void agregar_y_partir_raiz(Nodo *n, int k, int i, Registro *r);
    int  se_puede_rotar_al_agregar(Nodo *n);
    void agregar_y_pasar_al_izquierdo(Nodo *n, int k, Registro *r);
    void agregar_y_pasar_al_derecho(Nodo *n, int k, Registro *r);

    void borrar_en_nodo_mediolleno(Nodo *n, int k, int i);
    void borrar_en_nodo_a_mitad(Nodo *n, int k, int i);
    bool borrar_y_fusionar_hoja(Nodo *n, int k, int i);
    bool borrar_y_fusionar_intermedio(Nodo *n, int k, int i);
    int  se_puede_rotar_al_borrar(Nodo *n);
    void borrar_y_agarrar_del_izquierdo(Nodo *n, int k, int i);
    void borrar_y_agarrar_del_derecho(Nodo *n, int k, int i);
    
    void inicializar();
    void borrar_nivel(Nodo *n);
};

#endif  // ARBOL_B_H_
