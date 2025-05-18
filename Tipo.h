#ifndef TIPO_H
#define TIPO_H

#include "Declaraciones.h"
#include <string>

class Tipo {
protected:
    std::string simbolo;

public:
    Tipo(const std::string& s) : simbolo(s) {}
    virtual ~Tipo() {}
    
    char dimeTipo() {
        if (simbolo.compare("int") == 0) return 'i';
        if (simbolo.compare("float") == 0) return 'f';
        if (simbolo.compare("string") == 0) return 's';
        if (simbolo.compare("void") == 0) return 'v';
        return 'v'; // valor por defecto
    }
};

#endif // TIPO_H 