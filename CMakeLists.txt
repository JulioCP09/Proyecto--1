cmake_minimum_required(VERSION 3.16)

project(GestorFlujosTrabajo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(GestorFlujosTrabajo
    "Sistema Gestor de Flujos de Trabajo.cpp"
    GestorArchivos.cpp
    ListaUsuarios.cpp
    MenuUsuarios.cpp
    MenuUsuariosNormales.cpp
    Tarea.cpp
    Usuario.cpp
    Utilidades.cpp
)

target_include_directories(GestorFlujosTrabajo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(usuarios.csv usuarios.csv COPYONLY)