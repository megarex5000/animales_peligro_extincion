#include "Especie.h"
#include <iostream>
#include <iomanip>

Especie::Especie() {
    id = 0;
    nombre = "";
    categoria = "";
    habitat = "";
    poblacion = 0;
}

void Especie::mostrar() {
    cout << id << " | "
         << nombre << " | "
         << categoria << " | "
         << habitat << " | "
         << poblacion << endl;
}
