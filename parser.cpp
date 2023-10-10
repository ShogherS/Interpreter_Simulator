#include "parser.h"
#include "data_parser.cpp"
#include "getValue.cpp"
#include "parsCout.cpp"
#include "updateVars.cpp"
#include "arrRhs.cpp"
#include "arrNamePars.cpp"
#include "checkRedefinition.cpp"
#include "isDeclared.cpp"
#include "chackSemicolon.cpp"
#include "print.cpp"
#include "removeSpace.cpp"
#include "trimString.cpp"
#include "processData.cpp"
#include "parsCurlyBraces.cpp"
#include "semicolonParser.cpp"
#include "commentParser.cpp"
#include "scopeParser.cpp"
#include "variableParser.cpp"
#include "hasMain.cpp"

// Constructor definition for Parser
Parser::Parser(std::vector<std::string>& d) : data{d}, break_flag{false} {
    // Initialize the 'data' member with the provided vector 'd'.
    // Set 'break_flag' to 'false'.
    // Resize the 'code' vector to the size of 'data' minus 2.
    code.resize(data.size() - 2);
}

// Member function 'pars' definition
void Parser::pars() {
    size_t i = hasIostream() ? 1 : 0; // Initialize 'i' based on the presence of 'iostream'.
    size_t ioFlag = i; // Store the initial value of 'i'.
    
    hasMain(i); // Check if 'main' function is present in the code.
    ++i; // Increment 'i'.

    for (; i < data.size() - 1; ++i) {
        commentParser(i); // Parse comments in the code.
        trimString(data[i]); // Remove leading and trailing spaces from the line.
        scopeParser('(', ')', i); // Parse and check parentheses.
        scopeParser('[', ']', i); // Parse and check square brackets.
        semicolonParser(i); // Check for semicolons.
    }

    parsCurlyBraces(); // Check for curly braces.
    processData(); // Process the data.
    
    for (size_t i{}; i < code.size() - ioFlag; ++i) {
        variableParser(i, variables); // Parse and process variables.
    }

    print(); // Print the results.
}
