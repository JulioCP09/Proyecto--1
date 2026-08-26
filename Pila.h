#ifndef PILA_H
#define PILA_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class PilaGenerica {
private:
    vector<T> elementos;

public:
    void push(const T& elemento) { elementos.push_back(elemento); }
    T pop() {
        if (elementos.empty()) throw std::out_of_range("La pila esta vacia.");
        T elemento = elementos.back();
        elementos.pop_back();
        return elemento;
    }
    const T& peek() const {
        if (elementos.empty()) throw std::out_of_range("La pila esta vacia.");
        return elementos.back();
    }
    bool estaVacia() const { return elementos.empty(); }
    int getTamano() const { return static_cast<int>(elementos.size()); }
    void limpiar() { elementos.clear(); }
};

class Pila {
private:
    PilaGenerica<string> items;

public:
    Pila();
    
    void push(const string& accion);
    string pop();
    string peek() const;
    bool estaVacia() const;
    int getTamano() const;
    void limpiar();
};

#endif // PILA_H
