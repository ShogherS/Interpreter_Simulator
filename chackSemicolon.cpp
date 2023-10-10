// Member function 'checkSemicolon' definition
void Parser::checkSemicolon(const size_t line) const {
    // Check if the 5th element (index 4) in the 'code' vector for the specified line is not equal to ";"
    if (code[line][4] != ";") {
        // If it's not equal to ";", throw an exception indicating an unknown symbol.
        throw std::invalid_argument("Unknown symbol " + code[line][4] + " in line " + std::to_string(line) + ".");
    }
}
