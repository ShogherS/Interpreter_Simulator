// Member function 'processData' definition
void Parser::processData() {
    // Determine the starting index based on the presence of #include <iostream>
    size_t i = hasIostream() ? 2 : 1;
    size_t j = 0; // Index for populating the 'code' vector

    while (i < data.size() - 1) {
        std::istringstream lineStream(data[i]);
        std::string current;

        while (lineStream >> current) {
            code[j].push_back(current); // Add individual words to the 'code' vector
        }

        // Check if the last element of 'code[j]' ends with a semicolon
        if (!code[j].empty() && code[j].back().back() == ';') {
            code[j].back().pop_back(); // Remove the semicolon and add it as a separate element
            code[j].push_back(";");
        }

        // Handle cases where the variable is incremented or decremented (++/-- prefix or suffix)
        if (code[j].size() > 1 && code[j][0].starts_with("--")) {
            std::string name = code[j][0].substr(2);
            code[j].insert(code[j].begin(), name);
            code[j][1] = "--";
        }
        if (code[j].size() > 1 && code[j][0].ends_with("--")) {
            std::string name = code[j][0].substr(0, code[j][0].size() - 2);
            code[j].insert(code[j].begin(), name);
            code[j][1] = "--";
        }
        if (code[j].size() > 1 && code[j][0].ends_with("++")) {
            std::string name = code[j][0].substr(0, code[j][0].size() - 2);
            code[j].insert(code[j].begin(), name);
            code[j][1] = "++";
        }
        if (code[j].size() > 1 && code[j][0].starts_with("++")) {
            std::string name = code[j][0].substr(2);
            code[j].insert(code[j].begin(), name);
            code[j][1] = "++";
        }

        ++i;
        ++j;
    }
}


