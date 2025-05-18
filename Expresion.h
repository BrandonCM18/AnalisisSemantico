#ifndef EXPRESION_H
#define EXPRESION_H

#include "Nodo.h"
#include <string>
#include <list>

// Forward declarations
class TablaSimbolos;

class Expresion : public Nodo {
public:
    virtual ~Expresion() = default;
    virtual void validaTipos() override = 0;
};

// Operaciones binarias
class OperacionBinaria : public Expresion {
protected:
    Expresion* izq;
    Expresion* der;

public:
    OperacionBinaria(Expresion* i, Expresion* d) : izq(i), der(d) {}
    virtual ~OperacionBinaria() {
        delete izq;
        delete der;
    }
};

// Suma
class Suma : public OperacionBinaria {
public:
    Suma(Expresion* i, Expresion* d) : OperacionBinaria(i, d) {}
    
    void validaTipos() override {
        if (izq) izq->validaTipos();
        if (der) der->validaTipos();
        
        if (!izq || !der) {
            tipoDato = 'e';
            return;
        }
        
        char tipoIzq = izq->getTipoDato();
        char tipoDer = der->getTipoDato();
        
        if (tipoIzq == 'e' || tipoDer == 'e') {
            tipoDato = 'e';
            return;
        }
        
        if (tipoIzq == 'i' && tipoDer == 'i') {
            tipoDato = 'i';
        } else if (tipoIzq == 'f' && tipoDer == 'f') {
            tipoDato = 'f';
        } else {
            tipoDato = 'e';
            if (tablaSimbolos != nullptr && tablaSimbolos->listaErrores != nullptr) {
                std::string msgError = "Error: tipos incompatibles en suma (";
                msgError += tipoIzq;
                msgError += " + ";
                msgError += tipoDer;
                msgError += ")";
                tablaSimbolos->listaErrores->push_back(msgError);
            }
        }
    }
};

// Multiplicación
class Multiplicacion : public OperacionBinaria {
public:
    Multiplicacion(Expresion* i, Expresion* d) : OperacionBinaria(i, d) {}
    
    void validaTipos() override {
        if (izq) izq->validaTipos();
        if (der) der->validaTipos();
        
        if (!izq || !der) {
            tipoDato = 'e';
            return;
        }
        
        char tipoIzq = izq->getTipoDato();
        char tipoDer = der->getTipoDato();
        
        if (tipoIzq == 'e' || tipoDer == 'e') {
            tipoDato = 'e';
            return;
        }
        
        if (tipoIzq == 'i' && tipoDer == 'i') {
            tipoDato = 'i';
        } else if (tipoIzq == 'f' && tipoDer == 'f') {
            tipoDato = 'f';
        } else {
            tipoDato = 'e';
            if (tablaSimbolos != nullptr && tablaSimbolos->listaErrores != nullptr) {
                std::string msgError = "Error: tipos incompatibles en multiplicación (";
                msgError += tipoIzq;
                msgError += " * ";
                msgError += tipoDer;
                msgError += ")";
                tablaSimbolos->listaErrores->push_back(msgError);
            }
        }
    }
};

// Identificador
class Identificador : public Expresion {
public:
    std::string simbolo;
    Identificador* sig;
    
    Identificador(const std::string& s) : simbolo(s), sig(nullptr) {}
    ~Identificador() {
        if (sig != nullptr) delete sig;
    }
    
    void validaTipos() override {
        if (tablaSimbolos != nullptr) {
            tipoDato = tablaSimbolos->buscaTipoIdentificador(simbolo, ambito);
            if (tipoDato == 'e') {
                tablaSimbolos->buscaIdentificador(simbolo);
            }
        }
        if (sig != nullptr) sig->validaTipos();
    }
};

#endif // EXPRESION_H 