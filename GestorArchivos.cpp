#include "GestorArchivos.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

// Metodo para cargar usuarios desde un archivo
void GestorArchivos::cargarUsuarios(const string& archivo, ListaUsuarios& lista) {
    ifstream file(archivo);
    if (!file) return;
    string linea;

    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, nombre, contrasena, rolStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, contrasena, ',');
        getline(ss, rolStr, ',');

        int id;
        try {
            id = stoi(idStr);
        } catch (const exception&) {
            continue;
        }
        if (nombre.empty() || contrasena.empty() || lista.existeUsuario(id)) continue;

        // Normalizar rol a minúsculas
        transform(rolStr.begin(), rolStr.end(), rolStr.begin(), ::tolower);

        Usuario::Rol rol = (rolStr == "admin") ? Usuario::ADMIN : Usuario::NORMAL;

        Usuario u(id, nombre, contrasena, rol);
        lista.agregarUsuario(u);
    }
}

// Metodo para guardar usuarios en un archivo
void GestorArchivos::guardarUsuarios(const string& archivo, ListaUsuarios& lista) {
    ofstream file(archivo);
    NodoUsuario* actual = lista.getCabeza();
    while (actual) {
        file << actual->usuario.getId() << ","
             << actual->usuario.getNombre() << ","
             << actual->usuario.getContrasena() << ","
             << (actual->usuario.getRol() == Usuario::ADMIN ? "admin" : "normal")
             << "\n";
        actual = actual->siguiente;
    }
}

bool GestorArchivos::cargarTareas(const string& archivo, vector<Tarea>& tareas) {
    ifstream file(archivo);
    if (!file) return false;
    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        string campo[6];
        stringstream ss(linea);
        for (int i = 0; i < 6 && getline(ss, campo[i], ','); ++i) {}
        try {
            Tarea tarea(stoi(campo[0]), campo[1], stoi(campo[2]), stoi(campo[3]));
            tarea.setEstado(static_cast<Tarea::Estado>(stoi(campo[4])));
            if (!campo[5].empty()) tarea.setCiclosEspera(stoi(campo[5]));
            tareas.push_back(tarea);
        } catch (const exception&) {
            continue;
        }
    }
    return true;
}

bool GestorArchivos::guardarTareas(const string& archivo, const vector<Tarea>& tareas) {
    ofstream file(archivo);
    if (!file) return false;
    for (const Tarea& tarea : tareas) {
        file << tarea.getId() << ',' << tarea.getTitulo() << ','
             << tarea.getPrioridad() << ',' << tarea.getResponsableId() << ','
             << static_cast<int>(tarea.getEstado()) << ',' << tarea.getCiclosEspera() << "\n";
    }
    return true;
}