#ifndef ARBOLGENERAL_H
#define ARBOLGENERAL_H

#include "Tarea.h"

class ArbolGeneral {
private:
    Tarea raiz;
    
    void mostrarAyuda(const Tarea& nodo, int nivel) const;
    Tarea* buscarAyuda(int id, Tarea& nodo);

public:
    ArbolGeneral();
    ArbolGeneral(const Tarea& raiz);
    
    void setRaiz(const Tarea& raiz);
    Tarea getRaiz() const;
    
    void agregarSubtarea(int idPadre, const Tarea& subtarea);
    void mostrar() const;
    Tarea* buscarTarea(int id);
    bool estaVacio() const;
};

#endif // ARBOLGENERAL_H
