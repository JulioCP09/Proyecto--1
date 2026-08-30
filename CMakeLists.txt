cmake_minimum_required(VERSION 3.16)

project(GestorFlujosTrabajo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(GestorFlujosTrabajo
    "Sistema Gestor de Flujos de Trabajo.cpp"
    ArbolGeneral.cpp
    Auditoria.cpp
    ColaEstandar.cpp
    ColaPrioridad.cpp
    GestorArchivos.cpp
    GestorTareas.cpp
    ListaUsuarios.cpp
    MenuUsuarios.cpp
    MenuUsuariosNormales.cpp
    Pila.cpp
    Tarea.cpp
    Usuario.cpp
    Utilidades.cpp
)

target_include_directories(GestorFlujosTrabajo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(GestorFlujosTrabajo PRIVATE /W4 /permissive-)
else()
    target_compile_options(GestorFlujosTrabajo PRIVATE -Wall -Wextra -pedantic)
endif()

configure_file(usuarios.csv usuarios.csv COPYONLY)
configure_file(tareas.csv tareas.csv COPYONLY)