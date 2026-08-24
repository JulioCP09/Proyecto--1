#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include "Tarea.h"
#include <vector>

class ColaPrioridad {
private:
    std::vector<Tarea> heap;
    
    void flotar(int indice);
    void hundir(int indice);
    int padre(int indice) const;
    int hijoIzquierdo(int indice) const;
    int hijoDerecho(int indice) const;

public:
    ColaPrioridad();
    
    void insertar(const Tarea& tarea);
    Tarea extraerMaximo();
    Tarea obtenerMaximo() const;
    bool estaVacia() const;
    int getTamano() const;
    void mostrar() const;
    void limpiar();
};

#endif // COLAPRIORIDAD_H
