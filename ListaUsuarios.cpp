#include "ListaUsuarios.h"
#include <iostream>
using namespace std;

// Constructor del nodo
NodoUsuario::NodoUsuario(Usuario u) : usuario(u), siguiente(nullptr), anterior(nullptr) {}

// Constructor de la lista
ListaUsuarios::ListaUsuarios() : cabeza(nullptr), cola(nullptr) {}

// Metodo para agregar un usuario a la lista
void ListaUsuarios::agregarUsuario(Usuario u) {
    NodoUsuario* nuevo = new NodoUsuario(u);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

// Metodo para buscar un usuario por su ID
Usuario* ListaUsuarios::buscarUsuario(int id) {
    NodoUsuario* actual = cabeza;
    while (actual) {
        if (actual->usuario.getId() == id) return &actual->usuario;
        actual = actual->siguiente;
    }
    return nullptr;
}

// Metodo para validar las credenciales de un usuario
bool ListaUsuarios::validarCredenciales(int id, string contrasena) {
    Usuario* u = buscarUsuario(id);
    if (u && u->getContrasena() == contrasena) return true;
    return false;
}

// Metodo para listar todos los usuarios
void ListaUsuarios::listarUsuarios() {
    NodoUsuario* actual = cabeza;
    while (actual) {
        cout << "ID: " << actual->usuario.getId()
            << " Nombre: " << actual->usuario.getNombre() << endl;
        actual = actual->siguiente;
    }
}