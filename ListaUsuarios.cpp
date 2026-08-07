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
    return (u && u->getContrasena() == contrasena);
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

// Metodo para eliminar un usuario por su ID
bool ListaUsuarios::eliminarUsuario(int id) {
    NodoUsuario* actual = cabeza;
    while (actual) {
        if (actual->usuario.getId() == id) {
            // Caso: único nodo
            if (actual == cabeza && actual == cola) {
                cabeza = cola = nullptr;
            }
            // Caso: eliminar cabeza
            else if (actual == cabeza) {
                cabeza = cabeza->siguiente;
                if (cabeza) cabeza->anterior = nullptr;
            }
            // Caso: eliminar cola
            else if (actual == cola) {
                cola = cola->anterior;
                if (cola) cola->siguiente = nullptr;
            }
            // Caso: nodo intermedio
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            return true;
        }
        actual = actual->siguiente;
    }
    return false; // no encontrado
}