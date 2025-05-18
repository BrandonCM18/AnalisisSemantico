#ifndef DEF_VAR_H
#define DEF_VAR_H

#include "Nodo.h"
#include "Tipo.h"
#include "Expresion.h"

class DefVar : public Nodo {
public:
    Tipo* tipo;
    Identificador* listaVar;

    DefVar(Tipo* t, Identificador* lista) : tipo(t), listaVar(lista) {}
    
    ~DefVar() {
        delete tipo;
        delete listaVar;
    }

    void validaTipos() override {
        tipoDato = tipo->dimeTipo();
        if (tablaSimbolos) {
            tablaSimbolos->agrega(this);
        }
        if (sig != nullptr) {
            sig->validaTipos();
        }
    }
};

#endif // DEF_VAR_H 