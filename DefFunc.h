#ifndef DEF_FUNC_H
#define DEF_FUNC_H

#include "Nodo.h"
#include "Tipo.h"
#include "Parametro.h"

class DefFunc : public Nodo {
public:
    Tipo* tipo;
    std::string simbolo;
    Parametro* parametros;
    Nodo* cuerpo;

    DefFunc(Tipo* t, const std::string& s, Parametro* p, Nodo* c)
        : tipo(t), simbolo(s), parametros(p), cuerpo(c) {}
    
    ~DefFunc() {
        delete tipo;
        delete parametros;
        delete cuerpo;
    }

    void validaTipos() override {
        tipoDato = tipo->dimeTipo();
        std::string ambitoAnterior = ambito;
        ambito = simbolo;
        
        if (tablaSimbolos) {
            tablaSimbolos->agrega(this);
        }
        
        if (parametros != nullptr) {
            parametros->validaTipos();
        }
        
        if (cuerpo != nullptr) {
            cuerpo->validaTipos();
        }
        
        ambito = ambitoAnterior;
        
        if (sig != nullptr) {
            sig->validaTipos();
        }
    }
};

#endif // DEF_FUNC_H 