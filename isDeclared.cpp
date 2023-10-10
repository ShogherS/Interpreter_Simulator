// Member function 'isDeclared' definition
std::string Parser::isDeclared(const std::string& key) {
    // Check if the variable identifier 'key' is present in different maps within 'variables'
    if (variables.integers.find(key) != variables.integers.end()) {
        return variables.integers[key].second; // Return the type if it's an integer
    } else if (variables.booleans.find(key) != variables.booleans.end()) {
        return variables.booleans[key].second; // Return the type if it's a boolean
    } else if (variables.characters.find(key) != variables.characters.end()) {
        return variables.characters[key].second; // Return the type if it's a character
    } else if (variables.strings.find(key) != variables.strings.end()) {
        return variables.strings[key].second; // Return the type if it's a string
    } else if (variables.doubles.contains(key)) {
	return variables.doubles[key].second;
    } else if (variables.charArr.contains(key)) {
        return "charArr"; // Return "charArr" if it's a character array
    } else if (variables.intArr.contains(key)) {
        return "intArr"; // Return "intArr" if it's an integer array
    } else if (variables.doubleArr.contains(key)) {
        return "doubleArr"; // Return "intArr" if it's an integer array
    } else if (key.back() == ']') {
	std::string key1 = key;
	std::pair<std::string, size_t> value = arrNamePars(key1, variables);
	key1 = value.first;
		if (variables.charArr.contains(key1)) {
        		return "charArr"; // Return "charArr" if it's a character array
    		} else if (variables.intArr.contains(key1)) {
        		return "intArr"; // Return "intArr" if it's an integer array
    		} else if (variables.doubleArr.contains(key1)) {
        		return "doubleArr"; // Return "doubleArr" if it's an integer array
    		}
	}
    // If the variable identifier 'key' is not found in any map, return "NO" to indicate it's not declared.
    return "NO";
}

