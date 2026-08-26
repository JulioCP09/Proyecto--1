#ifndef SESION_H
#define SESION_H

#include "Usuario.h"
using namespace std;

// Clase que representa una sesion de usuario en el sistema
class Sesion {
private:
    // Puntero al usuario actualmente logueado
    Usuario* usuarioActual;
public:
    // Constructor de la clase Sesion
    Sesion() : usuarioActual(nullptr) {}

    // Metodo para iniciar sesion con un usuario
    void login(Usuario* u) { usuarioActual = u; }
    // Metodo para cerrar sesion
    Usuario* getUsuarioActual() { return usuarioActual; }
    bool esAdmin() { return usuarioActual && usuarioActual->getRol() == Usuario::ADMIN; }
};

#endif // SESION_H