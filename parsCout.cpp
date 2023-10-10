void Parser::parsCout(const size_t line) {
    if (!hasIostream()) {
        throw std::invalid_argument("The iostream header file is not included");
    }
    
    size_t count = 1;
    size_t size = code[line].size();
    while (count < size - 1 && code[line][count - 1] != "std::endl;") {
        ++count;
        
        if (code[line][count] == ";") {
            break;
        } else if (code[line][count] == "std::endl") {
            // If "std::endl" is encountered, print a newline and break
            std::cout << std::endl;
            break;
        }
        
        // Print the value associated with "<<" operator
        std::cout << getValue(code[line][count]) << ' ';
        ++count;
    }
}
