#include "parser.h"

// Constructor definition for Parser
Parser::Parser(std::vector<std::string>& d) : data{d}, break_flag{false} {
    // Initialize the 'data' member with the provided vector 'd'.
    // Set 'break_flag' to 'false'.
    // Resize the 'code' vector to the size of 'data' minus 2.
    code.resize(data.size() - 2);
}

// Member function 'pars' definition
void Parser::pars() {
    size_t i = hasIostream() ? 1 : 0; // Initialize 'i' based on the presence of 'iostream'.
    size_t ioFlag = i; // Store the initial value of 'i'.
    
    hasMain(i); // Check if 'main' function is present in the code.
    ++i; // Increment 'i'.

    for (; i < data.size() - 1; ++i) {
        commentParser(i); // Parse comments in the code.
        trimString(data[i]); // Remove leading and trailing spaces from the line.
        scopeParser('(', ')', i); // Parse and check parentheses.
        scopeParser('[', ']', i); // Parse and check square brackets.
        semicolonParser(i); // Check for semicolons.
    }

    parsCurlyBraces(); // Check for curly braces.
    processData(); // Process the data.
    
    for (size_t i{}; i < code.size() - ioFlag; ++i) {
        variableParser(i, variables); // Parse and process variables.
    }

    print(); // Print the results.
}


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

// Member function 'variableParser' definition
bool Parser::variableParser(size_t& line, Variables& variables)
{
	std::vector<std::string>& current = code[line];
	if (current[1].back() == ']') {
		//array name analises
		std::pair<std::string, int> arrInfo =  arrNamePars(current[1], variables);
		//check redefinition
		if (isDeclared(arrInfo.first) != "NO") {
			throw std::invalid_argument("Redefinition in lien " + std::to_string(line) + "."); 
		}
		//check = sign
		if (current[2] != "=") {
			throw std::invalid_argument("The = is expected in line " + std::to_string(line) + ".");
		}
		//check rhs expression
		arrRhs(current[0], arrInfo.first, current[3], line, variables);	        // Check rhs expression for the array
		checkSemicolon(line);
	} else if (current[0] == "bool") {        // Handle boolean variable declaration
		checkRedefinition(line);
		std::string type2 = isDeclared(current[3]);
		bool val{};
		if (type2 == "bool") {
			val = variables.booleans[current[3]].first;
		} else if (current[3] == "true" || current[3] == "false") {
			val = "true" ? true : false;
		} else {
			throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ", true or false is excpected.");
		}
		checkSemicolon(line);
		std::pair<bool, std::string> p (val, "bool");
		variables.booleans[current[1]] = p;
	} else if (current[0] == "char") {        // Handle character variable declaration
		checkRedefinition(line);
		std::string type2 = isDeclared(current[3]);
		char val{};	
		if (current[3].size() == 3 && current[3][0] == '\'' &&  current[3][2] == '\'') {
			char val = current[3][1];
		} else if (type2 == "char") {
			val = variables.characters[current[3]].first;
		} else {
			throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ", a single character is excpected.");
		}
		checkSemicolon(line);
		std::pair<char, std::string> p (val, "char");
		variables.characters[current[1]] = p;
	} else if (current[0] == "int") {        // Handle integer variable declaration
		checkRedefinition(line);
		int val{};
		std::string type2 = isDeclared(current[3]); 
		if (type2 == "int") {
			val = variables.integers[current[3]].first;
		} else {
			val = std::stoi(current[3]);
		}
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
	} else if (current[0] == "float") {
	
	} else if (current[0] == "double") {
	
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
				if (code[line][0] == "break") {
					break_flag = true;
					flag = false;
					break;
				}
				variableParser(line, newVars);	
				updateVars(newVars, variables);
			}
			if (break_flag) {
				flag = false;
				break_flag = false;
				break;
			} 
			if (current[0] == "if") break;
			line = sline;
			flag = init.ifwh["while"](code,variables,line);
		}
		if (!flag) {
			line = fline;
			break_flag = false;
		}
	} else if (current[0] == "{" || current[0] == "}" || current[0] == "std::cin") {
	
	} else if (current[0] == "return") {        // Handle return statement
		line = code.size();	
	} else if (current[0] == "std::cout") {
		parsCout(line);	
	} else if (current[0] == "break"){
		
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

// Member function 'commentParser' definition
void Parser::commentParser(size_t pos) {
    size_t position = data[pos].find("//"); // Find the position of "//" in the line

    if (position != std::string::npos) {
        data[pos].erase(position, data[pos].length()); // Remove the comment from the line
    }
}

// Member function 'semicolonParser' definition
void Parser::semicolonParser(const size_t pos) const {
    std::string& line = data[pos]; // Get the line at 'pos'
    char end = line.back(); // Get the last character of the line

    // Check if the last character is a semicolon, an opening curly brace, or a closing curly brace
    if (end == ';' || end == '{' || end == '}') {
        return; // The line ends with a valid character, so return without error.
    }

    // If the last character is not one of the expected characters, throw an exception.
    throw std::invalid_argument("A semicolon is missing in line " + std::to_string(pos) + ".");
}

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

void Parser::removeSpace(size_t pos)
{
	data[pos].erase(std::remove_if(data[pos].begin(), data[pos].end(), ::isspace), data[pos].end()); 
}
// Member function 'print' definition
void Parser::print()const
{
	std::cout << "\n____________CODE____________" << std::endl;
	for (size_t i{}; i < code.size(); ++i) {
		std::cout <<i <<": " ;
		for (auto& word : code[i]) {
			std::cout << word << " " ;
		}
		std::cout << std::endl;
	}
	std::cout << "_____________________________________\n______________Variables__________________" << std::endl;
	
	for (auto& item : variables.booleans) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.integers) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.characters) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.strings) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item :variables.charArr) {
		std::cout << "Char array: " << item.first << ": " ;
		for (const auto c : item.second) {
			std::cout << c << ' ';
		}
		std::cout << std::endl;
	} 
	for (auto& item : variables.intArr) {
		std::cout << "Int array: " << item.first << ": ";
		for (int i : item.second) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
}

