#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include "ListaUsuarios.h"
#include "Tarea.h"
#include <vector>
#include <string>
using namespace std;

// Clase que gestiona la carga y guardado de usuarios desde y hacia archivos
class GestorArchivos {
public:
    // Metodo para cargar usuarios desde un archivo
    static void cargarUsuarios(const string& archivo, ListaUsuarios& lista);
    // Metodo para guardar usuarios en un archivo
    static void guardarUsuarios(const string& archivo, ListaUsuarios& lista);
    static bool cargarTareas(const string& archivo, vector<Tarea>& tareas);
    static bool guardarTareas(const string& archivo, const vector<Tarea>& tareas);
};

#endif // GESTORARCHIVOS_H