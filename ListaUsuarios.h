#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "Usuario.h"
using namespace std;

// Clase que representa un nodo en la lista de usuarios
class NodoUsuario {
public:
    // Atributos del nodo
    Usuario usuario;
    NodoUsuario* siguiente;
    NodoUsuario* anterior;

    // Constructor del nodo
    NodoUsuario(Usuario u);
};

// Clase que representa la lista de usuarios
class ListaUsuarios {
private:
    // Punteros al primer y último nodo de la lista
    NodoUsuario* cabeza;
    NodoUsuario* cola;

public:
    // Constructor de la lista
    ListaUsuarios();

    // Metodos para manipular la lista de usuarios
    void agregarUsuario(Usuario u);
    Usuario* buscarUsuario(int id);
    bool validarCredenciales(int id, string contrasena);
    void listarUsuarios();
};

#endif // LISTAUSUARIOS_H