// Member function 'checkSemicolon' definition
void Parser::checkSemicolon(const size_t line) const {
    // Check if the 5th element (index 4) in the 'code' vector for the specified line is not equal to ";"
    if (code[line][4] != ";") {
        // If it's not equal to ";", throw an exception indicating an unknown symbol.
        throw std::invalid_argument("Unknown symbol " + code[line][4] + " in line " + std::to_string(line) + ".");
    }
}

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
    } else if (variables.charArr.contains(key)) {
        return "charArr"; // Return "charArr" if it's a character array
    } else if (variables.intArr.contains(key)) {
        return "intArr"; // Return "intArr" if it's an integer array
    }

    // If the variable identifier 'key' is not found in any map, return "NO" to indicate it's not declared.
    return "NO";
}

// Member function 'checkRedefinition' definition
void Parser::checkRedefinition(const size_t line) const {
    // Check the type of variable declaration (e.g., bool, char, int, string)
    if (code[line][0] == "bool") {
        // Check if a variable with the same name already exists in the 'booleans' map
        if (variables.booleans.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "char") {
        if (variables.characters.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "int") {
        if (variables.integers.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    } else if (code[line][0] == "string") {
        if (variables.strings.contains(code[line][1])) {
            throw std::invalid_argument("Redefinition in line " + std::to_string(line) + ".");
        }
    }

    // Check if the 3rd element (index 2) in the line is not equal to "="
    if (code[line][2] != "=") {
        throw std::invalid_argument("In line " + std::to_string(line) + ", '=' is expected.");
    }
}

// Member function 'arrNamePars' definition
std::pair<std::string, int> Parser::arrNamePars(std::string& name, Variables& variables) {
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
    std::pair<std::string, int> arrInfo(name1, i);
    return arrInfo;
}

void Parser::arrRhs(std::string& type, std::string& name, std::string& rhs, const size_t line, Variables& variables) {
    // Determine the type of the RHS expression (e.g., charArr, intArr, etc.)
    std::string type2 = isDeclared(rhs);
    type2 = type2.substr(0, type2.length() - 3);

    if (type2 == type) {
        // If the RHS type matches the expected type, copy the RHS into the corresponding array in 'variables'
        if (type2 == "char") {
            variables.charArr[name] = variables.charArr[rhs];
        } else if (type2 == "int") {
            variables.intArr[name] = variables.intArr[rhs];
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
            }
            variables.intArr[name] = arr;
            if (skip != '}') {
                throw std::invalid_argument("The '}' is expected in line " + std::to_string(line) + ".");
            }
        }
    }
}

void Parser::updateVars(Variables& newVars, Variables& variables) {
    // Update boolean variables
    for (auto& it : newVars.booleans) {
        if (variables.booleans.contains(it.first)) {
            variables.booleans[it.first] = it.second;
        }
    }

    // Update character variables
    for (auto& it : newVars.characters) {
        if (variables.characters.contains(it.first)) {
            variables.characters[it.first] = it.second;
        }
    }

    // Update integer variables
    for (auto& it : newVars.integers) {
        if (variables.integers.contains(it.first)) {
            variables.integers[it.first] = it.second;
        }
    }

    // Update string variables
    for (auto& it : newVars.strings) {
        if (variables.strings.contains(it.first)) {
            variables.strings[it.first] = it.second;
        }
    }

    // Update charArr variables
    for (auto& it : newVars.charArr) {
        if (variables.charArr.contains(it.first)) {
            variables.charArr[it.first] = it.second;
        }
    }

    // Update intArr variables
    for (auto& it : newVars.intArr) {
        if (variables.intArr.contains(it.first)) {
            variables.intArr[it.first] = it.second;
        }
    }
}

void Parser::parsCout(const size_t line) {
    if (!hasIostream()) {
        throw std::invalid_argument("The iostream header file is not included");
    }
    
    size_t count = 1;
    size_t size = code[line].size();
    
    while (count < size - 1 && code[line][count] == "<<") {
        ++count;
        
        if (code[line][count] == ";") {
            break;
        } else if (code[line][count] == "std::endl") {
            // If "std::endl" is encountered, print a newline and break
            std::cout << std::endl;
            break;
        }
        
        // Print the value associated with "<<" operator
        std::cout << getValue(code[line][count]);
        ++count;
    }
}

std::string Parser::getValue(std::string& name) {
    if (name.back() != ']') {
        // Not an array, check its data type
        std::string type = isDeclared(name);
        if (type == "bool") {
            bool val = variables.booleans[name].first;
            return val ? "true" : "false";
        } else if (type == "char") {
            char val = variables.characters[name].first;
            return std::string(1, val);
        } else if (type == "int") {
            int val = variables.integers[name].first;
            return std::to_string(val);
        } else if (type == "string") {
            std::string val = variables.strings[name].first;
            return val;
        }
    } else {
        // It's an array element, retrieve the array and index
        std::pair<std::string, int> p = arrNamePars(name, variables);
        std::string type = isDeclared(p.first);
        if (type == "charArr") {
            std::vector<char> val = variables.charArr[p.first];
            if (val.size() <= p.second) {
                throw std::invalid_argument("Segmentation fault.");
            }
            char ch = val[p.second];
            return std::string(1, ch);
        } else if (type == "intArr") {
            std::vector<int> val = variables.intArr[p.first];
            if (val.size() <= p.second) {
                throw std::invalid_argument("Segmentation fault.");
            }
            int i = val[p.second];
            return std::to_string(i);
        }
    }
    // If none of the above conditions match, return the original name
    return name;
}
