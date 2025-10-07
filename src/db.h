#ifndef DB_H
#define DB_H

#include <vector>
#include <string>
#include "../models/Especie.h"
#include "../sqlite/sqlite3.h"

using namespace std;

class DB {
public:
    sqlite3* db;

    DB();
    ~DB();

    bool abrirDB(string ruta);
    void cerrarDB();
    vector<Especie> cargarAnimales();
};

#endif
