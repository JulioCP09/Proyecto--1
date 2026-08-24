#ifndef PILA_H
#define PILA_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Pila {
private:
    vector<string> items;

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
