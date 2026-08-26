#include "MenuUsuarios.h"
#include "GestorArchivos.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

// Implementacion del metodo mostrarMenu
void MenuUsuarios::mostrarMenu(ListaUsuarios& lista, bool esAdministrador) {
    if (!esAdministrador) {
        cout << "Acceso denegado: solo un administrador puede gestionar usuarios.\n";
        return;
    }
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
        opcion = obtenerOpcionMenu(0, 5);

        switch (opcion) {
        case 1: { // Agregar usuario
            int id;
            string nombre, contrasena, rolStr;
            id = obtenerEnteroValidado("ID: ");
            while (id <= 0 || lista.existeUsuario(id)) {
                if (id > 0) cout << "Error: ya existe un usuario con ese ID.\n";
                else cout << "Error: el ID debe ser positivo.\n";
                id = obtenerEnteroValidado("ID: ");
            }
            nombre = obtenerCadenaValidada("Nombre: ");
            do {
                cout << "Contrasena: ";
                contrasena = obtenerContrasenaOculta();
                if (contrasena.empty()) cout << "Error: la contrasena no puede estar vacia.\n";
            } while (contrasena.empty());
            do {
                rolStr = obtenerCadenaValidada("Rol (admin/normal): ");
                if (rolStr != "admin" && rolStr != "normal") cout << "Error: el rol debe ser admin o normal.\n";
            } while (rolStr != "admin" && rolStr != "normal");

            Usuario::Rol rol = (rolStr == "admin") ? Usuario::ADMIN : Usuario::NORMAL;
            Usuario nuevo(id, nombre, contrasena, rol);
            lista.agregarUsuario(nuevo);

            GestorArchivos::guardarUsuarios("usuarios.csv", lista);

            cout << "Usuario agregado.\n";
            break;
        }
        case 2: { // Actualizar usuario
            int id;
            id = obtenerEnteroValidado("Ingrese ID del usuario a actualizar: ");
            Usuario* u = lista.buscarUsuario(id);
            if (u) {
                string nuevoNombre, nuevaContrasena, rolStr;
                nuevoNombre = obtenerCadenaValidada("Nuevo nombre: ");
                do {
                    cout << "Nueva contrasena: ";
                    nuevaContrasena = obtenerContrasenaOculta();
                    if (nuevaContrasena.empty()) cout << "Error: la contrasena no puede estar vacia.\n";
                } while (nuevaContrasena.empty());
                do {
                    rolStr = obtenerCadenaValidada("Nuevo rol (admin/normal): ");
                    if (rolStr != "admin" && rolStr != "normal") cout << "Error: el rol debe ser admin o normal.\n";
                } while (rolStr != "admin" && rolStr != "normal");
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
            id = obtenerEnteroValidado("Ingrese ID del usuario a eliminar: ");
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
            id = obtenerEnteroValidado("Ingrese ID a buscar: ");
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