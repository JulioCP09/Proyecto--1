#include "GestorTareas.h"

#include "Auditoria.h"
#include "GestorArchivos.h"
#include <iostream>

GestorTareas::GestorTareas() {
    inicializarAuditoria();
}

void GestorTareas::agregarTarea(const Tarea& tarea, bool urgente) {
    agregarTarea(tarea, urgente, tarea.getResponsableId());
}

bool GestorTareas::agregarTarea(const Tarea& tarea, bool urgente, int responsableId) {
    if (tarea.getId() <= 0 || responsableId <= 0 || existeTarea(tarea.getId())) return false;
    Tarea copia = tarea;
    copia.setResponsableId(responsableId);
    tareas.push_back(copia);
    idsTareas.insert(copia.getId());
    if (urgente) tareasUrgentes.insert(copia.getId());
    reconstruirColas();
    guardar("tareas.csv");
    return true;
}

bool GestorTareas::existeTarea(int id) const {
    return idsTareas.find(id) != idsTareas.end();
}

Tarea GestorTareas::atenderSiguiente(const std::string& idUsuario) {
    Tarea atendida;
    if (!colaPrioridad.estaVacia()) atendida = colaPrioridad.extraerMaximo();
    else if (!colaEstandar.estaVacia()) atendida = colaEstandar.desencolar();
    else return atendida;

    if (atendida.getEstado() != Tarea::COMPLETADA) {
        const std::string estadoAnterior = nombreEstado(atendida.getEstado());
        aplicarEstado(atendida.getId(), Tarea::COMPLETADA);
        registrarAuditoria(idUsuario, "Cambio estado: " + estadoAnterior + " -> Completada", atendida.getId());
    }
    for (Tarea& tarea : tareas) {
        if (tarea.getEstado() == Tarea::COMPLETADA || tareasUrgentes.count(tarea.getId())) continue;
        tarea.incrementarCiclosEspera();
        if (tarea.getCiclosEspera() >= MAX_CICLOS_ESPERA) {
            tarea.setPrioridad(tarea.getPrioridad() + 1);
            tareasUrgentes.insert(tarea.getId());
            registrarAuditoria("SISTEMA", "Escalamiento automatico por SLA", tarea.getId());
        }
    }
    reconstruirColas();
    guardar("tareas.csv");
    return atendida;
}

bool GestorTareas::aplicarEstado(int idTarea, Tarea::Estado estado) {
    for (Tarea& tarea : tareas) {
        if (tarea.getId() == idTarea) {
            tarea.setEstado(estado);
            reconstruirColas();
            return true;
        }
    }
    return false;
}

std::string GestorTareas::nombreEstado(Tarea::Estado estado) {
    if (estado == Tarea::PENDIENTE) return "Pendiente";
    if (estado == Tarea::EN_PROGRESO) return "En Proceso";
    return "Completada";
}

bool GestorTareas::cambiarEstado(int idTarea, Tarea::Estado nuevoEstado, const std::string& idUsuario) {
    const Tarea* tarea = colaEstandar.buscar(idTarea);
    if (!tarea) tarea = colaPrioridad.buscar(idTarea);
    if (!tarea) return false;
    Tarea::Estado anterior = tarea->getEstado();
    if (!aplicarEstado(idTarea, nuevoEstado)) return false;

    CambioEstado cambio{idTarea, anterior, nuevoEstado,
        "Cambio estado: " + nombreEstado(anterior) + " -> " + nombreEstado(nuevoEstado)};
    cambiosDeshacer.push_back(cambio);
    historialDeshacer.push(cambio.descripcion);
    cambiosRehacer.clear();
    historialRehacer.limpiar();
    registrarAuditoria(idUsuario, cambio.descripcion, idTarea);
    guardar("tareas.csv");
    return true;
}

bool GestorTareas::deshacer(const std::string& idUsuario) {
    if (cambiosDeshacer.empty()) return false;
    CambioEstado cambio = cambiosDeshacer.back();
    cambiosDeshacer.pop_back();
    historialDeshacer.pop();
    if (!aplicarEstado(cambio.idTarea, cambio.anterior)) return false;
    cambiosRehacer.push_back(cambio);
    historialRehacer.push(cambio.descripcion);
    registrarAuditoria(idUsuario, "Deshacer: " + cambio.descripcion, cambio.idTarea);
    guardar("tareas.csv");
    return true;
}

