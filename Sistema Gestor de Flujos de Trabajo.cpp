#include "ListaUsuarios.h"
#include "GestorArchivos.h"
#include "Sesion.h"
#include "MenuUsuarios.h"
#include "MenuUsuariosNormales.h"
#include "GestorTareas.h"
#include "Utilidades.h"
#include "Excepciones.h"
#include <iostream>
using namespace std;

void menuTareas(GestorTareas& gestor, const string& idUsuario, ListaUsuarios& lista, bool esAdministrador) {
    try {
    if (!esAdministrador) {
        int opcion;
        do {
            cout << "\n--- TAREAS DISPONIBLES ---\n"
                 << "1. Listar tareas pendientes\n"
                 << "2. Buscar tarea\n"
                 << "3. Cambiar estado de mi tarea\n"
                 << "0. Volver\n";
            opcion = obtenerOpcionMenu(0, 3);
            if (opcion == 1) {
                for (const Tarea& tarea : gestor.listarPendientes()) {
                    cout << "ID: " << tarea.getId() << " - " << tarea.getTitulo()
                         << " - Responsable: " << tarea.getResponsableId() << "\n";
                }
            } else if (opcion == 2) {
                int id = obtenerEnteroValidado("ID de tarea: ");
                const Tarea* tarea = gestor.buscarTarea(id);
                if (!tarea) cout << "Tarea no encontrada.\n";
                else cout << "ID: " << tarea->getId() << " - " << tarea->getTitulo()
                          << " - Responsable: " << tarea->getResponsableId() << "\n";
            } else if (opcion == 3) {
                int id = obtenerEnteroValidado("ID de tarea: ");
                int estado = obtenerOpcionMenu(0, 2);
                if (!gestor.cambiarEstadoComo(id, static_cast<Tarea::Estado>(estado), std::stoi(idUsuario), false))
                    cout << "No se pudo cambiar el estado.\n";
                else cout << "Estado actualizado.\n";
            }
        } while (opcion != 0);
        return;
    }

    int opcion;
    do {
        cout << "\n--- MENU DE TAREAS ---\n"
             << "1. Agregar tarea regular\n"
             << "2. Agregar tarea urgente\n"
             << "3. Atender siguiente tarea\n"
             << "4. Cambiar estado\n"
             << "5. Deshacer\n"
             << "6. Rehacer\n"
             << "7. Mostrar colas\n"
             << "8. Buscar tarea\n"
             << "9. Listar pendientes\n"
             << "10. Actualizar tarea\n"
             << "11. Eliminar tarea\n"
             << "0. Salir\nSeleccione una opcion: ";
        opcion = obtenerOpcionMenu(0, 11);

        if (opcion == 1 || opcion == 2) {
            int id, prioridad = 0;
            int responsable;
            string titulo;
            id = obtenerEnteroValidado("ID: ");
            while (id <= 0) {
                cout << "Error: el ID debe ser positivo.\n";
                id = obtenerEnteroValidado("ID: ");
            }
            while (gestor.existeTarea(id)) {
                cout << "Error: ya existe una tarea con ese ID.\n";
                id = obtenerEnteroValidado("ID: ");
            }
            titulo = obtenerCadenaValidada("Titulo: ");
            if (opcion == 2) {
                prioridad = obtenerEnteroValidado("Prioridad: ");
                while (prioridad < 0) {
                    cout << "Error: la prioridad no puede ser negativa.\n";
                    prioridad = obtenerEnteroValidado("Prioridad: ");
                }
            }
            do {
                responsable = obtenerEnteroValidado("ID del responsable: ");
                if (!lista.existeUsuario(responsable)) cout << "Error: el usuario responsable no existe.\n";
            } while (!lista.existeUsuario(responsable));
            if (gestor.agregarTarea(Tarea(id, titulo, prioridad, responsable), opcion == 2, responsable)) {
                cout << "Tarea agregada.\n";
            } else {
                cout << "No se pudo agregar la tarea.\n";
            }
        } else if (opcion == 3) {
            Tarea tarea = gestor.atenderSiguiente(idUsuario);
            if (tarea.getId() == 0) cout << "No hay tareas pendientes.\n";
            else cout << "Tarea atendida: " << tarea.getId() << "\n";
        } else if (opcion == 4) {
            int id, estado;
            id = obtenerEnteroValidado("ID de tarea: ");
            estado = obtenerOpcionMenu(0, 2);
            if (!gestor.cambiarEstadoComo(id, static_cast<Tarea::Estado>(estado), std::stoi(idUsuario), esAdministrador))
                cout << "No se pudo cambiar el estado.\n";
            else cout << "Estado actualizado.\n";
        } else if (opcion == 5) {
            cout << (gestor.deshacer(idUsuario) ? "Deshacer realizado.\n" : "No hay acciones para deshacer.\n");
        } else if (opcion == 6) {
            cout << (gestor.rehacer(idUsuario) ? "Rehacer realizado.\n" : "No hay acciones para rehacer.\n");
        } else if (opcion == 7) {
            gestor.mostrarColas();
        } else if (opcion == 8) {
            int id = obtenerEnteroValidado("ID de tarea: ");
            const Tarea* tarea = gestor.buscarTarea(id);
            if (!tarea) cout << "Tarea no encontrada.\n";
            else cout << "Tarea encontrada: ID " << tarea->getId() << " - " << tarea->getTitulo()
                      << " - Responsable: " << tarea->getResponsableId()
                      << " - Prioridad: " << tarea->getPrioridad() << "\n";
        } else if (opcion == 9) {
            for (const Tarea& tarea : gestor.listarPendientes()) {
                cout << "ID: " << tarea.getId() << " - " << tarea.getTitulo()
                     << " - Responsable: " << tarea.getResponsableId() << "\n";
            }
        } else if (opcion == 10 && esAdministrador) {
            int id = obtenerEnteroValidado("ID de tarea: ");
            string titulo = obtenerCadenaValidada("Nueva descripcion: ");
            int prioridad = obtenerEnteroValidado("Nueva prioridad: ");
            int responsable = obtenerEnteroValidado("Nuevo responsable: ");
            if (!lista.existeUsuario(responsable) || !gestor.actualizarTarea(id, titulo, prioridad, responsable, idUsuario))
                cout << "No se pudo actualizar la tarea.\n";
            else cout << "Tarea actualizada.\n";
        } else if (opcion == 11 && esAdministrador) {
            int id = obtenerEnteroValidado("ID de tarea: ");
            cout << (gestor.eliminarTarea(id, idUsuario) ? "Tarea eliminada.\n" : "Tarea no encontrada.\n");
        }
    } while (opcion != 0);
    } catch (const std::exception& error) {
        cout << "Error controlado en tareas: " << error.what() << "\n";
        cout << "Regresando al menu principal.\n";
    }
}

