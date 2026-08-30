@echo off
title Compilar y ejecutar Gestor de Flujos de Trabajo
cd /d "%~dp0"
chcp 65001 >nul

set "salida=GestorFlujosTrabajo.exe"
where g++ >nul 2>&1
if not errorlevel 1 goto compilar_gcc

where cl >nul 2>&1
if not errorlevel 1 goto compilar_msvc

echo No se encontro g++ ni cl en el PATH.
echo Abre "Developer PowerShell for VS" o instala Desktop development with C++.
pause
exit /b 1

:compilar_gcc
echo Compilando con g++...
g++ -std=c++17 -Wall -Wextra -pedantic "Sistema Gestor de Flujos de Trabajo.cpp" ArbolGeneral.cpp Auditoria.cpp ColaEstandar.cpp ColaPrioridad.cpp GestorArchivos.cpp GestorTareas.cpp ListaUsuarios.cpp MenuUsuarios.cpp MenuUsuariosNormales.cpp Pila.cpp Tarea.cpp Usuario.cpp Utilidades.cpp -o "%salida%"
if errorlevel 1 goto error_compilacion
goto ejecutar

:compilar_msvc
echo Compilando con MSVC...
cl /std:c++17 /EHsc /W4 "Sistema Gestor de Flujos de Trabajo.cpp" ArbolGeneral.cpp Auditoria.cpp ColaEstandar.cpp ColaPrioridad.cpp GestorArchivos.cpp GestorTareas.cpp ListaUsuarios.cpp MenuUsuarios.cpp MenuUsuariosNormales.cpp Pila.cpp Tarea.cpp Usuario.cpp Utilidades.cpp /Fe:"%salida%"
if errorlevel 1 goto error_compilacion
goto ejecutar

:error_compilacion
echo La compilacion fallo. Revisa los mensajes anteriores.
pause
exit /b 1

:ejecutar
echo Compilacion correcta. Iniciando programa...
"%salida%"
set "codigo=%errorlevel%"
echo.
echo Codigo de salida: %codigo%
pause