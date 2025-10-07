#ifndef ESPECIE_H
#define ESPECIE_H

#include <string>
#include <iostream>
using namespace std;

class Especie {
public:
    int id;
    string nombre;
    string categoria;
    string habitat;
    int poblacion;

    Especie();
    void mostrar();
};

#endif
