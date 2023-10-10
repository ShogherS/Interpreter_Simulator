void Parser::trimString(std::string& str) 
{
    size_t start = str.find_first_not_of(" \t\n\r"); // Find the first non-white space character
    if (start == std::string::npos) {
        // The string consists only of white spaces
        str.clear(); // Clear the string
        return;
    }

    size_t end = str.find_last_not_of(" \t\n\r"); // Find the last non-white space character
    str = str.substr(start, end - start + 1); // Assign the trimmed part back to the string
}
