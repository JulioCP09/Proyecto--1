#include "ListaUsuarios.h"
#include "GestorArchivos.h"
#include "Sesion.h"
#include "MenuUsuarios.h"
#include "MenuUsuariosNormales.h"
#include <iostream>
using namespace std;

// Funcion para mostrar el menu principal dependiendo del rol del usuario
void menuPrincipal(Sesion& sesion, ListaUsuarios& lista) {
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        if (sesion.esAdmin()) { // Mostrar opciones para admin
            cout << "1. Usuarios\n";
            cout << "2. Tareas\n";
            cout << "3. Kanban\n";
        } else { // Mostrar opciones para usuario normal
            cout << "1. Usuario\n";
            cout << "2. Kanban\n";
        }
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        // Dependiendo del rol del usuario, mostrar el menu correspondiente
        if (sesion.esAdmin()) { // Menu para admin
            switch (opcion) {
            case 1:
                MenuUsuarios::mostrarMenu(lista);
                break;
            case 2:
                cout << "(Pendiente: implementar menu de tareas)\n";
                break;
            case 3:
                cout << "(Pendiente: implementar tablero Kanban)\n";
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
            }
        } else { // Menu para usuario normal
            switch (opcion) {
            case 1:
                MenuUsuariosNormales::mostrarMenu(lista, sesion.getUsuarioActual());
                break;
            case 2:
                cout << "(Pendiente: implementar tablero Kanban)\n";
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
            }
        }
    } while (opcion != 0);
}

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
        menuPrincipal(sesion, lista);
    } else {
        cout << "Credenciales incorrectas.\n";
    }

    return 0;
}