// Member function 'scopeParser' definition
void Parser::scopeParser(const char open, const char close, const size_t pos) const {
    size_t countOfOpen{}, countOfClose{}; // Counters for open and close scopes

    // Iterate through each character in the line of code at 'pos'
    for (const char current : data[pos]) {
        if (current == open) {
            ++countOfOpen; // Increment the count for open scopes
        } else if (current == close) {
            ++countOfClose; // Increment the count for close scopes
        }

        // Check for an inappropriate count of close scopes
        if (countOfOpen < countOfClose) {
            throw std::invalid_argument("An inappropriate " + std::to_string(close) +
                                        " scope in line " + std::to_string(pos));
        }
    }

    // Check if the counts of open and close scopes are not equal
    if (countOfOpen != countOfClose) {
        throw std::invalid_argument("A " + std::to_string(open) + " scope in line " +
                                    std::to_string(pos) + " is not closed.");
    }
}
