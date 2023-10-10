// Member function 'checkRedefinition' definition
void Parser::checkRedefinition(const size_t line) const {
    // Check the type of variable declaration (e.g., bool, char, int, string)
    if (code[line][0] == "bool") {
        // Check if a variable with the same name already exists in the 'booleans' map
        if (variables.booleans.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "char") {
        if (variables.characters.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "int") {
        if (variables.integers.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "string") {
        if (variables.strings.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "double" || code[line][0] == "float") {
	if (variables.doubles.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    }
    // Check if the 3rd element (index 2) in the line is not equal to "="
    if (code[line][2] != "=") {
        throw std::invalid_argument("In line " + std::to_string(line) + ", '=' is expected.");
    }
}


