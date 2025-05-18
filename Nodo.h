#ifndef NODO_H
#define NODO_H

#include "Declaraciones.h"
#include <string>
#include <list>

// Forward declarations
class TablaSimbolos;
class Expresion;
class Suma;
class Multiplicacion;
class Identificador;

class Nodo {
protected:
    Nodo* sig;
    char tipoDato;

public:
    // Hacemos públicos los miembros estáticos
    static TablaSimbolos* tablaSimbolos;
    static std::string ambito;

    // Friend classes
    friend class TablaSimbolos;
    friend class Expresion;
    friend class Suma;
    friend class Multiplicacion;
    friend class Identificador;

    Nodo() : sig(nullptr), tipoDato('v') {}
    virtual ~Nodo() {
        if (sig != nullptr) delete sig;
    }
    
    virtual void validaTipos() {
        tipoDato = 'v';
        if (sig != nullptr) sig->validaTipos();
    }

    // Getters públicos
    char getTipoDato() const { return tipoDato; }
    Nodo* getSiguiente() const { return sig; }
    void setSiguiente(Nodo* n) { sig = n; }
    void setTipoDato(char t) { tipoDato = t; }
};

#endif // NODO_H 