bool GestorTareas::rehacer(const std::string& idUsuario) {
    if (cambiosRehacer.empty()) return false;
    CambioEstado cambio = cambiosRehacer.back();
    cambiosRehacer.pop_back();
    historialRehacer.pop();
    if (!aplicarEstado(cambio.idTarea, cambio.nuevo)) return false;
    cambiosDeshacer.push_back(cambio);
    historialDeshacer.push(cambio.descripcion);
    registrarAuditoria(idUsuario, "Rehacer: " + cambio.descripcion, cambio.idTarea);
    guardar("tareas.csv");
    return true;
}

void GestorTareas::mostrarColas() const {
    std::cout << "\n--- Cola estandar ---\n";
    colaEstandar.mostrar();
    std::cout << "--- Cola de prioridad ---\n";
    colaPrioridad.mostrar();
}

const Tarea* GestorTareas::buscarTarea(int id) const {
    for (const Tarea& tarea : tareas) if (tarea.getId() == id) return &tarea;
    return nullptr;
}

void GestorTareas::reconstruirColas() {
    colaEstandar.limpiar();
    colaPrioridad.limpiar();
    for (const Tarea& tarea : tareas) {
        if (tarea.getEstado() == Tarea::COMPLETADA) continue;
        if (tareasUrgentes.count(tarea.getId())) colaPrioridad.insertar(tarea);
        else colaEstandar.encolar(tarea);
    }
}

bool GestorTareas::actualizarTarea(int id, const std::string& titulo, int prioridad, int responsableId, const std::string& idUsuario) {
    Tarea* tarea = nullptr;
    for (Tarea& elemento : tareas) if (elemento.getId() == id) { tarea = &elemento; break; }
    if (!tarea || titulo.empty() || prioridad < 0 || responsableId <= 0) return false;
    tarea->setTitulo(titulo);
    tarea->setPrioridad(prioridad);
    tarea->setResponsableId(responsableId);
    if (prioridad > 0) tareasUrgentes.insert(id); else tareasUrgentes.erase(id);
    reconstruirColas();
    registrarAuditoria(idUsuario, "Actualizacion de tarea", id);
    guardar("tareas.csv");
    return true;
}

bool GestorTareas::eliminarTarea(int id, const std::string& idUsuario) {
    for (auto iter = tareas.begin(); iter != tareas.end(); ++iter) {
        if (iter->getId() == id) {
            tareas.erase(iter);
            idsTareas.erase(id);
            tareasUrgentes.erase(id);
            reconstruirColas();
            registrarAuditoria(idUsuario, "Eliminacion de tarea", id);
            guardar("tareas.csv");
            return true;
        }
    }
    return false;
}

std::vector<Tarea> GestorTareas::listarPendientes() const {
    std::vector<Tarea> resultado;
    for (const Tarea& tarea : tareas) if (tarea.getEstado() == Tarea::PENDIENTE) resultado.push_back(tarea);
    return resultado;
}

bool GestorTareas::cambiarEstadoComo(int idTarea, Tarea::Estado estado, int idUsuario, bool esAdministrador) {
    const Tarea* tarea = buscarTarea(idTarea);
    if (!tarea) return false;
    if (!esAdministrador && tarea->getResponsableId() != idUsuario) {
        std::cout << "No tiene permisos para modificar esta tarea.\n";
        return false;
    }
    return cambiarEstado(idTarea, estado, std::to_string(idUsuario));
}

bool GestorTareas::cargar(const std::string& archivo) {
    tareas.clear(); idsTareas.clear(); tareasUrgentes.clear();
    if (!GestorArchivos::cargarTareas(archivo, tareas)) return false;
    for (const Tarea& tarea : tareas) {
        if (idsTareas.insert(tarea.getId()).second && tarea.getPrioridad() > 0) tareasUrgentes.insert(tarea.getId());
    }
    reconstruirColas();
    return true;
}

bool GestorTareas::guardar(const std::string& archivo) const {
    return GestorArchivos::guardarTareas(archivo, tareas);
}