// Member function 'arrNamePars' definition
std::pair<std::string, size_t> Parser::arrNamePars(std::string& name, Variables& variables) {
    // Find the position of the '[' symbol in the array declaration
    size_t pos = name.find('[');
    if (pos == std::string::npos) {
        throw std::invalid_argument("The '[' symbol is expected.");
    }

    // Extract the array name (before '[') and the size (inside '[' and ']')
    std::string name1 = name.substr(0, pos);
    std::string val = name.substr(pos + 1, name.size() - pos - 2);

    size_t i{};
    if (variables.integers.contains(val)) {
        // If the size is a declared integer variable, get its value
        i = variables.integers[val].first;
    } else {
        // If the size is a constant (not declared as an integer), convert it to an integer
        i = std::stoi(val);
    }

    // Create a pair containing the array name and its size
    std::pair<std::string, size_t> arrInfo(name1, i);
    return arrInfo;
}


