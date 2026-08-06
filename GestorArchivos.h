#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include "ListaUsuarios.h"
#include <string>
using namespace std;

// Clase que gestiona la carga y guardado de usuarios desde y hacia archivos
class GestorArchivos {
public:
    // Metodo para cargar usuarios desde un archivo
    static void cargarUsuarios(const string& archivo, ListaUsuarios& lista);
    // Metodo para guardar usuarios en un archivo
    static void guardarUsuarios(const string& archivo, ListaUsuarios& lista);
};

#endif // GESTORARCHIVOS_H