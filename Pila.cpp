#include "Pila.h"

Pila::Pila() = default;

void Pila::push(const std::string& accion) { items.push(accion); }

std::string Pila::pop() {
    return items.pop();
}

std::string Pila::peek() const { return items.peek(); }
bool Pila::estaVacia() const { return items.estaVacia(); }
int Pila::getTamano() const { return items.getTamano(); }
void Pila::limpiar() { items.limpiar(); }