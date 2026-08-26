# Gestor de Flujos de Trabajo

Proyecto de consola en C++17 para administrar usuarios y organizar tareas mediante estructuras de datos.

## Componentes

- `Usuario` y `ListaUsuarios`: modelo y lista doblemente enlazada de usuarios.
- `Sesion`: usuario autenticado y control de rol.
- `MenuUsuarios` y `MenuUsuariosNormales`: interacción de cada tipo de usuario.
- `GestorArchivos`: persistencia de usuarios en `usuarios.csv`.
- `Tarea`: modelo común para el árbol y las colas de tareas.
- `ArbolGeneral`, `ColaEstandar`, `ColaPrioridad` y `Pila`: estructuras para el flujo de trabajo.
- `GestorTareas`: coordina las colas, el SLA de cinco ciclos y Deshacer/Rehacer.
- `Auditoria`: registra acciones en `auditoria_log.csv` usando modo append.
- `Excepciones`: errores de entrada, dominio, archivos y operaciones inválidas se manejan de forma controlada.

## Templates y rendimiento

`PilaGenerica<T>` en `Pila.h` reutiliza la lógica de una pila para cualquier tipo. Las búsquedas de IDs del gestor usan `unordered_set`, con coste promedio O(1). Las operaciones FIFO de la cola estándar son O(1), mientras que insertar y extraer del heap de prioridad son O(log n).
- `Sistema Gestor de Flujos de Trabajo.cpp`: punto de entrada y menú principal.

## Compilación

Requiere CMake 3.16 o superior y un compilador compatible con C++17:

```text
cmake -S . -B build
cmake --build build
```

El archivo `usuarios.csv` se copia automáticamente al directorio de ejecución.