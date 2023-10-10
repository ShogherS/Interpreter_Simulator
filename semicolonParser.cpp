// Member function 'semicolonParser' definition
void Parser::semicolonParser(const size_t pos) const {
    std::string& line = data[pos]; // Get the line at 'pos'
    char end = line.back(); // Get the last character of the line

    // Check if the last character is a semicolon, an opening curly brace, or a closing curly brace
    if (end == ';' || end == '{' || end == '}') {
        return; // The line ends with a valid character, so return without error.
    }

    // If the last character is not one of the expected characters, throw an exception.
    throw std::invalid_argument("A semicolon is missing in line " + std::to_string(pos) + ".");
}
