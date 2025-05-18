#include "TablaSimbolos.h"
#include "DefVar.h"
#include "DefFunc.h"
#include "Parametro.h"
#include "Nodo.h"
#include "Expresion.h"

TablaSimbolos::TablaSimbolos(std::list<std::string>* errores) : listaErrores(errores) {
    tabla.resize(100);
    varLocal = varGlobal = funcion = nullptr;
}

TablaSimbolos::~TablaSimbolos() {
    for (auto* elem : tabla) {
        delete elem;
    }
}

void TablaSimbolos::agrega(ElementoTabla* elemento) {
    tabla.push_back(elemento);
}

void TablaSimbolos::muestra() {
    std::cout << "Tabla de Símbolos:" << std::endl;
    for (const auto* elem : tabla) {
        if (elem) {
            std::cout << "Símbolo: " << elem->getSimbolo() 
                     << ", Tipo: " << elem->getTipo()
                     << ", Ámbito: " << elem->getAmbito() << std::endl;
        }
    }
}

bool TablaSimbolos::varGlobalDefinida(const std::string& simbolo) {
    for (const auto* elem : tabla) {
        if (elem && elem->getSimbolo() == simbolo && elem->getAmbito() == "global") {
            return true;
        }
    }
    return false;
}

bool TablaSimbolos::funcionDefinida(const std::string& simbolo) {
    for (const auto* elem : tabla) {
        if (auto* func = dynamic_cast<const Funcion*>(elem)) {
            if (func->getSimbolo() == simbolo) {
                return true;
            }
        }
    }
    return false;
}

bool TablaSimbolos::varLocalDefinida(const std::string& variable, const std::string& funcion) {
    for (const auto* elem : tabla) {
        if (elem && elem->getSimbolo() == variable && elem->getAmbito() == funcion) {
            return true;
        }
    }
    return false;
}

void TablaSimbolos::buscaIdentificador(const std::string& simbolo) {
    for (const auto* elem : tabla) {
        if (elem && elem->getSimbolo() == simbolo) {
            std::cout << "Identificador encontrado: " << simbolo << std::endl;
            return;
        }
    }
    listaErrores->push_back("Error: identificador '" + simbolo + "' no definido");
}

void TablaSimbolos::buscaFuncion(const std::string& simbolo) {
    for (const auto* elem : tabla) {
        if (auto* func = dynamic_cast<const Funcion*>(elem)) {
            if (func->getSimbolo() == simbolo) {
                std::cout << "Función encontrada: " << simbolo << std::endl;
                return;
            }
        }
    }
    listaErrores->push_back("Error: función '" + simbolo + "' no definida");
}

void TablaSimbolos::agrega(DefVar* defVar) {
    if (!defVar || !defVar->tipo || !defVar->listaVar) return;
    
    char tipo = defVar->tipo->dimeTipo();
    Identificador* p = defVar->listaVar;
    
    while (p != nullptr) {
        if (Nodo::ambito == "global") {
            if (varGlobalDefinida(p->simbolo)) {
                listaErrores->push_back("Error: variable global \"" + p->simbolo + "\" redefinida");
                p = p->sig;
                continue;
            }
        } else {
            if (varLocalDefinida(p->simbolo, Nodo::ambito)) {
                listaErrores->push_back("Error: variable local \"" + p->simbolo + "\" redefinida");
                p = p->sig;
                continue;
            }
        }
        
        ElementoTabla* elem = new Variable(tipo, p->simbolo, Nodo::ambito);
        agrega(elem);
        p = p->sig;
    }
}

void TablaSimbolos::agrega(DefFunc* defFunc) {
    if (!defFunc || !defFunc->tipo) return;

    if (funcionDefinida(defFunc->simbolo)) {
        listaErrores->push_back("Error: función \"" + defFunc->simbolo + "\" redefinida");
        return;
    }

    char tipoRetorno = defFunc->tipo->dimeTipo();
    ElementoTabla* elem = new Funcion(tipoRetorno, defFunc->simbolo);
    agrega(elem);
    
    if (defFunc->parametros != nullptr) {
        agrega(defFunc->parametros);
    }
}

void TablaSimbolos::agrega(Parametro* parametros) {
    if (!parametros || !parametros->tipo) return;

    Parametro* p = parametros;
    while (p != nullptr) {
        char tipo = p->tipo->dimeTipo();
        if (!varLocalDefinida(p->simbolo, Nodo::ambito)) {
            ElementoTabla* elem = new Variable(tipo, p->simbolo, Nodo::ambito);
            agrega(elem);
        } else {
            listaErrores->push_back("Error: parámetro '" + p->simbolo + "' redefinido en función '" + Nodo::ambito + "'");
        }
        p = p->sig;
    }
} 