#include "Usuario.h"
using namespace std;

// Constructor de la clase Usuario
Usuario::Usuario(int id, string nombre, string contrasena, Rol rol)
    : id(id), nombre(nombre), contrasena(contrasena), rol(rol) {}

// Metodos getters
int Usuario::getId() const { return id; }
string Usuario::getNombre() const { return nombre; }
string Usuario::getContrasena() const { return contrasena; }
Usuario::Rol Usuario::getRol() const { return rol; }

// Metodos setters
void Usuario::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
void Usuario::setContrasena(const string& nuevaContrasena) { contrasena = nuevaContrasena; }
void Usuario::setRol(Rol nuevoRol) { rol = nuevoRol; }