void Parser::arrRhs(std::string& type, std::string& name, std::string& rhs, const size_t line, const size_t size, Variables& variables) {
    // Determine the type of the RHS expression (e.g., charArr, intArr, etc.)
    std::string type2 = isDeclared(rhs);
    type2 = type2.substr(0, type2.length() - 3);
    if (type2 == type) {
        // If the RHS type matches the expected type, copy the RHS into the corresponding array in 'variables'
        if (type2 == "char") {
		if (variables.charArr[rhs].size() != size) {
			throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
	}
            variables.charArr[name] = variables.charArr[rhs];
        } else if (type2 == "int") {
		if (variables.intArr[rhs].size() != size) {
			throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
		}
	    variables.intArr[name] = variables.intArr[rhs];
        } else if (type2 == "double") {
		if (variables.intArr[rhs].size() != size) {
			throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
		}
	    variables.doubleArr[name] = variables.doubleArr[rhs];
        }
   } else {
        // If the RHS type does not match the expected type, it should be an array literal in { ... } format
        if (rhs.front() != '{' || rhs.back() != '}') {
            throw std::invalid_argument("The '{' and '}' are expected at line " + std::to_string(line) + ".");
        }
        
        // Handle the RHS based on the expected type
        if (type == "bool") {
            // Handle boolean arrays (omitted in your provided code)
        } else if (type == "char") {
            // Handle character arrays
            std::string arrstr = rhs;
            std::vector<char> arr;
            std::string tmp = "','";
            for (int i{2}; i < arrstr.size() - 2; ++i) {
                if ((i - 2) % 4 == 0) {
                    arr.push_back(arrstr[i]);
                    if (tmp != "','") {
                        throw std::invalid_argument("The array literal syntax error at line " + std::to_string(line) + ".");
                    }
                    tmp.clear();
                } else {
                    tmp.push_back(arrstr[i]);
                }
		if (tmp.size() > size) {
			throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
		}
            }
            variables.charArr[name] = arr;
        } else if (type == "int") {
            // Handle integer arrays
            std::stringstream strarr(rhs);
            strarr.ignore(1);
            std::vector<int> arr;
            int num{};
            char skip{};
            while (strarr >> num) {
                arr.push_back(num);
                strarr >> skip;
        	if (arr.size() > size) {
			throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
		}    
		}
            variables.intArr[name] = arr;
            if (skip != '}') {
                throw std::invalid_argument("The '}' is expected in line " + std::to_string(line) + ".");
            }
        } else if (type == "double" || type == "float") {
	// Handle double arrays
		std::stringstream strarr(rhs);
		strarr.ignore(1);
		std::vector<double> arr;
		double num{};
		std::string token;
		while (std::getline(strarr, token, ',')) {
			try {
				num = std::stod(token);
			} catch (const std::invalid_argument& e) {
				throw std::invalid_argument("Invalid argument: " + token + " at line " + std::to_string(line) + ".");
			} catch (const std::out_of_range& e) {
				throw std::out_of_range("Out of rangne " + token + " at line" + std::to_string(line) + ".");
			}
			arr.push_back(num);
			if (arr.size() > size) {
				throw std::invalid_argument("Error: excess elements in array in line " + std::to_string(line) + ".");
			}
		}    
		variables.doubleArr[name] = arr;
	}
    }
}
