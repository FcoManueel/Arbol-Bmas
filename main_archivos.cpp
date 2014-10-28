#include <iostream>
#include <fstream>
#include "arbol_b.h"
#include "tipos.h"

using namespace std;

int main()
{
    Arbol *a = new Arbol(4);

    int k;

    cout<<" -- se lee el archivo 'datos' con valores separados por espacios o enters --\n -- estos valores se agregaran al arbol b+ --\n";
    cin.get();
    ifstream datos("datos");
    while(datos>>k){
        a->agregar(k);
    }
    
    cout<<" -- se lee el archivo 'borrar' con valores separados por espacios o enters --\n -- estos valores se borraran al arbol b+ --\n";
    cin.get();
    ifstream borrar("borrar");
    while(borrar>>k){
        a->borrar(k);
    }

    cout<<" -- se completaron las operaciones de agregar y borrar --\n -- ahora se guardan los valores ordenados del arbol resultante en un archivo llamado 'resultado' --\n";
    cin.get();
    ofstream resultado;
    resultado.open("resultado");
    Nodo *n = a->get_principio();
    while(n != NULL){
        for(int i=0; i<n->cuantas_llaves; ++i)
            resultado<<n->datos[i]->valor<<" ";
        n = n->siguiente;
    }
    
    delete a;
}
