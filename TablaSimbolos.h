#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "Declaraciones.h"
#include "ElementoTabla.h"
#include "Tipo.h"
#include <string>
#include <list>
#include <vector>
#include <iostream>

class DefVar;
class DefFunc;
class Parametro;
class Nodo;

class TablaSimbolos {
private:
    std::vector<ElementoTabla*> tabla;
    ElementoTabla *varLocal, *varGlobal, *funcion;

public:
    std::list<std::string>* listaErrores;

    TablaSimbolos(std::list<std::string>* errores);
    ~TablaSimbolos();

    void agrega(ElementoTabla* elemento);
    void muestra();
    bool varGlobalDefinida(const std::string& simbolo);
    bool funcionDefinida(const std::string& simbolo);
    bool varLocalDefinida(const std::string& variable, const std::string& funcion);
    void buscaIdentificador(const std::string& simbolo);
    void buscaFuncion(const std::string& simbolo);

    void agrega(DefVar* defVar);
    void agrega(DefFunc* defFunc);
    void agrega(Parametro* parametros);

    // Nuevo método para buscar el tipo de un identificador
    char buscaTipoIdentificador(const std::string& simbolo, const std::string& ambito) {
        for (const auto* elem : tabla) {
            if (elem && elem->getSimbolo() == simbolo &&
                (elem->getAmbito() == ambito || elem->getAmbito() == "global")) {
                return elem->getTipo();
            }
        }
        return 'e'; // error si no se encuentra
    }
};

#endif // TABLA_SIMBOLOS_H 