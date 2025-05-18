#ifndef PARAMETRO_H
#define PARAMETRO_H

#include "Nodo.h"
#include "Tipo.h"

class Parametro : public Nodo {
public:
    Tipo* tipo;
    std::string simbolo;
    Parametro* sig;

    Parametro(Tipo* t, const std::string& s)
        : tipo(t), simbolo(s), sig(nullptr) {}
    
    ~Parametro() {
        delete tipo;
        if (sig != nullptr) {
            delete sig;
        }
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

#endif // PARAMETRO_H 