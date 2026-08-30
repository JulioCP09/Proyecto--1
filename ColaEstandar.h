#ifndef COLAESTANDAR_H
#define COLAESTANDAR_H

#include "Tarea.h"

struct NodoCola {
    Tarea dato;
    NodoCola* siguiente;
    NodoCola(const Tarea& tarea);
};

class ColaEstandar {
private:
    NodoCola* frente;
    NodoCola* final;
    int tamano;

public:
    ColaEstandar();
    ~ColaEstandar();
    ColaEstandar(const ColaEstandar&) = delete;
    ColaEstandar& operator=(const ColaEstandar&) = delete;
    
    void encolar(const Tarea& tarea);
    Tarea desencolar();
    Tarea verFrente() const;
    bool estaVacia() const;
    int getTamano() const;
    void mostrar() const;
    void incrementarCiclosEspera(int maxCiclos);
    void escalarTareas(int maxCiclos, class ColaPrioridad& colaPrioridad);
    bool cambiarEstado(int id, Tarea::Estado estado);
    const Tarea* buscar(int id) const;
    void limpiar();
};

#endif // COLAESTANDAR_H
