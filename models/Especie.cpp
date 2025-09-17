#include "Especie.h"
#include <iostream>

void Especie::mostrar() {  // Definición de la función
    std::cout << id << " | "
              << nombre << " | "
              << categoria << " | "
              << habitat << " | "
              << poblacion << std::endl;
}
