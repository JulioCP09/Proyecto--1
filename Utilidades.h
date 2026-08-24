#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

// Validación de entrada
int obtenerEnteroValidado(const std::string& mensaje);
std::string obtenerCadenaValidada(const std::string& mensaje);
int obtenerOpcionMenu(int min, int max);

// Ocultamiento de contraseña (para Linux/macOS)
std::string obtenerContrasenaOculta();

// Limpiar buffer de entrada
void limpiarBuffer();

#endif // UTILIDADES_H
