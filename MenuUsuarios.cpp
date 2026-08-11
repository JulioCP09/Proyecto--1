#include "MenuUsuarios.h"
#include "GestorArchivos.h"
#include <iostream>
using namespace std;

// Implementación del metodo mostrarMenu
void MenuUsuarios::mostrarMenu(ListaUsuarios& lista) {
    int opcion;
    do {
        cout << "\n--- MENU ADMIN ---\n";
        cout << "1. Agregar usuario\n";
        cout << "2. Actualizar usuario\n";
        cout << "3. Eliminar usuario\n";
        cout << "4. Listar usuarios\n";
        cout << "5. Buscar usuario\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: { // Agregar usuario
            int id;
            string nombre, contrasena, rolStr;
            cout << "ID: "; cin >> id;
            cout << "Nombre: "; cin >> nombre;
            cout << "Contrasena: "; cin >> contrasena;
            cout << "Rol (admin/normal): "; cin >> rolStr;

            Usuario::Rol rol = (rolStr == "admin") ? Usuario::ADMIN : Usuario::NORMAL;
            Usuario nuevo(id, nombre, contrasena, rol);
            lista.agregarUsuario(nuevo);

            GestorArchivos::guardarUsuarios("usuarios.csv", lista);

            cout << "Usuario agregado.\n";
            break;
        }
        case 2: { // Actualizar usuario
            int id;
            cout << "Ingrese ID del usuario a actualizar: ";
            cin >> id;
            Usuario* u = lista.buscarUsuario(id);
            if (u) {
                string nuevoNombre, nuevaContrasena, rolStr;
                cout << "Nuevo nombre: "; cin >> nuevoNombre;
                cout << "Nueva contrasena: "; cin >> nuevaContrasena;
                cout << "Nuevo rol (admin/normal): "; cin >> rolStr;
                u->setNombre(nuevoNombre);
                u->setContrasena(nuevaContrasena);
                u->setRol((rolStr == "admin") ? Usuario::ADMIN : Usuario::NORMAL);

                GestorArchivos::guardarUsuarios("usuarios.csv", lista);
                
                cout << "Usuario actualizado.\n";
            } else {
                cout << "Usuario no encontrado.\n";
            }
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del usuario a eliminar: ";
            cin >> id;
            if (lista.eliminarUsuario(id)) {
                GestorArchivos::guardarUsuarios("usuarios.csv", lista);

                cout << "Usuario eliminado.\n";
            } else {
                cout << "Usuario no encontrado.\n";
            }
            break;
        }
        case 4: // Listar usuarios
            lista.listarUsuarios();
            break;
        case 5: { // Buscar usuario
            int id;
            cout << "Ingrese ID a buscar: ";
            cin >> id;
            Usuario* u = lista.buscarUsuario(id);
            if (u) {
                cout << "ID: " << u->getId()
                     << " Nombre: " << u->getNombre()
                     << " Rol: " << (u->getRol() == Usuario::ADMIN ? "admin" : "normal") << endl;
            } else {
                cout << "Usuario no encontrado.\n";
            }
            break;
        }
        case 0: // Salir
            cout << "Saliendo del menu admin...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}