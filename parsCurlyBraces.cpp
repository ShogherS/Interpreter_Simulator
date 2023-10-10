// Member function 'parsCurlyBraces' definition
void Parser::parsCurlyBraces() {
    std::stack<char> braces; // Stack to keep track of open curly braces

    // Iterate through each line of code in 'data'
    for (size_t i = 0; i < data.size(); ++i) {
        for (const char c : data[i]) {
            if (c == '{') {
                braces.push('{'); // Push an open curly brace onto the stack
            } else if (c == '}') {
                if (braces.empty()) {
                    // If a closing curly brace is encountered without a corresponding open brace, throw an exception
                    throw std::invalid_argument("The '}' is expected in line " + std::to_string(i) + ".");
                }
                braces.pop(); // Pop a matching open curly brace from the stack
            }
        }
    }

    // Check if there are any unmatched open curly braces left in the stack
    if (!braces.empty()) {
        throw std::invalid_argument("Curly braces mismatch.");
    }
}

bool Parser::hasIostream()
{
	std::string& iostream = data[0];
	removeSpace(0);
	return data[0] == "#include<iostream>" ? true : false;
}
