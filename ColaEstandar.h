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
    
    void encolar(const Tarea& tarea);
    Tarea desencolar();
    Tarea verFrente() const;
    bool estaVacia() const;
    int getTamano() const;
    void mostrar() const;
    void incrementarCiclosEspera(int maxCiclos);
    void escalarTareas(int maxCiclos, class ColaPrioridad& colaPrioridad);
};

#endif // COLAESTANDAR_H
