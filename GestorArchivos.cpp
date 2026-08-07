#include "GestorArchivos.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Metodo para cargar usuarios desde un archivo
void GestorArchivos::cargarUsuarios(const string& archivo, ListaUsuarios& lista) {
    ifstream file(archivo);
    string linea;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string idStr, nombre, contrasena, rolStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, contrasena, ',');
        getline(ss, rolStr, ',');

        int id = stoi(idStr);

        // Normalizar rol a minúsculas
        transform(rolStr.begin(), rolStr.end(), rolStr.begin(), ::tolower);

        Usuario::Rol rol = (rolStr == "admin") ? Usuario::ADMIN : Usuario::NORMAL;

        Usuario u(id, nombre, contrasena, rol);
        lista.agregarUsuario(u);
    }
}

// Metodo para guardar usuarios en un archivo
void GestorArchivos::guardarUsuarios(const string& archivo, ListaUsuarios& lista) {
    // Aquí se implementaría la escritura en CSV recorriendo la lista
}