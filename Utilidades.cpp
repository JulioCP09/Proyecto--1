#include "Utilidades.h"
#include "Excepciones.h"
#include <charconv>
#include <cctype>
#include <iostream>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

int obtenerEnteroValidado(const std::string& mensaje) {
    std::string entrada;
    while (true) {
        std::cout << mensaje;
        if (!std::getline(std::cin, entrada)) {
            throw ErrorEntrada("No se pudo leer el valor numerico.");
        }

        std::size_t inicio = 0;
        while (inicio < entrada.size() && std::isspace(static_cast<unsigned char>(entrada[inicio]))) ++inicio;
        std::size_t fin = entrada.size();
        while (fin > inicio && std::isspace(static_cast<unsigned char>(entrada[fin - 1]))) --fin;
        if (inicio == fin) {
            std::cout << "Error: debe ingresar un numero entero valido.\n";
            continue;
        }

        int valor = 0;
        const char* primero = entrada.data() + inicio;
        const char* ultimo = entrada.data() + fin;
        const auto resultado = std::from_chars(primero, ultimo, valor);
        if (resultado.ec == std::errc() && resultado.ptr == ultimo) return valor;

        std::cout << "Error: debe ingresar un numero entero valido.\n";
    }
}

std::string obtenerCadenaValidada(const std::string& mensaje) {
    std::string valor;
    do {
        std::cout << mensaje;
        std::getline(std::cin, valor);
        if (valor.empty()) {
            std::cout << "El campo no puede estar vacio. Intente de nuevo." << std::endl;
        }
    } while (valor.empty());
    return valor;
}

int obtenerOpcionMenu(int min, int max) {
    int opcion;
    do {
        opcion = obtenerEnteroValidado("Seleccione una opcion: ");
        if (opcion < min || opcion > max) {
            std::cout << "Opcion fuera de rango. Intente de nuevo." << std::endl;
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
