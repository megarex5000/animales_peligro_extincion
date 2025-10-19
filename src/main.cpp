#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include "../models/Especie.h"
#include "db.h"

using namespace std;

// ===== Funciones =====

string minusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

void mostrarEstadisticas(vector<Especie>& animales);
void porcentajePorCategoria(vector<Especie>& animales);
void menuGraficacion();
void menuANOVA();
void agruparPorCategoria(vector<Especie>& animales);
void ordenarPorPoblacion(vector<Especie>& animales);
void buscarPorHabitat(vector<Especie>& animales);
void buscarPorNombre(vector<Especie>& animales);
void mostrarCausasExtincion(vector<Especie>& animales);
void listarPorID(vector<Especie>& animales);

// ===== Implementaciones =====

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
        string cat = minusculas(animales[i].categoria);
        if (cat == "mamifero") mamiferos++;
        else if (cat == "ave") aves++;
        else if (cat == "reptil") reptiles++;
        else otros++;
    }

    cout << "\n--- Porcentaje por Categoria ---\n";
    cout << "Mamiferos: " << (mamiferos * 100.0 / total) << "%\n";
    cout << "Aves: " << (aves * 100.0 / total) << "%\n";
    cout << "Reptiles: " << (reptiles * 100.0 / total) << "%\n";
    cout << "Otros: " << (otros * 100.0 / total) << "%\n";
}

void menuGraficacion() {
    cout << "\n--- Menú Graficación ---\n";
    cout << "Funcionalidad pendiente.\n";
}

void menuANOVA() {
    cout << "\n--- Menu ANOVA ---\n";
    cout << "Funcionalidad pendiente.\n";
}

void agruparPorCategoria(vector<Especie>& animales) {
    cout << "\n--- Agrupacion por Categoria ---\n";
    string categorias[] = {"mamifero", "ave", "reptil", "otro"};

    for (int c = 0; c < 4; c++) {
        cout << "\n*** " << categorias[c] << " ***\n";
        bool encontrado = false;

        for (size_t i = 0; i < animales.size(); i++) {
            if (minusculas(animales[i].categoria) == categorias[c]) {
                cout << left << setw(5) << animales[i].id
                     << setw(20) << animales[i].nombre
                     << setw(15) << animales[i].categoria
                     << setw(20) << animales[i].habitat
                     << setw(10) << animales[i].poblacion << endl;
                encontrado = true;
            }
        }
        if (!encontrado) cout << "No hay animales en esta categoria.\n";
    }
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
    cout << "\nLista ordenada por poblacion descendente:\n";
    cout << left << setw(5) << "ID" << setw(20) << "Nombre" << setw(15) << "Categoria" << setw(20) << "Habitat" << setw(10) << "Poblacion" << endl;
    for (size_t i = 0; i < animales.size(); i++) {
        cout << left << setw(5) << animales[i].id
             << setw(20) << animales[i].nombre
             << setw(15) << animales[i].categoria
             << setw(20) << animales[i].habitat
             << setw(10) << animales[i].poblacion << endl;
    }
}

void buscarPorHabitat(vector<Especie>& animales) {
    string habitat;
    cout << "Ingrese habitat: ";
    cin.ignore();
    getline(cin, habitat);
    habitat = minusculas(habitat);

    bool encontrado = false;
    cout << left << setw(5) << "ID" << setw(20) << "Nombre" << setw(15) << "Categoria" << setw(20) << "Habitat" << setw(10) << "Poblacion" << endl;
    for (size_t i = 0; i < animales.size(); i++) {
        if (minusculas(animales[i].habitat).find(habitat) != string::npos) {
            cout << left << setw(5) << animales[i].id
                 << setw(20) << animales[i].nombre
                 << setw(15) << animales[i].categoria
                 << setw(20) << animales[i].habitat
                 << setw(10) << animales[i].poblacion << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron animales en ese habitat.\n";
}

void buscarPorNombre(vector<Especie>& animales) {
    string buscar;
    cout << "Nombre del animal: ";
    cin.ignore();
    getline(cin, buscar);
    buscar = minusculas(buscar);

    bool encontrado = false;
    cout << left << setw(5) << "ID" << setw(20) << "Nombre" << setw(15) << "Categoria" << setw(20) << "Habitat" << setw(10) << "Poblacion" << endl;
    for (size_t i = 0; i < animales.size(); i++) {
        if (minusculas(animales[i].nombre).find(buscar) != string::npos) {
            cout << left << setw(5) << animales[i].id
                 << setw(20) << animales[i].nombre
                 << setw(15) << animales[i].categoria
                 << setw(20) << animales[i].habitat
                 << setw(10) << animales[i].poblacion << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "Animal no encontrado.\n";
}

void mostrarCausasExtincion(vector<Especie>& animales) {
    cout << left << setw(20) << "Nombre"
         << setw(15) << "Categoria"
         << setw(20) << "Habitat"
         << setw(30) << "Causa de extincion" << endl;

    for (size_t i = 0; i < animales.size(); i++) {
        cout << left << setw(20) << animales[i].nombre
             << setw(15) << animales[i].categoria
             << setw(20) << animales[i].habitat;

        if (minusculas(animales[i].categoria) == "mamifero") cout << setw(30) << "Caza furtiva, pérdida de hábitat";
        else if (minusculas(animales[i].categoria) == "ave") cout << setw(30) << "Destrucción de hábitat, contaminación";
        else if (minusculas(animales[i].categoria) == "reptil") cout << setw(30) << "Cambio climático, tráfico ilegal";
        else cout << setw(30) << "Factores desconocidos";

        cout << endl;
    }
}

void listarPorID(vector<Especie>& animales) {
    for (size_t i = 0; i < animales.size(); i++) {
        for (size_t j = i + 1; j < animales.size(); j++) {
            if (animales[i].id > animales[j].id) {
                Especie temp = animales[i];
                animales[i] = animales[j];
                animales[j] = temp;
            }
        }
    }

    cout << left << setw(5) << "ID"
         << setw(20) << "Nombre"
         << setw(15) << "Categoria"
         << setw(20) << "Habitat"
         << setw(10) << "Poblacion" << endl;

    for (size_t i = 0; i < animales.size(); i++) {
        cout << left << setw(5) << animales[i].id
             << setw(20) << animales[i].nombre
             << setw(15) << animales[i].categoria
             << setw(20) << animales[i].habitat
             << setw(10) << animales[i].poblacion << endl;
    }
}

// ===== MAIN =====

int main() {
    DB db;
    if (!db.abrirDB("../data/animales.db")) {
        cout << "No se pudo abrir la base de datos.\n";
        return 1;
    }

    vector<Especie> animales = db.cargarAnimales();
    if (animales.empty()) {
        cout << "No hay animales en la base de datos.\n";
        return 1;
    }

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
        cout << "10. Causas de extincion\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: listarPorID(animales); break;
            case 2: buscarPorNombre(animales); break;
            case 3: mostrarEstadisticas(animales); break;
            case 4: porcentajePorCategoria(animales); break;
            case 5: menuGraficacion(); break;
            case 6: menuANOVA(); break;
            case 7: agruparPorCategoria(animales); break;
            case 8: ordenarPorPoblacion(animales); break;
            case 9: buscarPorHabitat(animales); break;
            case 10: mostrarCausasExtincion(animales); break;
        }
    } while (opcion != 0);
    db.cerrarDB();
    return 0;
}
