// Member function 'hasMain' definition
bool Parser::hasMain(size_t mainLine) {
    // Remove leading and trailing spaces from the line where 'main' should be.
    removeSpace(mainLine);

    // Check if the line where 'main' should be is not equal to "intmain(){".
    if (data[mainLine] != "intmain(){") {
        // If not, throw an invalid_argument exception indicating that the program does not have 'main'.
        throw std::invalid_argument("The program does not have a main.");
    } else {
        // If it is "intmain(){", continue checking.

        // Remove leading and trailing spaces from the last line of 'data'.
        removeSpace(data.size() - 1);

        // Check if the last line does not contain a closing curly brace '}'.
        if (data.back() != "}") {
            // If not, throw an invalid_argument exception indicating that 'main' does not have a closing scope.
            throw std::invalid_argument("The function main does not have a closing scope.");
        }
    }

    // If all checks pass, return 'true' indicating that 'main' is present and properly formatted.
    return true;
}
