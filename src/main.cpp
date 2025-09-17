#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "../models/Especie.h"

using namespace std;

int main() {
    vector<Especie> animales;
    string line;

    // Leer CSV
    ifstream file("../data/animales.csv");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo animales.csv" << endl;

    // Saltar encabezado
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Especie e;
        string temp;

        getline(ss, temp, ','); e.id = stoi(temp);
        getline(ss, e.nombre, ',');
        getline(ss, e.categoria, ',');
        getline(ss, e.habitat, ',');
        getline(ss, temp, ','); e.poblacion = stoi(temp);

        animales.push_back(e);
    }
    file.close();

    // Men� simple
    int opcion;
    do {
        cout << "\n--- Animales en Peligro Bolivia ---\n";
        cout << "1. Listar todos los animales\n";
        cout << "2. Buscar animal por nombre\n";
        cout << "0. Salir\n";
        cout << "Opci�n: "; cin >> opcion;

        cin.ignore(); // Limpiar buffer

        if (opcion == 1) {
            cout << "\nID | Nombre | Categoria | Habitat | Poblacion\n";
            for (auto &a : animales) a.mostrar();
        } else if (opcion == 2) {
            string buscar;
            cout << "Nombre del animal: "; getline(cin, buscar);
            bool encontrado = false;
            for (auto &a : animales) {
                if (a.nombre == buscar) {
                    a.mostrar();
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "Animal no encontrado.\n";
        }

    } while (opcion != 0);

    return 0;
}
