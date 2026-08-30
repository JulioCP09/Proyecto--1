# Gestor de Flujos de Trabajo

Proyecto de consola en C++17 para administrar usuarios y organizar tareas mediante estructuras de datos.

## Componentes

* `Usuario` y `ListaUsuarios`: modelo y lista doblemente enlazada de usuarios.
* `Sesion`: usuario autenticado y control de rol.
* `MenuUsuarios` y `MenuUsuariosNormales`: interacción de cada tipo de usuario.
* `GestorArchivos`: persistencia de usuarios en `usuarios.csv`.
* `Tarea`: modelo común para el árbol y las colas de tareas.
* `ArbolGeneral`, `ColaEstandar`, `ColaPrioridad` y `Pila`: estructuras para el flujo de trabajo.
* `GestorTareas`: coordina las colas, el SLA de cinco ciclos y Deshacer/Rehacer.
* `Auditoria`: registra acciones en `auditoria\_log.csv` usando modo append.
* `Excepciones`: errores de entrada, dominio, archivos y operaciones inválidas se manejan de forma controlada.

## Templates y rendimiento

`PilaGenerica<T>` en `Pila.h` reutiliza la lógica de una pila para cualquier tipo. Las búsquedas de IDs del gestor usan `unordered\_set`, con coste promedio O(1). Las operaciones FIFO de la cola estándar son O(1), mientras que insertar y extraer del heap de prioridad son O(log n).

* `Sistema Gestor de Flujos de Trabajo.cpp`: punto de entrada y menú principal.

## Compilación

Requiere CMake 3.16 o superior y un compilador compatible con C++17:

```text
cmake -S . -B build
cmake --build build
```

El archivo `usuarios.csv` se copia automáticamente al directorio de ejecución.

# Sistema Gestor de Flujos de Trabajo

## Bitácora de Uso de Inteligencia Artificial

|Área del proyecto|Prompt utilizado|Revisión y ajustes realizados|
|-|-|-|
|Lectura de archivos CSV|"Ayúdame a revisar por qué mi programa no encuentra el archivo usuarios.csv y cómo solucionarlo."|Se verificó el manejo de rutas y se agregaron los archivos CSV requeridos en la carpeta del ejecutable.|
|Manejo de excepciones|"Explícame cómo manejar excepciones al abrir archivos en C++ utilizando clases personalizadas."|Se adaptó el ejemplo al diseño del proyecto y se mantuvieron las clases de excepción propias.|
|Organización del proyecto|"¿Cómo puedo organizar un proyecto de C++ utilizando varias clases y archivos .h y .cpp?"|Se reorganizó la estructura según las necesidades del proyecto y se modificaron nombres y métodos.|
|Depuración|"Revisa este error y explícame qué significa."|Se analizaron los mensajes del compilador y se realizaron las correcciones manualmente.|
|Documentación|"Ayúdame a redactar el README del proyecto y la bitácora de uso de IA."|El contenido fue revisado y adaptado para reflejar el trabajo realizado durante el desarrollo.|

## Observaciones

La IA se utilizó como herramienta de apoyo para comprender errores, revisar partes del código, proponer mejoras y redactar documentación.

Todo el código sugerido fue revisado antes de incorporarlo al proyecto, realizando modificaciones para adaptarlo al proyecto en cuestión.

