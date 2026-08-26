#include "ColaEstandar.h"

#include "Auditoria.h"
#include "ColaPrioridad.h"
#include <iostream>
#include <stdexcept>

NodoCola::NodoCola(const Tarea& tarea) : dato(tarea), siguiente(nullptr) {}

ColaEstandar::ColaEstandar() : frente(nullptr), final(nullptr), tamano(0) {}

ColaEstandar::~ColaEstandar() {
    while (!estaVacia()) {
        desencolar();
    }
}

void ColaEstandar::encolar(const Tarea& tarea) {
    NodoCola* nuevo = new NodoCola(tarea);
    if (!final) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
    ++tamano;
}

Tarea ColaEstandar::desencolar() {
    if (estaVacia()) throw std::out_of_range("No se puede desencolar una cola vacia.");
    NodoCola* nodo = frente;
    Tarea tarea = nodo->dato;
    frente = frente->siguiente;
    if (!frente) final = nullptr;
    delete nodo;
    --tamano;
    return tarea;
}

Tarea ColaEstandar::verFrente() const {
    if (!frente) throw std::out_of_range("No hay tareas en la cola estandar.");
    return frente->dato;
}

bool ColaEstandar::estaVacia() const { return frente == nullptr; }
int ColaEstandar::getTamano() const { return tamano; }

void ColaEstandar::limpiar() {
    while (!estaVacia()) desencolar();
}

void ColaEstandar::mostrar() const {
    for (NodoCola* actual = frente; actual; actual = actual->siguiente) {
        std::cout << "ID: " << actual->dato.getId() << " - "
                  << actual->dato.getTitulo() << " (espera: "
                  << actual->dato.getCiclosEspera() << ")\n";
    }
}

void ColaEstandar::incrementarCiclosEspera(int maxCiclos) {
    for (NodoCola* actual = frente; actual; actual = actual->siguiente) {
        if (actual->dato.getCiclosEspera() < maxCiclos) {
            actual->dato.incrementarCiclosEspera();
        }
    }
}

void ColaEstandar::escalarTareas(int maxCiclos, ColaPrioridad& colaPrioridad) {
    NodoCola* anterior = nullptr;
    NodoCola* actual = frente;
    while (actual) {
        NodoCola* siguiente = actual->siguiente;
        if (actual->dato.getCiclosEspera() >= maxCiclos) {
            Tarea tarea = actual->dato;
            tarea.setPrioridad(tarea.getPrioridad() + 1);
            colaPrioridad.insertar(tarea);
            registrarAuditoria("SISTEMA", "Escalamiento automatico por SLA", tarea.getId());

            if (anterior) anterior->siguiente = siguiente;
            else frente = siguiente;
            if (actual == final) final = anterior;
            delete actual;
            --tamano;
        } else {
            anterior = actual;
        }
        actual = siguiente;
    }
}

bool ColaEstandar::cambiarEstado(int id, Tarea::Estado estado) {
    for (NodoCola* actual = frente; actual; actual = actual->siguiente) {
        if (actual->dato.getId() == id) {
            actual->dato.setEstado(estado);
            return true;
        }
    }
    return false;
}

const Tarea* ColaEstandar::buscar(int id) const {
    for (NodoCola* actual = frente; actual; actual = actual->siguiente) {
        if (actual->dato.getId() == id) return &actual->dato;
    }
    return nullptr;
}