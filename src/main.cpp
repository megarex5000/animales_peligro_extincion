#include <iostream> /// Causas de extincion, tabular los datos y base de datos.
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm> // Para transform
#include "../models/Especie.h"

using namespace std;

// Función para convertir string a int sin stoi
int stringToInt(string str) {
    int num = 0;
    stringstream ss(str);
    ss >> num;
    return num;
}

// Función para pasar string a minúsculas y quitar espacios al inicio y fin
string toLowerTrim(string str) {
    while (!str.empty() && isspace(str[0])) str.erase(0, 1);
    while (!str.empty() && isspace(str[str.size() - 1])) str.erase(str.size() - 1, 1);
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void mostrarEstadisticas(vector<Especie>& animales) {
    if (animales.empty()) return;

    int totalPoblacion = 0;
    int maxPoblacion = animales[0].poblacion;
    int minPoblacion = animales[0].poblacion;

    for (size_t i = 0; i < animales.size(); i++) {
        totalPoblacion += animales[i].poblacion;
        if (animales[i].poblacion > maxPoblacion) maxPoblacion = animales[i].poblacion;
        if (animales[i].poblacion < minPoblacion) minPoblacion = animales[i].poblacion;
    }

    double promedio = (double)totalPoblacion / animales.size();

    cout << "\n--- Estadisticas Generales ---\n";
    cout << "Total especies: " << animales.size() << endl;
    cout << "Poblacion total: " << totalPoblacion << endl;
    cout << "Poblacion promedio: " << promedio << endl;
    cout << "Maxima poblacion: " << maxPoblacion << endl;
    cout << "Minima poblacion: " << minPoblacion << endl;
}

void porcentajePorCategoria(vector<Especie>& animales) {
    if (animales.empty()) return;

    int total = animales.size();
    int mamiferos = 0, aves = 0, reptiles = 0, otros = 0;

    for (size_t i = 0; i < animales.size(); i++) {
        if (toLowerTrim(animales[i].categoria) == "mamifero") mamiferos++;
        else if (toLowerTrim(animales[i].categoria) == "ave") aves++;
        else if (toLowerTrim(animales[i].categoria) == "reptil") reptiles++;
        else otros++;
    }

    cout << "\n--- Porcentaje por Categoría ---\n";
    cout << "Mamiferos: " << (mamiferos * 100.0 / total) << "%\n";
    cout << "Aves: " << (aves * 100.0 / total) << "%\n";
    cout << "Reptiles: " << (reptiles * 100.0 / total) << "%\n";
    cout << "Otros: " << (otros * 100.0 / total) << "%\n";
}

void menuGraficacion() {
    cout << "\n--- Menú Graficación ---\n";
    cout << "Funcionalidad pendiente (Python).\n";
}

void menuANOVA() {
    cout << "\n--- Menú ANOVA ---\n";
    cout << "Funcionalidad pendiente.\n";
}

void agruparPorCategoria(vector<Especie>& animales) {
    cout << "\n--- Agrupación por Categoría ---\n";
    porcentajePorCategoria(animales);
}

void ordenarPorPoblacion(vector<Especie>& animales) {
    for (size_t i = 0; i < animales.size(); i++) {
        for (size_t j = i + 1; j < animales.size(); j++) {
            if (animales[i].poblacion < animales[j].poblacion) {
                Especie temp = animales[i];
                animales[i] = animales[j];
                animales[j] = temp;
            }
        }
    }
    cout << "\nLista ordenada por población descendente:\n";
    cout << "ID | Nombre | Categoria | Habitat | Poblacion\n";
    for (size_t i = 0; i < animales.size(); i++) {
        animales[i].mostrar();
    }
}

void buscarPorHabitat(vector<Especie>& animales) {
    string habitat;
    cout << "Ingrese habitat: ";
    cin.ignore();
    getline(cin, habitat);
    habitat = toLowerTrim(habitat);

    bool encontrado = false;
    for (size_t i = 0; i < animales.size(); i++) {
        if (toLowerTrim(animales[i].habitat) == habitat) {
            animales[i].mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron animales en ese habitat.\n";
}

int main() {
    vector<Especie> animales;
    string line;

    ifstream file("../data/animales.csv");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo animales.csv\n";
        system("pause");
        return 1;
    }

    getline(file, line); // Saltar encabezado
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

    int opcion;
    do {
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Listar todos los animales\n";
        cout << "2. Buscar animal por nombre\n";
        cout << "3. Estadisticas generales\n";
        cout << "4. Porcentaje por categoria\n";
        cout << "5. Graficacion\n";
        cout << "6. ANOVA\n";
        cout << "7. Agrupar por categoria\n";
        cout << "8. Ordenar por poblacion\n";
        cout << "9. Buscar por habitat\n";
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
            buscar = toLowerTrim(buscar);
            bool encontrado = false;
            for (size_t i = 0; i < animales.size(); i++) {
                if (toLowerTrim(animales[i].nombre) == buscar) {
                    animales[i].mostrar();
                    encontrado = true;
                }
            }
            if (!encontrado) cout << "Animal no encontrado.\n";
        }
        else if (opcion == 3) {
            mostrarEstadisticas(animales);
        }
        else if (opcion == 4) {
            porcentajePorCategoria(animales);
        }
        else if (opcion == 5) {
            menuGraficacion();
        }
        else if (opcion == 6) {
            menuANOVA();
        }
        else if (opcion == 7) {
            agruparPorCategoria(animales);
        }
        else if (opcion == 8) {
            ordenarPorPoblacion(animales);
        }
        else if (opcion == 9) {
            buscarPorHabitat(animales);
        }

    } while (opcion != 0);

    return 0;
}
