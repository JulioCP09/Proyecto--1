#include "ColaPrioridad.h"

#include <iostream>
#include <stdexcept>

ColaPrioridad::ColaPrioridad() = default;

int ColaPrioridad::padre(int indice) const { return (indice - 1) / 2; }
int ColaPrioridad::hijoIzquierdo(int indice) const { return indice * 2 + 1; }
int ColaPrioridad::hijoDerecho(int indice) const { return indice * 2 + 2; }

void ColaPrioridad::flotar(int indice) {
    while (indice > 0 && heap[padre(indice)].getPrioridad() < heap[indice].getPrioridad()) {
        std::swap(heap[padre(indice)], heap[indice]);
        indice = padre(indice);
    }
}

void ColaPrioridad::hundir(int indice) {
    int mayor = indice;
    int izquierdo = hijoIzquierdo(indice);
    int derecho = hijoDerecho(indice);
    if (izquierdo < static_cast<int>(heap.size()) && heap[izquierdo].getPrioridad() > heap[mayor].getPrioridad()) mayor = izquierdo;
    if (derecho < static_cast<int>(heap.size()) && heap[derecho].getPrioridad() > heap[mayor].getPrioridad()) mayor = derecho;
    if (mayor != indice) {
        std::swap(heap[indice], heap[mayor]);
        hundir(mayor);
    }
}

void ColaPrioridad::insertar(const Tarea& tarea) {
    heap.push_back(tarea);
    flotar(static_cast<int>(heap.size()) - 1);
}

Tarea ColaPrioridad::extraerMaximo() {
    if (estaVacia()) return Tarea();
    Tarea resultado = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    if (!heap.empty()) hundir(0);
    return resultado;
}

Tarea ColaPrioridad::obtenerMaximo() const { return estaVacia() ? Tarea() : heap.front(); }
bool ColaPrioridad::estaVacia() const { return heap.empty(); }
int ColaPrioridad::getTamano() const { return static_cast<int>(heap.size()); }

void ColaPrioridad::mostrar() const {
    for (const Tarea& tarea : heap) {
        std::cout << "ID: " << tarea.getId() << " - " << tarea.getTitulo()
                  << " (prioridad: " << tarea.getPrioridad() << ")\n";
    }
}

void ColaPrioridad::limpiar() { heap.clear(); }

bool ColaPrioridad::cambiarEstado(int id, Tarea::Estado estado) {
    for (Tarea& tarea : heap) {
        if (tarea.getId() == id) {
            tarea.setEstado(estado);
            return true;
        }
    }
    return false;
}

const Tarea* ColaPrioridad::buscar(int id) const {
    for (const Tarea& tarea : heap) {
        if (tarea.getId() == id) return &tarea;
    }
    return nullptr;
}