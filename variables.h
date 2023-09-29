#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <map>
#include <utility>
#include <vector>

// This is a header guard, ensuring that this header file is included only once in a compilation unit.

struct Variables
{
    // This struct defines a collection of various types of variables using C++ maps.
    
    // Maps for storing boolean variables with their names as keys.
    std::map<std::string, std::pair<bool, std::string>> booleans;
    
    // Maps for storing character variables with their names as keys.
    std::map<std::string, std::pair<char, std::string>> characters;
    
    // Maps for storing integer variables with their names as keys.
    std::map<std::string, std::pair<int, std::string>> integers;
    
    // Maps for storing string variables with their names as keys.
    std::map<std::string, std::pair<std::string, std::string>> strings;
    
    // Maps for storing character arrays (vectors) with their names as keys.
    std::map<std::string, std::vector<char>> charArr;
    
    // Maps for storing integer arrays (vectors) with their names as keys.
    std::map<std::string, std::vector<int>> intArr;
};

#endif // VARIABLES_H

