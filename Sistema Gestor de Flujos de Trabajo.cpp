#include "ListaUsuarios.h"
#include "GestorArchivos.h"
#include "Sesion.h"
#include "MenuUsuarios.h"
#include "MenuUsuariosNormales.h"
#include <iostream>
using namespace std;

int main() {
    // Cargar usuarios desde el archivo 
    ListaUsuarios lista;
    GestorArchivos::cargarUsuarios("usuarios.csv", lista);

    // Solicitar credenciales al usuario
    int id;
    string contrasena;
    cout << "Ingrese ID: ";
    cin >> id;
    cout << "Ingrese contraseña: ";
    cin >> contrasena;

    // Validar credenciales y manejar la sesión
    if (lista.validarCredenciales(id, contrasena)) {
        Usuario* u = lista.buscarUsuario(id);
        Sesion sesion;
        sesion.login(u);

        cout << "Bienvenido " << u->getNombre() << endl;
        if (sesion.esAdmin()) {
            MenuUsuarios::mostrarMenu(lista);
        } else {
            MenuUsuariosNormales::mostrarMenu(lista, u);
        }
    } else {
        cout << "Credenciales inválidas." << endl;
    }

    return 0;
}