/*
    Programa que toma una proposición lógica en notación infija,
    construye un árbol de sintaxis y la imprime en preorden.
*/
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <sstream>

struct Nodo {
    std::string valor;
    Nodo* der;
    Nodo* izq;
    Nodo(std::string v) : valor(v), der(nullptr), izq(nullptr) {}
};

std::map<std::string,int> jerarquia {
    {"<->", 0},
    {"->", 1},
    {"or", 2},
    {"and", 3},
    {"neg", 4}
};

bool esOperador(const std::string& token) {
    return jerarquia.count(token) > 0;
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
    while(ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

Nodo* construirArbol(const std::vector<std::string>& tokens) {
    std::stack<Nodo*> operandos;
    std::stack<std::string> operadores;

    auto aplicarOperador = [&]() {
        std::string operador = operadores.top(); operadores.pop();
        Nodo* nodo = new Nodo(operador);
        if (operador == "neg") {
            nodo->der = operandos.top(); operandos.pop();
        } else {
            nodo->der = operandos.top(); operandos.pop();
            nodo->izq = operandos.top(); operandos.pop();
        }
        operandos.push(nodo);
    };

    for (const std::string& token : tokens) {
        if (esVariable(token)) {
            operandos.push(new Nodo(token));
        } else if (token == "(") {
            operadores.push(token);
        } else if (token == ")") {
            while (!operadores.empty() && operadores.top() != "(") {
                aplicarOperador();
            }
            operadores.pop();
        } else if (esOperador(token)) {
            while (!operadores.empty() && operadores.top() != "(" && jerarquia[operadores.top()] >= jerarquia[token]) {
                aplicarOperador();
            }
            operadores.push(token);
        }
    }
    while (!operadores.empty()) {
        aplicarOperador();
    }

    return operandos.top();
}

void imprimirPreorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    std::cout << raiz->valor << " ";
    imprimirPreorden(raiz->izq);
    imprimirPreorden(raiz->der);
}

int main() {
    std::string proposicion;
    std::cout << "Ingrese una proposición lógica: \n(Debe tener espacio entre cada expresión. Ej: ( p or q ) and neg r)\n";
    std::getline(std::cin, proposicion);
    std::vector<std::string> tokens = tokenizar(proposicion);
    Nodo* arbol = construirArbol(tokens);
    imprimirPreorden(arbol);
    return 0;
}

