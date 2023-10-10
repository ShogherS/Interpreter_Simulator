// Member function 'variableParser' definition
bool Parser::variableParser(size_t& line, Variables& variables)
{
	std::vector<std::string>& current = code[line];
	if (current[1].back() == ']' && (current[0] == "int" || current[0] == "char" || current[0] == "double" || current[0] == "float")) {
		//array name analises
		std::pair<std::string, size_t> arrInfo =  arrNamePars(current[1], variables);
		//check redefinition
		if (isDeclared(arrInfo.first) != "NO") {
			throw std::invalid_argument("Redefinition in lien " + std::to_string(line) + "."); 
		}
		//check = sign
		if (current[2] != "=") {
			throw std::invalid_argument("The = is expected in line " + std::to_string(line) + ".");
		}
		//check rhs expression
		arrRhs(current[0], arrInfo.first, current[3], line, arrInfo.second, variables);	        // Check rhs expression for the array
		checkSemicolon(line);
	} else if (current[0] == "bool") {        // Handle boolean variable declaration
		checkRedefinition(line);
		bool val = toBool(current[3], line, variables);
		checkSemicolon(line);
		std::pair<bool, std::string> p (val, "bool");
		variables.booleans[current[1]] = p;
	} else if (current[0] == "char") {        // Handle character variable declaration
		checkRedefinition(line);
		char val = toChar(current[3], line, variables);	
		checkSemicolon(line);
		std::pair<char, std::string> p (val, "char");
		variables.characters[current[1]] = p;
	} else if (current[0] == "int") {        // Handle integer variable declaration
		checkRedefinition(line);
		int val= toInt(current[3], line, variables);
		checkSemicolon(line);
		std::pair<int, std::string> p(val, "int");
		variables.integers[current[1]] = p;		
	} else if (current[0] == "string") {        // Handle string variable declaration
		checkRedefinition(line);
		std::string type2 = isDeclared(current[3]);
		std::string val;
		if (type2 == "string") {
			val = variables.strings[current[3]].first;
		} else {
			size_t count{4};
			val = current[3];
			while (count < current.size() && val.back() != '\"') {
				val +=  " " + current[count];
				++count;
			}
			if (val.front() !='\"' || val.back() != '\"') {
					throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ". A stirng literal is excpectrd.");	
		}
			if (count != current.size() - 1 || current[count] != ";") {
				throw std::invalid_argument("Invalid argument at line " + std::to_string(line) + ".");
			}
		}
		std::pair<std::string, std::string> p (val, "string");
		variables.strings[current[1]] = p;
	} else if (current[0] == "float" || current[0] == "double") {
		checkRedefinition(line);
		double val{toDouble(current[3], line, variables)};
		checkSemicolon(line);
		std::pair<double, std::string> p{val, "double"};
		variables.doubles[current[1]] = p;
	} else if (init.ifwh.contains(current[0])) {
		bool flag = init.ifwh[current[0]](code,variables, line);
		std::stack<char> curly;
		size_t fline = line;
		for (; fline < code.size(); ++fline) {
			for (auto& word : code[fline]) {
				for (const char c : word) {
					if (c == '}') {
						curly.pop();
					} else if (c == '{') {
						curly.push('{');
					} 
				}
			}
			if (curly.empty()) {
				break;
			}
		}
		
		size_t sline = line;
		while (flag && !break_flag) {
			while (line < fline) {
			//new variables with all the data
				Variables newVars = variables;
				++line;
			variableParser(line, newVars);	
				updateVars(newVars, variables);
			}
			if (current[0] == "if") break;
			line = sline;
			flag = init.ifwh["while"](code,variables,line);
		}
		if (!flag) {
			line = fline;
			break_flag = false;
		}
	} else if (current[0] == "{" || current[0] == "}" ) {
	} else if (current[0] == "std::cin") {
		if (current[1] != ">>") {
			throw std::invalid_argument("The input stream operator is expected in line " + std::to_string(line) + ">");
		}
		std::string type = isDeclared(current[2]);
		if (type == "NO") {
			throw std::invalid_argument("Use of undeclared identifier " + current[2] + " at line " + std::to_string(line) + ".");
		}
		std::string input;
		std::getline(std::cin, input);
		std::stringstream instream{input};
		int val{};
		double d{};
		if (type == "bool") {
			if (instream >> val) {
				variables.booleans[current[2]].first = val;
			}
		} else if (type == "char") {
			variables.characters[current[2]].first = input[0];
		} else if (type == "int") {
			if (instream >> val) {
				variables.integers[current[2]].first = val;
			}
		} else if (type == "double") {
			if (instream >> d) {
				variables.doubles[current[2]].first = d;
			}
		} else if (type == "stirng") {
			variables.strings[current[0]].first = input;
		} else if (type == "charArr") {
			std::pair<std::string, size_t> chArr = arrNamePars(current[2], variables);
			variables.charArr[chArr.first][chArr.second] = input[0];
		} else if (type == "intArr") {
			if (instream >> val) {
				std::pair<std::string, size_t> intArrInfo = arrNamePars(current[2], variables);
				variables.intArr[intArrInfo.first][intArrInfo.second] = val;
			}
		} else if (type == "doubleArr") {
			if (instream >> d) {
				std::pair<std::string, size_t> doArr = arrNamePars(current[2], variables);
				variables.doubleArr[doArr.first][doArr.second] = d;
			}
		}
	} else if (current[0] == "return") {        // Handle return statement
		line = code.size();	
	} else if (current[0] == "std::cout") {
		parsCout(line);	
	} else if (current[0] == "break"){
		size_t ccc{};
		while (ccc < 2) {
			if (code[line][0] == "}") {
				++ccc;
			}
			++line;
		}
		break_flag = true;
	} else {
		std::string varType = isDeclared(current[0]);        // Handle other cases (e.g., variable references, operations)
		if (varType == "NO") {	
			throw std::invalid_argument("Use of undeclared identifier " + std::to_string(line) + ".");
		}
		if (init.operations.find(current[1]) != init.operations.end()) {
			init.operations[current[1]](current, varType, variables);
		} else {
			throw std::invalid_argument("Unknown argument at line " + std::to_string(line) + "."); 
		}
	}
	return true;	// Return 'true' to indicate successful parsing
}


