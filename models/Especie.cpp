#include "Especie.h"
#include <iostream>

void Especie::mostrar() {
    std::cout << id << " | "
              << nombre << " | "
              << categoria << " | "
              << habitat << " | "
              << poblacion << std::endl;
}
