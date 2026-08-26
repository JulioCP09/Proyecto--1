#include "Pila.h"

#include <stdexcept>

Pila::Pila() = default;

void Pila::push(const std::string& accion) { items.push_back(accion); }

std::string Pila::pop() {
    if (estaVacia()) return "";
    std::string accion = items.back();
    items.pop_back();
    return accion;
}

std::string Pila::peek() const { return estaVacia() ? "" : items.back(); }
bool Pila::estaVacia() const { return items.empty(); }
int Pila::getTamano() const { return static_cast<int>(items.size()); }
void Pila::limpiar() { items.clear(); }