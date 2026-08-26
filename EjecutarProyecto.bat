@echo off
title Gestor de Flujos de Trabajo
cd /d "%~dp0"

if not exist "programa.exe" (
    echo No se encontro programa.exe en esta carpeta.
    echo Necesitas compilar el proyecto primero desde Visual Studio.
    pause
    exit /b 1
)

echo Iniciando programa...
"%~dp0programa.exe"
set "codigo=%errorlevel%"
echo.
if not "%codigo%"=="0" echo El programa termino con el codigo: %codigo%
echo Presiona una tecla para cerrar esta ventana.
pause