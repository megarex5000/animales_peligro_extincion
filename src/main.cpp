#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib> // Para system()
#include "Especie.h"

using namespace std;

// Función para convertir string a int sin stoi
int stringToInt(const string& str) {
    int num = 0;
    stringstream ss(str);
    ss >> num;
    return num;
}

int main() {
    vector<Especie> animales;
    string line;

    // Leer CSV desde data en bin/Debug/
    ifstream file("data/animales.csv");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo animales.csv" << endl;
        system("pause");
        return 1;
    }

    // Saltar encabezado
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Especie e;
        string temp;

        getline(ss, temp, ';');
        e.id = stringToInt(temp);

        getline(ss, e.nombre, ';');
        getline(ss, e.categoria, ';');
        getline(ss, e.habitat, ';');

        getline(ss, temp, ';');
        e.poblacion = stringToInt(temp);

        animales.push_back(e);
    }
    file.close();

    if (animales.empty()) {
        cout << "No hay animales cargados desde el CSV." << endl;
        system("pause");
        return 1;
    }

    int opcion;
    do {
        cout << "\n--- Animales en Peligro Bolivia ---\n";
        cout << "1. Listar todos los animales\n";
        cout << "2. Buscar animal por nombre\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        cin.ignore();

        if (opcion == 1) {
            cout << "\nID | Nombre | Categoria | Habitat | Poblacion\n";
            for (size_t i = 0; i < animales.size(); i++) {
                animales[i].mostrar();
            }
        }
        else if (opcion == 2) {
            string buscar;
            cout << "Nombre del animal: ";
            getline(cin, buscar);
            bool encontrado = false;
            for (size_t i = 0; i < animales.size(); i++) {
                if (animales[i].nombre == buscar) {
                    animales[i].mostrar();
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "Animal no encontrado.\n";
        }

    } while (opcion != 0);

    return 0;
}
