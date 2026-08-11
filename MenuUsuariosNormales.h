#ifndef MENUUSUARIOSNORMALES_H
#define MENUUSUARIOSNORMALES_H

#include "ListaUsuarios.h"

// Clase para manejar el menú de usuarios normales
class MenuUsuariosNormales {
public:
    // Metodo estatico para mostrar el menu de usuarios normales
    static void mostrarMenu(ListaUsuarios& lista, Usuario* usuarioActual);
};

#endif // MENUUSUARIOSNORMALES_H