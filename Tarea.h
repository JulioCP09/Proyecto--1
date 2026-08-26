#ifndef TAREA_H
#define TAREA_H

#include <string>
#include <vector>

class Tarea {
public:
    enum Estado { PENDIENTE, EN_PROGRESO, COMPLETADA };

    Tarea();
    Tarea(int id, const std::string& titulo, int prioridad = 0);

    int getId() const;
    const std::string& getTitulo() const;
    int getPrioridad() const;
    int getCiclosEspera() const;
    Estado getEstado() const;
    const std::vector<Tarea>& getSubtareas() const;
    std::vector<Tarea>& getSubtareas();

    void setTitulo(const std::string& nuevoTitulo);
    void setPrioridad(int nuevaPrioridad);
    void setEstado(Estado nuevoEstado);
    void incrementarCiclosEspera();
    void agregarSubtarea(const Tarea& subtarea);

private:
    int id;
    std::string titulo;
    int prioridad;
    int ciclosEspera;
    Estado estado;
    std::vector<Tarea> subtareas;
};

#endif