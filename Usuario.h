#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

// Clase que representa a un usuario en el sistema
class Usuario {
public:
    // Enum para representar los roles de usuario
    enum Rol { ADMIN, NORMAL };

private:
    // Atributos del usuario
    int id;
    string nombre;
    string contrasena;
    Rol rol;

public:
    // Constructor
    Usuario(int id, string nombre, string contrasena, Rol rol);

    // Metodos getters
    int getId() const;
    string getNombre() const;
    string getContrasena() const;
    Rol getRol() const;

    // Metodos setters
    void setNombre(const string& nuevoNombre);
    void setContrasena(const string& nuevaContrasena);
    void setRol(Rol nuevoRol);
};

#endif // USUARIO_H