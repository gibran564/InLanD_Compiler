#include "analyzer.h"
#include <cctype>
#include <unordered_set>
#include <algorithm>
#include <iostream>

                      Analyzer::Analyzer() {
    int tempM[16][33] = {
        // Estados:    m    M    n    _    +    -    *    /    %    =    (    )    [    ]    {    }    :    ,    ;    &    |    !    '    "    #    <    >    .    E    e    sp  otro  \0
        /* 0  */    {  1,   1,   3,   1, 105, 106, 108, 107, 109, 117, 115, 116, 114, 114, 122, 121, 118, 119, 120,  20,  20,  20,  10,  11,  13,  14,  15, 125,   1,   1,   0, 501,   0},
        /* 1  */    {  1,   1,   1,   1, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,   1,   1, 101, 101, 101},
        /* 2  */    {102, 102,   2, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
        /* 3  */    {102, 102,   3, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102,   4,   6,   6, 102, 102, 102},
        /* 4  */    {500, 500,   5, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500},
        /* 5  */    {103, 103,   5, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103},
        /* 6  */    {501, 501,   7, 501,   7,   7, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501},
        /* 7  */    {104, 104,   8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
        /* 8  */    {104, 104,   8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
        /* 9  */    {505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505,  10, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505},
        /* 10 */    {507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 110, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507},
        /* 11 */    { 11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  12,  11,  11,  11,  11,  11,  11,  11,  11,  11},
        /* 12 */    {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
        /* 13 */    { 13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13, 112},
        /* 14 */    { 14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  15,  14,  14,  14,  14,  14,  14},
        /* 15 */    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113}
    };
    memcpy(M, tempM, sizeof(tempM));
}


Analyzer::~Analyzer() {}

int Analyzer::charClass(char c) {
    if (std::islower(c) && c != 'e') {
        return 0;  // Letras minúsculas (excepto 'e')
    }
    if (c == 'e') {
        return 29; // Letra 'e'
    }
    if (std::isupper(c) && c != 'E') {
        return 1;  // Letras mayúsculas (excepto 'E')
    }
    if (c == 'E') {
        return 28; // Letra 'E'
    }
    if (std::isdigit(c)) {
        return 2;  // Dígitos
    }

    switch (c) {
    case '_': return 3;   // Guion bajo
    case '+': return 4;   // Suma
    case '-': return 5;   // Resta
    case '*': return 6;   // Multiplicación
    case '/': return 7;   // División
    case '%': return 8;   // Módulo
    case '=': return 9;   // Igual
    case '(': return 10;  // Paréntesis izquierdo
    case ')': return 11;  // Paréntesis derecho
    case '[': return 12;  // Corchete izquierdo
    case ']': return 13;  // Corchete derecho
    case '{': return 14;  // Llave izquierda
    case '}': return 15;  // Llave derecha
    case ':': return 16;  // Dos puntos
    case ',': return 17;  // Coma
    case ';': return 18;  // Punto y coma
    case '&': return 19;  // Ampersand
    case '|': return 20;  // Barra vertical
    case '!': return 21;  // Admiración
    case '\'': return 22; // Comilla simple
    case '"': return 23;  // Comilla doble
    case '#': return 24;  // Numeral
    case '<': return 25;  // Menor que
    case '>': return 26;  // Mayor que
    case '.': return 27;  // Punto
    case ' ': case '\t': case '\r': return 30; // Espacios en blanco
    case '\n': return 32; // Tratamos el salto de línea como fin de línea para comentarios
    case '\0': return 32; // Fin de línea
    default: return 31;   // Otros caracteres
    }
}


int Analyzer::checkReservedWord(const std::string& lexema) {
    static const std::unordered_set<std::string> palabrasReservadas = {
        "program", "endprogram", "int", "longint", "real", "doble",
        "char", "string", "boolean", "array", "of", "if", "then",
        "else", "repeat", "until", "while", "do", "read", "write",
        "var", "eq", "neq", "gt", "ge", "lt", "le", "and", "or",
        "not"
    };

    std::string lexemaMinuscula = lexema;
    lexemaMinuscula.erase(0, lexemaMinuscula.find_first_not_of(" \t\n\r"));
    lexemaMinuscula.erase(lexemaMinuscula.find_last_not_of(" \t\n\r") + 1);
    std::transform(lexemaMinuscula.begin(), lexemaMinuscula.end(),
                   lexemaMinuscula.begin(), ::tolower);

    return palabrasReservadas.find(lexemaMinuscula) != palabrasReservadas.end() ? 100 : 101;
}

void Analyzer::addToken(int tokenCode) {
    if (lexema.empty()) return;

    // Remover espacios en blanco al inicio y final del lexema
    std::string trimmedLexema = lexema;
    trimmedLexema.erase(0, trimmedLexema.find_first_not_of(" \t\n\r"));
    trimmedLexema.erase(trimmedLexema.find_last_not_of(" \t\n\r") + 1);

    // Si es un identificador potencial, verificar si es palabra reservada
    if (tokenCode == 101) {
        tokenCode = checkReservedWord(trimmedLexema);
    }

    std::string gramema;
    switch (tokenCode) {
    case 100: gramema = "Palabra Reservada"; break;
    case 101: gramema = "Identificador"; break;
    case 102: gramema = "Número Entero"; break;
    case 103: gramema = "Número Real"; break;
    case 104: gramema = "Número en Notación Científica"; break;
    case 105: gramema = "Operador Suma (+)"; break;
    case 106: gramema = "Operador Resta (-)"; break;
    case 107: gramema = "Operador División (/)"; break;
    case 108: gramema = "Operador Multiplicación (*)"; break;
    case 109: gramema = "Operador Módulo (%)"; break;
    case 110: gramema = "Constante de Carácter"; break;
    case 111: gramema = "Cadena de Caracteres"; break;
    case 112: gramema = "Comentario de Línea"; break;
    case 113: gramema = "Comentario de Bloque"; break;
    case 114: gramema = "Corchete"; break;
    case 115: gramema = "Paréntesis que Abre"; break;
    case 116: gramema = "Paréntesis que Cierra"; break;
    case 117: gramema = "Operador de Asignación"; break;
    case 118: gramema = "Dos Puntos"; break;
    case 119: gramema = "Coma"; break;
    case 120: gramema = "Punto y Coma"; break;
    case 121: gramema = "Llave que Cierra"; break;
    case 122: gramema = "Llave que Abre"; break;
    case 123: gramema = "Operador Menor que (<)"; break;
    case 124: gramema = "Operador Mayor que (>)"; break;
    case 125: gramema = "Punto (.)"; break;
    default: gramema = "Token Desconocido"; break;
    }

    // Solo agregar el token si el lexema no está vacío después del trim
    if (!trimmedLexema.empty()) {
        tokens.push_back(Token{trimmedLexema, gramema});
    }
    lexema.clear();
}


void Analyzer::logError(int errorCode, const std::string& lexema) {
    std::string message;
    switch (errorCode) {
    case 501: message = "Error léxico: carácter inesperado en '" + lexema + "'"; break;
    case 502: message = "Error léxico: operador no reconocido en '" + lexema + "'"; break;
    case 503: message = "Error léxico: constante de carácter mal formada en '" + lexema + "'"; break;
    case 504: message = "Error léxico: número real mal formado en '" + lexema + "'"; break;
    case 505: message = "Error léxico: constante de cadena mal formada en '" + lexema + "'"; break;
    case 506: message = "Error léxico: comentario no cerrado correctamente"; break;
    default:  message = "Error desconocido en el lexema '" + lexema + "'"; break;
    }
    errors.push_back(message);
}

std::vector<Token> Analyzer::analyzeString(const std::string& input) {
    tokens.clear();
    errors.clear();
    lexema.clear();
    int estadoActual = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        int clase = charClass(c);

        if (clase < 0 || clase >= 33) {
            logError(501, lexema + c);
            estadoActual = 0;
            lexema.clear();
            continue;
        }

        if (estadoActual < 0 || estadoActual >= 16) {
            logError(501, lexema + c);
            estadoActual = 0;
            lexema.clear();
            continue;
        }

        int estadoSiguiente = M[estadoActual][clase];

        if ((c == ',' || c == ';') && !lexema.empty() && estadoActual != 11) {
            if (estadoActual >= 100 && estadoActual < 500) {
                addToken(estadoActual);
            } else if (estadoActual > 0) {
                addToken(estadoActual == 1 ? 101 : (estadoActual == 2 ? 102 : estadoActual));
            }
            lexema.clear();
            estadoActual = 0;

            lexema = c;
            addToken(c == ',' ? 119 : 120);
            lexema.clear();
            continue;
        }

        if (estadoSiguiente >= 500) {
            logError(estadoSiguiente, lexema + c);
            estadoActual = 0;
            lexema.clear();
            continue;
        }

        if (estadoSiguiente >= 100 && estadoSiguiente < 500) {
            if (estadoSiguiente != 112 && estadoSiguiente != 113) {
                lexema += c;
            }
            addToken(estadoSiguiente);
            estadoActual = 0;
        }
        else if (estadoSiguiente >= 0 && estadoSiguiente < 16) {
            lexema += c;
            estadoActual = estadoSiguiente;
        }
        else {
            logError(501, lexema + c);
            estadoActual = 0;
            lexema.clear();
        }
    }

    if (!lexema.empty()) {
        if (estadoActual >= 100 && estadoActual < 500) {
            addToken(estadoActual);
        } else if (estadoActual > 0) {
            // Para identificadores y números al final
            addToken(estadoActual == 1 ? 101 : (estadoActual == 2 ? 102 : estadoActual));
        } else {
            logError(501, lexema);
        }
    }

    return tokens;
}




const std::vector<std::string>& Analyzer::getErrors() const {
    return errors;
}
