#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <functional>
#include <iostream>

#include "loader.h"
#include "variables.h"
#include "init.h"
// Definition of the Parser struct
struct Parser
{
    // Constructor that takes a reference to a vector of strings
    Parser(std::vector<std::string>&);

    // Member functions to parse and process code
    bool hasMain(size_t);
    void scopeParser(const char, const char, const size_t) const;
    bool hasIostream();
    bool variableParser(size_t&, Variables&);
    bool variableTypeParser(size_t) const;
    void commentParser(size_t);
    void semicolonParser(size_t) const;
    void parsCurlyBraces();
    void pars();
    void parsCout(const size_t);
    std::string getValue(std::string&);

    // Member functions for data processing and manipulation
    void processData();
    void removeSpace(size_t);
    void trimString(std::string&);
    void print() const;
    std::string isDeclared(const std::string&);
    void arrRhs(std::string&, std::string&, std::string&, const size_t size, const size_t, Variables&);
    std::pair<std::string, size_t> arrNamePars(std::string&, Variables&);
    void updateVars(Variables& newVars, Variables& variables);
    void checkRedefinition(const size_t line) const;
    void checkSemicolon(const size_t line) const;
    bool toBool(std::string&, size_t, Variables&);
    char toChar(std::string& , size_t, Variables&);
    int toInt(std::string&, const size_t, Variables&);
double toDouble(std::string& rhs, const size_t line, Variables&  variables);
// std::string toString(std::string&, const size_t, Variables&);
   // Member variables
    std::vector<std::string>& data; // Reference to a vector of strings
    std::vector<std::vector<std::string>> code; // 2D vector of strings

    Variables variables; // An instance of the Variables struct
    Init init; // An instance of the Init struct
    bool break_flag; // Boolean flag
};

#endif //PARSER_H
