#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <stdexcept>
#include <string>

class ErrorEntrada : public std::runtime_error {
public:
    explicit ErrorEntrada(const std::string& mensaje) : std::runtime_error(mensaje) {}
};

class ErrorArchivo : public std::runtime_error {
public:
    explicit ErrorArchivo(const std::string& mensaje) : std::runtime_error(mensaje) {}
};

#endif