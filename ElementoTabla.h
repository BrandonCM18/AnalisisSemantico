#ifndef ELEMENTO_TABLA_H
#define ELEMENTO_TABLA_H

#include "Declaraciones.h"
#include <string>

class ElementoTabla {
protected:
    char tipo;
    std::string simbolo;
    std::string ambito;

public:
    ElementoTabla(char t, const std::string& s, const std::string& a) 
        : tipo(t), simbolo(s), ambito(a) {}
    virtual ~ElementoTabla() {}

    char getTipo() const { return tipo; }
    std::string getSimbolo() const { return simbolo; }
    std::string getAmbito() const { return ambito; }
};

class Variable : public ElementoTabla {
public:
    Variable(char t, const std::string& s, const std::string& a) 
        : ElementoTabla(t, s, a) {}
};

class Funcion : public ElementoTabla {
public:
    Funcion(char t, const std::string& s) 
        : ElementoTabla(t, s, "global") {}
};

#endif // ELEMENTO_TABLA_H 