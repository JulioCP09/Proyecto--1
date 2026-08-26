#include "Tarea.h"

Tarea::Tarea()
    : id(0), titulo(), prioridad(0), responsableId(0), ciclosEspera(0), estado(PENDIENTE) {}

Tarea::Tarea(int id, const std::string& titulo, int prioridad, int responsableId)
    : id(id), titulo(titulo), prioridad(prioridad), responsableId(responsableId), ciclosEspera(0), estado(PENDIENTE) {}

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
    titulo = nuevoTitulo;
}

void Tarea::setPrioridad(int nuevaPrioridad) {
    prioridad = nuevaPrioridad;
}

void Tarea::setResponsableId(int nuevoResponsableId) {
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