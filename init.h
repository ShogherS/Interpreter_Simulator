#ifndef INIT_H
#define INIT_H

#include <map>
#include <string>
#include <functional>
#include <stack>

#include "variables.h"
#include "utility.h"


struct Init
{
	std::map<std::string, std::function<void(std::vector<std::string>&, std::string&, Variables&)>> operations {
		 {"=", // Lambda function for assignment
			[](std::vector<std::string>& line, std::string& type, Variables& variables) {
			size_t i = 2;
		        // Check the variable type and perform the assignment accordingly
			if (type == "bool") {
				variables.booleans[line[0]].first = toBool(line[i], 111, variables);
			} else if (type == "int") {
				variables.integers[line[0]].first = toInt(line[i], 111, variables);
			} else if (type == "char") {
				variables.characters[line[0]].first = toChar(line[i], 111, variables);
			} else if (type == "double" || type == "float") {
				variables.doubles[line[0]].first = toDouble(line[i], 111, variables);
			} else if (type == "string") {
				std::string& value = variables.strings[line[0]].first;
				if (variables.strings.find(line[i]) != variables.strings.end()) {
					value = variables.strings[line[i]].first;
				} else {
					++i;
					while (i < line.size() &&  line[2].back() != '\"') {
						line[2] += " " + line[i];
						++i;
					}
					if (line[2].front() !='\"' || line[2].back() != '\"') {
						throw std::invalid_argument("Invalid value. A stirng literal is excpectrd.");	
					}		
					value = line[2];
				}
			} else if (type == "intArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.intArr[value.first][value.second] = toInt(line[2], 111, variables);
			} else if (type == "charArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.charArr[value.first][value.second] = toChar(line[2], 111, variables);
			} else if (type == "doubleArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.doubleArr[value.first][value.second] = toDouble(line[2], 111, variables);
			}

			++i;
			// Check for the semicolon to complete the statement
			if (i >= line.size() || line[i] != ";") {
				throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
			}
	}},
	{"+=",	// Lambda function for addition assignment
		 [](std::vector<std::string>& line, std::string& type, Variables& variables) {
		size_t i = 2;
	        // Check the variable type and perform the addition assignment accordingly
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  += for type bool.");                          
		} else if (type == "int") {
			variables.integers[line[0]].first += toInt(line[2], 222, variables);
		} else if (type == "char") {
			variables.characters[line[0]].first += toInt(line[2], 222, variables);
		} else if (type == "double" || type == "float") {
			variables.doubles[line[0]].first += toDouble(line[2], 222, variables);
		} else if (type == "string") {
			std::string& value = variables.strings[line[0]].first;
			if (variables.strings.find(line[i]) != variables.strings.end()) {
				value += variables.strings[line[i]].first;
			} else {    // Check if line[2] is a valid string literal
				if (line[2].front() !='\"' || line[2].back() != '\"') {
					throw std::invalid_argument("Invalid value. A stirng literal is excpectrd.");	
				}		
			}
			value.pop_back();
			std::string value2 = line[2].substr(1, line[2].size() - 1);
			value += " ";
			value += value2;
		} else if (type == "intArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.intArr[value.first][value.second] += toInt(line[2], 111, variables);
		} else if (type == "charArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.charArr[value.first][value.second] += toChar(line[2], 111, variables);
		} else if (type == "doubleArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.doubleArr[value.first][value.second] += toDouble(line[2], 111, variables);
		}
		++i;
	        // Check for the semicolon to complete the statement

		if (i >= line.size() || line[i] != ";") {
			throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
		}
	}},
	{"-=",	// Lambda function for subtraction assignment
		[](std::vector<std::string>& line, std::string& type, Variables& variables) {
		size_t i = 2;
		// Check the variable type and perform the subtraction assignment accordingly

		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  -= for type bool.");
		} else if (type == "int") {
			variables.integers[line[0]].first -= toInt(line[i], 333, variables);
		} else if (type == "char") {
			variables.characters[line[0]].first -= toInt(line[i], 333, variables);
		} else if (type == "double" || type == "float") {
			variables.doubles[line[0]].first -= toDouble(line[i], 333, variables);
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");
		} else if (type == "intArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.intArr[value.first][value.second] = toInt(line[2], 111, variables);
		} else if (type == "charArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.charArr[value.first][value.second] = toChar(line[2], 111, variables);
		} else if (type == "doubleArr") {
				std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
				variables.doubleArr[value.first][value.second] = toDouble(line[2], 111, variables);
		}
		++i;
		// Check for the semicolon to complete the statement
		if (i >= line.size() || line[i] != ";") {
				throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
		}
	}},
	{"++", [](std::vector<std::string>& line, std::string& type, Variables& variables){
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  ++ for type bool.");
		} else if (type == "int") {
			++variables.integers[line[0]].first;
		} else if (type == "char") {
			++variables.characters[line[0]].first;
		} else if (type == "double" || type == "float") {
			++variables.doubles[line[0]].first;
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");
		} else if (type == "intArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			++variables.intArr[value.first][value.second];
		} else if (type == "charArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			++variables.charArr[value.first][value.second];
		} else if (type == "doubleArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			++variables.doubleArr[value.first][value.second];
		}

		if ( 2 >= line.size() || line[2] != ";") {
			throw std::invalid_argument("Unknown symbole \"" + line[2]+ "\".");
		}
	} },
	{"--", [](std::vector<std::string>& line, std::string& type, Variables& variables){
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  -- for type bool.");
		} else if (type == "int") {
			--variables.integers[line[0]].first;
		} else if (type == "char") {
			--variables.characters[line[0]].first;
		} else if (type == "double") {
			--variables.doubles[line[0]].first;
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");
		} else if (type == "intArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			--variables.intArr[value.first][value.second];
		} else if (type == "charArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			--variables.charArr[value.first][value.second];
		} else if (type == "charArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			--variables.charArr[value.first][value.second];
		} else if (type == "doubleArr") {
			std::pair<std::string, size_t> value = arrNamePars(line[0], variables);
			--variables.doubleArr[value.first][value.second];
		}

		if ( 2 >= line.size() || line[2] != ";") {
			throw std::invalid_argument("Unknown symbole \"" + line[2]+ "\".");
		}
	} }
	};
	std::map<std::string, std::function<bool(std::string&, std::string&, Variables&)>> cmp {
	{"==", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "double") {
			double lhs = variables.doubles[argument1].first;
			double rhs = toDouble(argument2, 444, variables);
			return lhs == rhs;
		} else if (type == "doubleArr") {
			double lhs = toDouble(argument1, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
		} else if (type == "string") {
			std::string& value = variables.strings[argument1].first;
			if (type2 == "string") {
				return value == variables.strings[argument2].first ? true : false;
			} else {
				if (argument2.front() !='\"' || argument2.back() != '\"') {
					throw std::invalid_argument("Invalid value " + argument2 + ". A stirng literal is excpectrd.");	
				}		
			return value == argument2 ? true : false;
			}
		}
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		bool result = lhs == rhs;
		return result;
	} },
	{"!=", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "double") {
			double lhs = variables.doubles[argument1].first;
			double rhs = toDouble(argument2, 444, variables);
			return lhs != rhs;
		} else if (type == "doubleArr") {
			double lhs = toDouble(argument1, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
			return lhs != rhs;
		} else if (type == "string") {
			std::string& value = variables.strings[argument1].first;
			if (type2 == "string") {
				return value != variables.strings[argument2].first ? true : false;
			} else {
				if (argument2.front() !='\"' || argument2.back() != '\"') {
					throw std::invalid_argument("Invalid value " + argument2 + ". A stirng literal is excpectrd.");	
				}		
			return value != argument2 ? true : false;
			}
		}
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		bool result = lhs != rhs;
		return false;
	} },
	{"<", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		bool result{};
		if (type == "double" || type == "doubleArr") {
			double lhs = toDouble(argument2, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
			return lhs < rhs;
		} else if (type == "string" || type2 == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		result = lhs < rhs; 
		return result;
	} },
	{">", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "double" || type == "doubleArr") {
			double lhs = toDouble(argument1, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
			return lhs > rhs;
		} else if (type == "string" || type2 == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		bool result{};
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		result = lhs > rhs;
		return result;
	} }, 
	{"<=", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		bool result{};
		if (type == "double" || type == "doubleArr") {
			double lhs = toDouble(argument1, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
			return lhs <= rhs;
		} else if (type == "string" || type2 == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		result = lhs <= rhs; 
		return result;
	} },
	{">=", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "double" || type == "doubleArr") {
			double lhs = toDouble(argument1, 444, variables);
			double rhs = toDouble(argument2, 444, variables);
			return lhs >= rhs;
		} else if (type == "string" || type2 == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		bool result{};
		int lhs = toInt(argument1, 444, variables);
		int rhs = toInt(argument2, 444, variables);
		result = lhs >= rhs;
		return result;
	} } };

	std::map<std::string, std::function<bool(std::vector<std::vector<std::string>>&, Variables&,  size_t&)>> ifwh {
		{"if", [this](std::vector<std::vector<std::string>>& code, Variables& variables, size_t& line) -> bool {
			if (code[line].size() < 5) {	
				throw std::invalid_argument("Some arguments arre missing in line " + std::to_string(line) + ".");
			}
			if (!code[line][1].starts_with('(')) {
				throw std::invalid_argument("A ( is expectred in line " + std::to_string(line) + ".");
			}
			if (!cmp.contains(code[line][2])) {		
				throw std::invalid_argument("An invalid operator in line " + std::to_string(line) + ".");
			}
			if (!code[line][3].ends_with(')')){
				throw std::invalid_argument("A ) id expected in line" + std::to_string(line) + ".");
			}
			std::string operand1 = code[line][1].substr(1);
			std::string operation = code[line][2];
			std::string operand2 = code[line][3];
			operand2.pop_back(); 
			bool flag =  cmp[operation](operand1, operand2, variables);
			return flag;
		} },
		{"while", [this](std::vector<std::vector<std::string>>& code, Variables& variables, size_t& line) -> bool {
			if (code[line].size() < 5) {	
				throw std::invalid_argument("Some arguments arre missing in line " + std::to_string(line) + ".");
			}
			if (!code[line][1].starts_with('(')) {
				throw std::invalid_argument("A ( is expectred in line " + std::to_string(line) + ".");
			}
			if (!cmp.contains(code[line][2])) {		
				throw std::invalid_argument("An invalid operator in line " + std::to_string(line) + ".");
			}
			if (!code[line][3].ends_with(')')){
				throw std::invalid_argument("A ) id expected in line" + std::to_string(line) + ".");
			}
			std::string operand1 = code[line][1].substr(code[line][1].size() - 1);
			std::string operation = code[line][2];
			std::string operand2 = code[line][3];
			operand2.pop_back(); 
			bool flag =  cmp[operation](operand1, operand2, variables);
			return flag;
	} }
	};
	std::string isDeclared(Variables&, std::string&);
};


std::string Init::isDeclared(Variables& variables, std::string& key)
{
	if (variables.integers.find(key) != variables.integers.end()) {
		return variables.integers[key].second;
	} else if (variables.booleans.find(key) != variables.booleans.end()) {
		return  variables.booleans[key].second;	
	} else if (variables.characters.find(key) != variables.characters.end()) {
		return variables.characters[key].second;
	} else if (variables.strings.find(key) != variables.strings.end()) {	
		return variables.strings[key].second;
	} else if (variables.doubles.contains(key)) {
		return variables.doubles[key].second;
	}
	return "NO";
}
#endif //INIT_H
