#include "db.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

DB::DB() {
    db = NULL;
}

DB::~DB() {
    cerrarDB();
}

bool DB::abrirDB(string ruta) {
    int rc = sqlite3_open(ruta.c_str(), &db);
    if (rc) {
        cout << "Error al abrir DB: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

void DB::cerrarDB() {
    if (db) sqlite3_close(db);
}

vector<Especie> DB::cargarAnimales() {
    vector<Especie> lista;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, nombre, categoria, habitat, poblacion FROM animales";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        cout << "Error preparando consulta: " << sqlite3_errmsg(db) << endl;
        return lista;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Especie e;
        e.id = sqlite3_column_int(stmt, 0);
        e.nombre = (char*)sqlite3_column_text(stmt, 1);
        e.categoria = (char*)sqlite3_column_text(stmt, 2);
        e.habitat = (char*)sqlite3_column_text(stmt, 3);
        e.poblacion = sqlite3_column_int(stmt, 4);
        lista.push_back(e);
    }

    sqlite3_finalize(stmt);
    return lista;
}
