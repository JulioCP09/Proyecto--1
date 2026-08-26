#ifndef MENUUSUARIOS_H
#define MENUUSUARIOS_H

#include "ListaUsuarios.h"

// Clase para manejar el menú de usuarios
class MenuUsuarios {
public:
    // Metodo estático para mostrar el menu de usuarios
    static void mostrarMenu(ListaUsuarios& lista, bool esAdministrador);
};

#endif // MENUUSUARIOS_H