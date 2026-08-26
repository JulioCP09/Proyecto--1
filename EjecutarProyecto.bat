@echo off
title Gestor de Flujos de Trabajo
cd /d "%~dp0"
chcp 65001 >nul

set "ejecutable=GestorFlujosTrabajo.exe"

if not exist "%ejecutable%" (
    echo No se encontro el ejecutable actualizado: %ejecutable%
    echo Ejecuta CompilarYEjecutar.bat desde una Developer PowerShell for VS.
    echo No se ejecutara programa.exe porque puede ser una version antigua.
    pause
    exit /b 1
)

echo Iniciando programa...
"%~dp0%ejecutable%"
set "codigo=%errorlevel%"
echo.
if not "%codigo%"=="0" echo El programa termino con el codigo: %codigo%
echo Presiona una tecla para cerrar esta ventana.
pause