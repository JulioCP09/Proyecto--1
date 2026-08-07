#include "MenuUsuariosNormales.h"
#include <iostream>
using namespace std;

void MenuUsuariosNormales::mostrarMenu(ListaUsuarios& lista, Usuario* usuarioActual) {
    int opcion;
    do {
        cout << "\n--- MENU USUARIO NORMAL ---\n";
        cout << "Bienvenido, " << usuarioActual->getNombre() << endl;
        cout << "1. Ver mis datos\n";
        cout << "2. Cambiar mi contraseña\n";
        cout << "3. Ver tablero Kanban (pendiente)\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "ID: " << usuarioActual->getId()
                 << " Nombre: " << usuarioActual->getNombre()
                 << " Rol: " << (usuarioActual->getRol() == Usuario::ADMIN ? "admin" : "normal")
                 << endl;
            break;
        case 2: {
            string nuevaContrasena;
            cout << "Ingrese nueva contrasena: ";
            cin >> nuevaContrasena;
            usuarioActual->setContrasena(nuevaContrasena);
            cout << "Contrasena actualizada.\n";
            break;
        }
        case 3:
            cout << "(Pendiente: implementar tablero Kanban)\n";
            break;
        case 0:
            cout << "Saliendo del menu usuario normal...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}