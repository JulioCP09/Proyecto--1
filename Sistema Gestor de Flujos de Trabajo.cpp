#include <iostream>
#include "ListaUsuarios.h"
#include "GestorArchivos.h"
#include "Sesion.h"

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
            cout << "Menu: [1] Usuarios [2] Tareas [3] Kanban" << endl;
        } else {
            cout << "Menu: [1] Mis Tareas [2] Kanban" << endl;
        }
    } else {
        cout << "Credenciales inválidas." << endl;
    }

    return 0;
}