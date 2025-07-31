/*
    Programa que toma una proposicion en notacion infija 
*/
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <sstream>

struct Nodo { 
    std::string valor;
    Nodo* izq;
    Nodo* der;

    Nodo(std::string v) : valor(v), izq(nullptr), der(nullptr) {}
};

std::map<std::string, int> jerarquia = {
    {"<->", 0},
    {"->", 1},
    {"or", 2},
    {"and", 3},
    {"neg", 4}
};

bool esOperador(const std::string& token) {
    return token == "neg" || token == "and" || token == "or" || token == "->" || token == "<->"; 
}

bool esParentesis(const std::string& token) {
    return token == "(" || token == ")";
}

bool esVariable(const std::string& token) {
    return !esOperador(token) && !esParentesis(token);
}

std::vector<std::string> tokenizar(const std::string& proposicion) {
    std::vector<std::string> tokens;
    std::istringstream ss(proposicion);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

Nodo* construirArbol(const std::vector<std::string>& tokens) {
    std::stack<Nodo*> operandos;
    std::stack<std::string> operadores;
    
}
