#include "ArbolGeneral.h"

#include <iostream>

ArbolGeneral::ArbolGeneral() = default;
ArbolGeneral::ArbolGeneral(const Tarea& raiz) : raiz(raiz) {}

void ArbolGeneral::setRaiz(const Tarea& nuevaRaiz) { raiz = nuevaRaiz; }
Tarea ArbolGeneral::getRaiz() const { return raiz; }

void ArbolGeneral::mostrarAyuda(const Tarea& nodo, int nivel) const {
    std::cout << std::string(nivel * 2, ' ') << "ID: " << nodo.getId()
              << " - " << nodo.getTitulo() << "\n";
    for (const Tarea& subtarea : nodo.getSubtareas()) mostrarAyuda(subtarea, nivel + 1);
}

Tarea* ArbolGeneral::buscarAyuda(int id, Tarea& nodo) {
    if (nodo.getId() == id) return &nodo;
    for (Tarea& subtarea : nodo.getSubtareas()) {
        Tarea* encontrada = buscarAyuda(id, subtarea);
        if (encontrada) return encontrada;
    }
    return nullptr;
}

void ArbolGeneral::agregarSubtarea(int idPadre, const Tarea& subtarea) {
    Tarea* padre = buscarTarea(idPadre);
    if (padre) padre->agregarSubtarea(subtarea);
}

void ArbolGeneral::mostrar() const {
    if (!estaVacio()) mostrarAyuda(raiz, 0);
}

Tarea* ArbolGeneral::buscarTarea(int id) { return estaVacio() ? nullptr : buscarAyuda(id, raiz); }
bool ArbolGeneral::estaVacio() const { return raiz.getId() == 0; }