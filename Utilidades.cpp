#include "Utilidades.h"
#include <iostream>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

int obtenerEnteroValidado(const std::string& mensaje) {
    int valor;
    std::cout << mensaje;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Por favor, ingrese un número: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

std::string obtenerCadenaValidada(const std::string& mensaje) {
    std::string valor;
    do {
        std::cout << mensaje;
        std::getline(std::cin, valor);
        if (valor.empty()) {
            std::cout << "El campo no puede estar vacío. Intente de nuevo." << std::endl;
        }
    } while (valor.empty());
    return valor;
}

int obtenerOpcionMenu(int min, int max) {
    int opcion;
    do {
        opcion = obtenerEnteroValidado("Seleccione una opción: ");
        if (opcion < min || opcion > max) {
            std::cout << "Opción fuera de rango. Intente de nuevo." << std::endl;
        }
    } while (opcion < min || opcion > max);
    return opcion;
}

std::string obtenerContrasenaOculta() {
#ifdef _WIN32
    std::string contrasena;
    int ch;
    while ((ch = _getch()) != '\r' && ch != '\n') {
        if (ch == '\b' && !contrasena.empty()) {
            contrasena.pop_back();
            std::cout << "\b \b";
        }
        else if (ch == '\b') continue;
        else {
            contrasena.push_back(static_cast<char>(ch));
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return contrasena;
#else
    struct termios oldt, newt;
    std::string contrasena;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && ch != EOF) {
        contrasena.push_back(ch);
        // Opcional: mostrar asteriscos
        // std::cout << '*';
        // fflush(stdout);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return contrasena;
#endif
}

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
