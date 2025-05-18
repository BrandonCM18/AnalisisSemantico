#include "Semantico.h"
#include "DefVar.h"
#include "DefFunc.h"
#include "Expresion.h"
#include <iostream>

// Función auxiliar para construir el árbol de prueba
Nodo* construirArbol() {
    // Definición de variables globales
    Tipo* tipoInt = new Tipo("int");
    Tipo* tipoFloat = new Tipo("float");
    
    // Variable global int x
    Identificador* varX = new Identificador("x");
    DefVar* defVarX = new DefVar(tipoInt, varX);
    
    // Variable global float y
    Identificador* varY = new Identificador("y");
    DefVar* defVarY = new DefVar(tipoFloat, varY);
    defVarX->setSiguiente(defVarY);
    
    // Función void func(int a)
    Tipo* tipoVoid = new Tipo("void");
    Parametro* paramA = new Parametro(tipoInt, "a");
    
    // Cuerpo de la función: definición de variables locales y operaciones
    Identificador* varLocalX = new Identificador("x");
    DefVar* defVarLocalX = new DefVar(tipoInt, varLocalX);
    
    // Operación con error de tipos: x = a + y (int = int + float)
    Identificador* idA = new Identificador("a");
    Identificador* idY = new Identificador("y");
    Suma* suma = new Suma(idA, idY);
    
    // Conectar el cuerpo de la función
    defVarLocalX->setSiguiente(suma);
    
    // Crear y conectar la función
    DefFunc* func = new DefFunc(tipoVoid, "func", paramA, defVarLocalX);
    defVarY->setSiguiente(func);
    
    return defVarX;
} 