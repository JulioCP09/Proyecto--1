# Gestor de Flujos de Trabajo

Proyecto de consola en C++17 para administrar usuarios y organizar tareas mediante estructuras de datos.

## Componentes

- `Usuario` y `ListaUsuarios`: modelo y lista doblemente enlazada de usuarios.
- `Sesion`: usuario autenticado y control de rol.
- `MenuUsuarios` y `MenuUsuariosNormales`: interacción de cada tipo de usuario.
- `GestorArchivos`: persistencia de usuarios en `usuarios.csv`.
- `Tarea`: modelo común para el árbol y las colas de tareas.
- `ArbolGeneral`, `ColaEstandar`, `ColaPrioridad` y `Pila`: estructuras para el flujo de trabajo.
- `Sistema Gestor de Flujos de Trabajo.cpp`: punto de entrada y menú principal.

## Compilación

Requiere CMake 3.16 o superior y un compilador compatible con C++17:

```text
cmake -S . -B build
cmake --build build
```

El archivo `usuarios.csv` se copia automáticamente al directorio de ejecución.