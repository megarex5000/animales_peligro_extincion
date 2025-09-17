#ifndef ESPECIE_H
#define ESPECIE_H

#include <string>
#include <iostream>

class Especie {
public:
    int id;
    std::string nombre;
    std::string categoria;
    std::string habitat;
    int poblacion;

    void mostrar();
};

#endif
