#include "Tarea.h"

#include <stdexcept>

Tarea::Tarea()
    : id(0), titulo(), prioridad(0), responsableId(0), ciclosEspera(0), estado(PENDIENTE) {}

Tarea::Tarea(int id, const std::string& titulo, int prioridad, int responsableId)
    : id(id), titulo(titulo), prioridad(prioridad), responsableId(responsableId), ciclosEspera(0), estado(PENDIENTE) {
    if (id <= 0) throw std::invalid_argument("El ID de tarea debe ser positivo.");
    if (titulo.empty()) throw std::invalid_argument("El titulo de tarea no puede estar vacio.");
    if (prioridad < 0) throw std::invalid_argument("La prioridad no puede ser negativa.");
}

int Tarea::getId() const {
    return id;
}

const std::string& Tarea::getTitulo() const {
    return titulo;
}

int Tarea::getPrioridad() const {
    return prioridad;
}

int Tarea::getResponsableId() const {
    return responsableId;
}

int Tarea::getCiclosEspera() const {
    return ciclosEspera;
}

Tarea::Estado Tarea::getEstado() const {
    return estado;
}

const std::vector<Tarea>& Tarea::getSubtareas() const {
    return subtareas;
}

std::vector<Tarea>& Tarea::getSubtareas() {
    return subtareas;
}

void Tarea::setTitulo(const std::string& nuevoTitulo) {
    if (nuevoTitulo.empty()) throw std::invalid_argument("El titulo de tarea no puede estar vacio.");
    titulo = nuevoTitulo;
}

void Tarea::setPrioridad(int nuevaPrioridad) {
    if (nuevaPrioridad < 0) throw std::invalid_argument("La prioridad no puede ser negativa.");
    prioridad = nuevaPrioridad;
}

void Tarea::setResponsableId(int nuevoResponsableId) {
    if (nuevoResponsableId < 0) throw std::invalid_argument("El responsable no puede ser negativo.");
    responsableId = nuevoResponsableId;
}

void Tarea::setEstado(Estado nuevoEstado) {
    estado = nuevoEstado;
}

void Tarea::incrementarCiclosEspera() {
    ++ciclosEspera;
}

void Tarea::setCiclosEspera(int ciclos) {
    ciclosEspera = ciclos < 0 ? 0 : ciclos;
}

void Tarea::agregarSubtarea(const Tarea& subtarea) {
    subtareas.push_back(subtarea);
}