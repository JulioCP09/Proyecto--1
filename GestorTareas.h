#ifndef GESTORTAREAS_H
#define GESTORTAREAS_H

#include "ColaEstandar.h"
#include "ColaPrioridad.h"
#include "Pila.h"
#include <string>
#include <unordered_set>
#include <vector>

const int MAX_CICLOS_ESPERA = 5;

class GestorTareas {
public:
    GestorTareas();

    void agregarTarea(const Tarea& tarea, bool urgente);
    bool agregarTarea(const Tarea& tarea, bool urgente, int responsableId);
    bool existeTarea(int id) const;
    const Tarea* buscarTarea(int id) const;
    bool actualizarTarea(int id, const std::string& titulo, int prioridad, int responsableId, const std::string& idUsuario);
    bool eliminarTarea(int id, const std::string& idUsuario);
    std::vector<Tarea> listarPendientes() const;
    bool cambiarEstadoComo(int idTarea, Tarea::Estado estado, int idUsuario, bool esAdministrador);
    bool cargar(const std::string& archivo);
    bool guardar(const std::string& archivo) const;
    Tarea atenderSiguiente(const std::string& idUsuario);
    bool cambiarEstado(int idTarea, Tarea::Estado nuevoEstado, const std::string& idUsuario);
    bool deshacer(const std::string& idUsuario);
    bool rehacer(const std::string& idUsuario);
    void mostrarColas() const;

private:
    struct CambioEstado {
        int idTarea;
        Tarea::Estado anterior;
        Tarea::Estado nuevo;
        std::string descripcion;
    };

    ColaEstandar colaEstandar;
    ColaPrioridad colaPrioridad;
    Pila historialDeshacer;
    Pila historialRehacer;
    std::vector<CambioEstado> cambiosDeshacer;
    std::vector<CambioEstado> cambiosRehacer;
    std::unordered_set<int> idsTareas;
    std::vector<Tarea> tareas;
    std::unordered_set<int> tareasUrgentes;

    bool aplicarEstado(int idTarea, Tarea::Estado estado);
    static std::string nombreEstado(Tarea::Estado estado);
    void reconstruirColas();
};

#endif