#include <iostream>
#include <fstream>
#include "arbol_b.h"
#include "auxiliares.h"
#include "menu.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
    int n_datos;
    if(argv[1]){
        n_datos = atoi(argv[1]);
    }else{
        cout << "Cuantos datos deseas agregar? ";
        cin >> n_datos;
    }
    
    srand(time(NULL));
    Arbol *a = new Arbol(4);
    
    int r;
    for(int i=0; i<n_datos; ++i){
        //r = rand()%(n_datos*4);
        r = i;
        a->agregar(r);
    }
    cout << "Listo!".
    // a->pintar();
    
    menu();
    int op, op_buscar, k, aux;
    while(op != -1){
        cout << "Que desea hacer?  ";
        cin >> op;

        switch(op){
            case 0: // Menu
                menu();
                break;
            case 1: // Agregar
                cout << "Que numero desea agregar? ";
                cin >> k;
                if(a->agregar(k)){
                    cout << "\t~ El elemento fue agregado con exito! ~\n";
                    a->pintar();
                }else{
                    a->pintar();
                    cout << "\t~ El elemento no pudo ser agregado :( ~\n";
                }
                break;
            case 2: // Borrar
                cout << "Que numero desea borrar? ";
                cin >> k;
                if(a->borrar(k)){
                    cout << "\t~ El elemento fue borrado con exito! ~\n";
                    a->pintar();
                }else{
                    a->pintar();
                    cout << "\t~ El elemento no pudo ser borrado :( ~\n";
                }
                break;
            case 3: // Buscar
                menu_buscar();
                cout << "Que desea hacer?  ";
                cin >> op_buscar;

                switch(op_buscar){
                    default:
                    case 0: //Menu anterior
                        // Simplemente no se hace nada; el menu se imprime siempre al terminar del switch-case
                        break;
                    case 1: // Buscar elemento
                        cout << "Que numero desea buscar? ";
                        cin >> k;
                        if(a->se_encuentra(k)){
                            cout << "\t~ Se encontro el elemento en el arbol! ~\n";
                        }else{
                            cout << "\t~ No se encontro el elemento en el arbol :( ~\n";
                        }
                        break;
                    case 2: // Busqueda de rango
                        cout << "Ingrese la cota izquierda del rango: ";
                        cin >> k;
                        cout << "Ingrese la cota derecha del rango: ";
                        cin >> aux;
                        cout << "\n";
                        a->buscar_rango(k,aux);
                        break;
                    case 3: // Buscar mayor a...
                        cout << "Buscar todos los elementos (igual o) mayores a: ";
                        cin >> k;
                        a->mayores_a(k);
                        break;
                    case 4: // Buscar menor a...
                        cout << "Buscar todos los elementos (igual o) menores a: ";
                        cin >> k;
                        a->menores_a(k);
                        break;
                    case 5: // Elemento menor
                        aux = a->elemento_menor();
                        if(aux == -999999){
                            cout << "\t~ El arbol esta vacio :( ~\n";
                        }else{
                            cout << "\t~ El elemento menor es el "<<aux<<" ~\n";
                        }
                        break;
                    case 6: // Elemento mayor
                        aux = a->elemento_mayor();
                        if(aux == 999999){
                            cout << "\t~ El arbol esta vacio :( ~\n";
                        }else{
                            cout << "\t~ El elemento mayor es el "<<aux<<" ~\n";
                        }
                        break;
                }
                cout << "\n";
                menu();
                break;
            case 4: // Pintar
                a->pintar();
                break;
            case -1: // Salir
                cout << "\t~ Ahi nos washamos";
                break;
            default:
                cout << "\t~ No mijo, que andas haciendo :( da una opcion valida, paro ~\n";
        }
    }
    cin.ignore();
    cin.get();
    return 0;
}
