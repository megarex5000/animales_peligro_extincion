#include "Especie.h"
#include <iostream>

void Especie::mostrar() {  // Definici�n de la funci�n
    std::cout << id << " | "
              << nombre << " | "
              << categoria << " | "
              << habitat << " | "
              << poblacion << std::endl;
}