// Funcion para mostrar el menu principal dependiendo del rol del usuario
void menuPrincipal(Sesion& sesion, ListaUsuarios& lista) {
    GestorTareas gestor;
    try {
        gestor.cargar("tareas.csv");
    } catch (const std::exception& error) {
        cout << "No se pudieron cargar las tareas: " << error.what() << "\n";
    }
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
        opcion = sesion.esAdmin() ? obtenerOpcionMenu(0, 3) : obtenerOpcionMenu(0, 2);
        
        // Dependiendo del rol del usuario, mostrar el menu correspondiente
        if (sesion.esAdmin()) { // Menu para admin
            switch (opcion) {
            case 1:
                MenuUsuarios::mostrarMenu(lista, sesion.esAdmin());
                break;
            case 2:
                menuTareas(gestor, to_string(sesion.getUsuarioActual()->getId()), lista, true);
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
                menuTareas(gestor, to_string(sesion.getUsuarioActual()->getId()), lista, false);
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
    try {
    // Cargar usuarios desde el archivo 
    ListaUsuarios lista;
    GestorArchivos::cargarUsuarios("usuarios.csv", lista);

    for (int intento = 1; intento <= 3; ++intento) {
        int id = obtenerEnteroValidado("Ingrese ID: ");
        string contrasena;
        cout << "Ingrese contrasenna: ";
        contrasena = obtenerContrasenaOculta();

        if (lista.validarCredenciales(id, contrasena)) {
            Usuario* u = lista.buscarUsuario(id);
            Sesion sesion;
            sesion.login(u);
            cout << "Bienvenido " << u->getNombre() << endl;
            menuPrincipal(sesion, lista);
            return 0;
        }

        cout << "Credenciales incorrectas. Intento " << intento << " de 3.\n";
    }

    cout << "Demasiados intentos fallidos. Programa finalizado.\n";

    } catch (const std::exception& error) {
        cerr << "Error controlado: " << error.what() << "\n";
        return 1;
    }
    return 0;
}