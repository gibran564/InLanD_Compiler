#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include "token.h"

class Analyzer {
public:
    Analyzer();
    ~Analyzer();

    // Método principal que analiza una cadena y retorna los tokens encontrados
    std::vector<Token> analyzeString(const std::string &input);

    // Retorna los errores encontrados durante el análisis
    const std::vector<std::string>& getErrors() const;

private:
    // Determina la clase de carácter según la matriz de transiciones
    int charClass(char c);

    // Agrega un token con el código específico
    void addToken(int tokenCode);

    // Registra un error específico basado en el código de error
    void logError(int errorCode, const std::string& lexema);

    // Verifica si el lexema es una palabra reservada
    int checkReservedWord(const std::string& lexema);

    std::string lexema;           // Almacena el lexema en construcción
    int estado;                   // Estado actual durante el análisis
    size_t index;                 // Índice de posición en la cadena de entrada

    std::vector<std::string> errors; // Lista de mensajes de error
    std::vector<Token> tokens;       // Lista de tokens

    int M[16][33]; // Matriz de transiciones alineada con `tempM` en Analyzer.cpp

    std::string input;
    size_t idx;
};

#endif
