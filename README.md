# Analizador Semántico

Este proyecto implementa un analizador semántico para un lenguaje de programación simple. El analizador realiza validaciones de tipos y manejo de ámbitos, detectando errores comunes en tiempo de compilación.

## Características

- Tabla de símbolos con manejo de ámbitos (global y local)
- Validación de tipos en expresiones aritméticas
- Detección de variables redefinidas
- Manejo de diferentes tipos de datos (int, float, void)
- Validación de operaciones aritméticas compatibles
- Reporte detallado de errores semánticos

## Estructura del Proyecto

- `Semantico.h`: Clase principal del analizador semántico
- `TablaSimbolos.h/.cpp`: Implementación de la tabla de símbolos
- `Nodo.h`: Clase base para todos los nodos del AST
- `Expresion.h`: Clases para expresiones y operaciones
- `DefVar.h`: Definición de variables
- `DefFunc.h`: Definición de funciones
- `Parametro.h`: Manejo de parámetros de funciones
- `Tipo.h`: Sistema de tipos
- `ElementoTabla.h`: Elementos de la tabla de símbolos

## Tipos de Validaciones

1. **Validación de Tipos**
   - Compatibilidad en operaciones aritméticas
   - Tipos correctos en asignaciones
   - Tipos de retorno en funciones

2. **Validación de Ámbitos**
   - Variables globales vs locales
   - Redefinición de variables
   - Acceso a variables en el ámbito correcto

3. **Validación de Funciones**
   - Parámetros correctos
   - Tipos de retorno
   - Redefinición de funciones

## Compilación y Ejecución

```bash
g++ -std=c++11 principal.cpp prueba.cpp TablaSimbolos.cpp -o analizador
./analizador
```

## Ejemplo de Uso

El archivo `prueba.cpp` contiene un ejemplo que demuestra las capacidades del analizador:

- Definición de variables globales y locales
- Función con parámetros
- Operaciones aritméticas con diferentes tipos
- Detección de errores de tipos

## Mensajes de Error

El analizador proporciona mensajes de error descriptivos como:
- "Error: tipos incompatibles en suma (i + f)"
- "Error: variable redefinida en ámbito actual"
- "Error: función no definida"

## Limitaciones Conocidas

- No soporta tipos de datos complejos
- No realiza optimizaciones
- No maneja expresiones booleanas

## Mejoras Futuras

- Agregar soporte para más tipos de datos
- Implementar análisis de flujo de control
- Agregar validación de inicialización de variables
- Mejorar el sistema de recuperación de errores 