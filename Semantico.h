#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Nodo.h"
#include "TablaSimbolos.h"
#include <iostream>
#include <list>

class Semantico {
private:
    Nodo* arbol;
    TablaSimbolos* tablaSimbolos;
    std::list<std::string>* listaErrores;

public:
    Semantico() : arbol(nullptr) {
        listaErrores = new std::list<std::string>();
        tablaSimbolos = new TablaSimbolos(listaErrores);
        Nodo::tablaSimbolos = tablaSimbolos;
        Nodo::ambito = "global";
    }

    ~Semantico() {
        if (arbol != nullptr) {
            delete arbol;
        }
        if (tablaSimbolos != nullptr) {
            delete tablaSimbolos;
        }
        if (listaErrores != nullptr) {
            delete listaErrores;
        }
        Nodo::tablaSimbolos = nullptr;
    }

    void analiza(Nodo* raiz) {
        // Limpiamos el árbol anterior si existe
        if (arbol != nullptr) {
            delete arbol;
        }
        arbol = raiz;

        if (arbol != nullptr) {
            // Reiniciamos el ámbito global
            Nodo::ambito = "global";
            
            // Realizamos el análisis semántico
            arbol->validaTipos();
            
            // Mostramos resultados
            mostrarResultados();
        }
    }

private:
    void mostrarResultados() {
        // Mostrar errores si existen
        if (listaErrores != nullptr && !listaErrores->empty()) {
            std::cout << "\n=== Errores Semánticos Encontrados ===\n" << std::endl;
            for (const auto& error : *listaErrores) {
                std::cout << error << std::endl;
            }
            std::cout << "\n=== Fin de Errores ===\n" << std::endl;
        } else {
            std::cout << "\n=== Análisis Semántico Completado ===\n" << std::endl;
            std::cout << "No se encontraron errores semánticos.\n" << std::endl;
        }

        // Mostrar tabla de símbolos
        std::cout << "=== Tabla de Símbolos ===\n" << std::endl;
        if (tablaSimbolos != nullptr) {
            tablaSimbolos->muestra();
        }
        std::cout << "\n=== Fin de Tabla de Símbolos ===\n" << std::endl;
    }
};

#endif // SEMANTICO_H 