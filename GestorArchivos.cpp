#include "GestorArchivos.h"
#include <fstream>
#include <sstream>
using namespace std;

// Metodo para cargar usuarios desde un archivo
void GestorArchivos::cargarUsuarios(const string& archivo, ListaUsuarios& lista) {
    ifstream file(archivo); // Abrir el archivo para lectura
    string linea; // Variable para almacenar cada línea del archivo

    // Leer cada línea del archivo y procesarla
    while (getline(file, linea)) {
        stringstream ss(linea);
        int id; string nombre, contrasena, rolStr;
        getline(ss, rolStr, ','); // formato CSV: id,nombre,contrasena,rol
        id = stoi(rolStr);
        getline(ss, nombre, ',');
        getline(ss, contrasena, ',');
        getline(ss, rolStr, ',');
        Usuario::Rol rol = (rolStr == "ADMIN") ? Usuario::ADMIN : Usuario::NORMAL;
        lista.agregarUsuario(Usuario(id, nombre, contrasena, rol));
    }
}

// Metodo para guardar usuarios en un archivo
void GestorArchivos::guardarUsuarios(const string& archivo, ListaUsuarios& lista) {
    // Aquí se implementaría la escritura en CSV recorriendo la lista
}