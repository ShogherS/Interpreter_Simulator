std::pair<std::string, size_t> arrNamePars(std::string& name, Variables& variables) {
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

std::string isDeclared(const std::string& key, Variables& variables) {
    // Check if the variable identifier 'key' is present in different maps within 'variables'
    if (variables.integers.find(key) != variables.integers.end()) {
        return variables.integers[key].second; // Return the type if it's an integer
    } else if (variables.booleans.find(key) != variables.booleans.end()) {
        return variables.booleans[key].second; // Return the type if it's a boolean
    } else if (variables.characters.find(key) != variables.characters.end()) {
        return variables.characters[key].second; // Return the type if it's a character
    } else if (variables.strings.find(key) != variables.strings.end()) {
        return variables.strings[key].second; // Return the type if it's a string
    } else if (variables.doubles.find(key) != variables.doubles.end()) {
        return variables.doubles[key].second; // Return the type if it's a double 
    } else if (variables.charArr.contains(key)) {
        return "charArr"; // Return "charArr" if it's a character array
    } else if (variables.intArr.contains(key)) {
        return "intArr"; // Return "intArr" if it's an integer array
    } else if (key.back() == ']') {
	std::string key1 = key;
	std::pair<std::string, size_t> value = arrNamePars(key1, variables);
	key1 = value.first;
		if (variables.charArr.contains(key1)) {
        		return "charArr"; // Return "charArr" if it's a character array
    		} else if (variables.intArr.contains(key1)) {
        		return "intArr"; // Return "intArr" if it's an integer array
    		}
	}
    // If the variable identifier 'key' is not found in any map, return "NO" to indicate it's not declared.
    return "NO";
}

bool toBool(std::string& rhs, size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs, variables);
	bool val{};
	if (type2 == "bool") {
		val = variables.booleans[rhs].first;
	} else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
	} else if (rhs.back() == ']') {
		std::string type = isDeclared(rhs, variables);
		std::pair<std::string, size_t> arrInfo = arrNamePars(rhs, variables);
		if (type == "charArr") {
			val = variables.charArr[arrInfo.first][arrInfo.second];
		} else if (type == "intArr") {
			val = variables.intArr[arrInfo.first][arrInfo.second];
		}
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
	}
	return val;
}

char toChar(std::string& rhs, size_t line, Variables& variables)
{
	std::string type2 = isDeclared(rhs, variables); 
	char val{};
	if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (type2 == "double") {
		val = variables.characters[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	} else if (rhs.back() == ']') {
		std::string type = isDeclared(rhs, variables);
		std::pair<std::string, size_t> arrInfo = arrNamePars(rhs, variables);
		if (type == "charArr") {
			val = variables.charArr[arrInfo.first][arrInfo.second];
		} else if (type == "intArr") {
			val = variables.intArr[arrInfo.first][arrInfo.second];
		}
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
		val = std::stoi(rhs);
	}
	return val;
}

int toInt(std::string& rhs, const size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs, variables); 
	int val{};
	if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	}  else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else if (rhs.back() == ']') {
		std::string type = isDeclared(rhs, variables);
		std::pair<std::string, size_t> arrInfo = arrNamePars(rhs, variables);
		if (type == "charArr") {
			val = variables.charArr[arrInfo.first][arrInfo.second];
		} else if (type == "intArr") {
			val = variables.intArr[arrInfo.first][arrInfo.second];
		}
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
		val = std::stoi(rhs);
	}
	return val;
}
double toDouble(std::string& rhs, const size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs, variables); 
	double val{};
	if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	}  else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else if (rhs.back() == ']') {
		std::string type = isDeclared(rhs, variables);
		std::pair<std::string, size_t> arrInfo = arrNamePars(rhs, variables);
		if (type == "charArr") {
			val = variables.charArr[arrInfo.first][arrInfo.second];
		} else if (type == "intArr") {
			val = variables.intArr[arrInfo.first][arrInfo.second];
		}
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
		val = std::stod(rhs);
	}
	return val;
}
