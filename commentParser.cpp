// Member function 'commentParser' definition
void Parser::commentParser(size_t pos) {
    size_t position = data[pos].find("//"); // Find the position of "//" in the line

    if (position != std::string::npos) {
        data[pos].erase(position, data[pos].length()); // Remove the comment from the line
    }
}
