#include "analyzer.h"
#include <cctype>
#include <unordered_set>
#include <algorithm>
#include <iostream>

Analyzer::Analyzer() {
    int tempM[18][33] = {
        // Estados:    m    M    n    _    +    -    *    /    %    =    (    )    [    ]    {    }    :    ,    ;    &    |    !    '    "    #    <    >    .    E    e    sp  otro  \0
        /* 0  */    {  1,   1,   2,   1, 105, 106, 108, 107, 109, 117, 115, 116, 114, 114, 122, 121, 118, 119, 120,  20,  20,  20,  10,  11,  13,  14,  15,  16,   1,   1,   0, 501,   0},
        /* 1  */    {  1,   1,   1,   1, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101,   1,   1, 101, 101, 101},
        /* 2  */    {102, 102,   2, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102,   3,   4,   4, 102, 102, 102},
        /* 3  */    {504, 504,   5, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
        /* 4  */    {504, 504,   6, 504,   7,   7, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
        /* 5  */    {103, 103,   5, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103,   4,   4, 103, 103, 103},
        /* 6  */    {104, 104,   6, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
        /* 7  */    {504, 504,   6, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
        /* 8  */    {104, 104,   8, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
        /* 9  */    {505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505,  10, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505},
        /* 10 */    {507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 110, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507},
        /* 11 */    { 11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  12,  11,  11,  11,  11,  11,  11,  11,  11,  11},
        /* 12 */    {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
        /* 13 */    { 13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13, 112},
        /* 14 */    { 14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14, 113,  14,  14,  14,  14,  14,  14},
        /* 15 */    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113},
        /* 16 */    {507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 126, 507, 507, 507, 507, 507},
        /* 17 */    {126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126}

    };
    memcpy(M, tempM, sizeof(tempM));
}


Analyzer::~Analyzer() {}

int Analyzer::charClass(char c) {
    if (std::isdigit(c)) {
        return 2;  // Dígitos
    }
    if (std::islower(c)) {
        return (c == 'e') ? 29 : 0;
    }
    if (std::isupper(c)) {
        return (c == 'E') ? 28 : 1;
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
    case '.': return 27;  // Punto decimal
    case ' ': case '\t': case '\r': return 30;
    case '\n': case '\0': return 32;
    default: return 31;
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
    std::transform(lexemaMinuscula.begin(), lexemaMinuscula.end(),
                   lexemaMinuscula.begin(), ::tolower);

    return palabrasReservadas.find(lexemaMinuscula) != palabrasReservadas.end() ? 100 : 101;
}

void Analyzer::addToken(int tokenCode) {
    if (lexema.empty()) return;

    std::string trimmedLexema = lexema;
    trimmedLexema.erase(0, trimmedLexema.find_first_not_of(" \t\n\r"));
    trimmedLexema.erase(trimmedLexema.find_last_not_of(" \t\n\r") + 1);

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
    case 126: gramema = "Rango (..)"; break;
    default: gramema = "Token Desconocido"; break;
    }

    tokens.push_back(Token{lexema, gramema});
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

    for (size_t i = 0; i <= input.length(); i++) {
        char c = (i < input.length()) ? input[i] : '\0';
        int clase = charClass(c);

        if (estadoActual >= 0 && estadoActual < 18 && clase >= 0 && clase < 33) {
            int estadoSiguiente = M[estadoActual][clase];

            // Estado de error
            if (estadoSiguiente >= 500) {
                logError(estadoSiguiente, lexema + c);
                estadoActual = 0;
                lexema.clear();
                continue;
            }

            // Estado de aceptación
            if (estadoSiguiente >= 100 && estadoSiguiente < 500) {
                if (clase != 30 && c != '\0') { // Si no es espacio en blanco ni fin de archivo
                    lexema += c;
                }
                addToken(estadoSiguiente);
                estadoActual = 0;
                lexema.clear();
                continue;
            }

            // Estado normal
            if (clase != 30) { // Si no es espacio en blanco
                lexema += c;
            }
            estadoActual = estadoSiguiente;

        } else {
            // Estado inválido
            if (!lexema.empty()) {
                logError(501, lexema);
                lexema.clear();
            }
            estadoActual = 0;
        }

        // Fin de archivo con lexema pendiente
        if (c == '\0' && !lexema.empty()) {
            if (estadoActual >= 100 && estadoActual < 500) {
                addToken(estadoActual);
            } else {
                logError(501, lexema);
            }
            lexema.clear();
        }
    }

    return tokens;
}

const std::vector<std::string>& Analyzer::getErrors() const {
    return errors;
}
