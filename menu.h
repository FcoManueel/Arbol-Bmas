/**
 * NOMBRE_DE_ARCHVIO:
 *   menu.h
 *
 * DESCRIPCION:
 *   Rutina que imprime en pantalla el menu de opciones disponibles en el Arbol B+.
 *
 * AUTORES:
 *   Acuña Yeomans Eduardo
 *   Valle Ruiz Francisco Manuel
 */

#ifndef MENU_
#define MENU_

#include <iostream>

void menu(){
    std::cout << "\n\t";
    std::cout << char(201);
    for (int i = 0; i < 28 ; ++i) std::cout << char(205);
    std::cout << char(187);
    std::cout << "\n\t" << char(186) << "                            " << char(186);
    std::cout << "\n\t" << char(186) << "  0: Imprimir este men"<<char(163)<<"     " << char(186);
    std::cout << "\n\t" << char(186) << "  1: Agregar elemento       " << char(186);
    std::cout << "\n\t" << char(186) << "  2: Borrar elemento        " << char(186);
    std::cout << "\n\t" << char(186) << "  3: Buscar                 " << char(186);
    std::cout << "\n\t" << char(186) << "  4: Pintar como lista      " << char(186);
    std::cout << "\n\t" << char(186) << "  -1: Salir                 " << char(186);
    std::cout << "\n\t" << char(186) << "                            " << char(186);
    std::cout << "\n\t";
    std::cout << char(200);
    for (int i = 0; i < 28 ; ++i) std::cout << char(205);
    std::cout << char(188);
    std::cout << "\n\n";
    //std::cout << "\n\t--------------------------\n\n";
}

void menu_buscar(){
    std::cout << "\n\t";
    std::cout << char(201);
    for (int i = 0; i < 7 ; ++i) std::cout << char(205);
    std::cout << " Busquedas ";
    for (int i = 0; i < 6 ; ++i) std::cout << char(205);
    std::cout << char(187);
    std::cout << "\n\t" << char(186) << "                        " << char(186);
    std::cout << "\n\t" << char(186) << "  0: Men"<<char(163)<<" anterior      " << char(186);
    std::cout << "\n\t" << char(186) << "  1: Buscar elemento    " << char(186);
    std::cout << "\n\t" << char(186) << "  2: Busqueda de rango  " << char(186);
    std::cout << "\n\t" << char(186) << "  3: Buscar mayores a.. " << char(186);
    std::cout << "\n\t" << char(186) << "  4: Buscar menores a.. " << char(186);
    std::cout << "\n\t" << char(186) << "  5: Elemento menor     " << char(186);
    std::cout << "\n\t" << char(186) << "  6: Elemento mayor     " << char(186);
    std::cout << "\n\t" << char(186) << "                        " << char(186);
    std::cout << "\n\t";
    std::cout << char(200);
    for (int i = 0; i < 24 ; ++i) std::cout << char(205);
    std::cout << char(188);
    std::cout << "\n\n";
    //std::cout << "\n\t--------------------------\n\n";
}

#endif //_MENU_
