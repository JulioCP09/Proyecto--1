#ifndef MENUUSUARIOS_H
#define MENUUSUARIOS_H

#include "ListaUsuarios.h"

// Clase para manejar el menu de usuarios
class MenuUsuarios {
public:
    // Metodo estatico para mostrar el menu de usuarios
    static void mostrarMenu(ListaUsuarios& lista, bool esAdministrador);
};

#endif // MENUUSUARIOS_H