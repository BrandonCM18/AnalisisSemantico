#include "Semantico.h"
#include "Nodo.h"
#include <string>
#include <iostream>

// Variables globales
TablaSimbolos* Nodo::tablaSimbolos = NULL;
std::string Nodo::ambito = "";

// Función auxiliar para construir el árbol de prueba
Nodo* construirArbol();  // Declaración - implementación en prueba.cpp

int main() {
    Nodo* arbol = construirArbol();
    
    Semantico semantico;
    semantico.analiza(arbol);
    
    delete arbol;
    return 0;
} 