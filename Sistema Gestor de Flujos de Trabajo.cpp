#include "ListaUsuarios.h"
#include "GestorArchivos.h"
#include "Sesion.h"
#include "MenuUsuarios.h"
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
            cout << "Bienvenido usuario normal: " << u->getNombre() << endl;
            cout << "Menu: [1] Mis Tareas [2] Kanban" << endl;
            // Aquí va menú de usuario normal
        }
    } else {
        cout << "Credenciales inválidas." << endl;
    }

    return 0;
}