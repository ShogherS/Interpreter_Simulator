#ifndef INIT_H
#define INIT_H

#include <map>
#include <string>
#include <functional>
#include <stack>

#include "variables.h"

struct Init
{
	std::map<std::string, std::function<void(std::vector<std::string>&, std::string&, Variables&)>> operations {
		 {"=", [](std::vector<std::string>& line, std::string& type, Variables& variables) {
			size_t i = 2;
			if (type == "bool") {
				bool& value = variables.booleans[line[0]].first;
				if (line[i] == "true") {
					value = true;
				} else if ( line[i] == "false") {
					value = false;
				} else if (variables.booleans.find(line[i]) != variables.booleans.end()) {
					value = variables.booleans[line[i]].first;
				} else {
					  throw std::invalid_argument("Invalid argument \"" + line[i] + "\".");    
				}                                             
			} else if (type == "int") {
				int& value = variables.integers[line[0]].first;
				if (variables.integers.find(line[i]) != variables.integers.end()) {
					value = variables.integers[line[i]].first;
				} else {
					value = std::stoi(line[i]);
				}	
			} else if (type == "char") {
				char& value = variables.characters[line[0]].first;
				if (variables.characters.find(line[i]) != variables.characters.end()) {
					value = variables.characters[line[i]].first;
				} else if (line[i].size() == 3 && line[i][0] == '\'' && line[i][2] == '\'' ) {
					value = line[i][1];
				} else {
					  throw std::invalid_argument("Invalid argument \"" + line[i] + "\".");    
				}                                             
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
			}
			++i;
			if (i >= line.size() || line[i] != ";") {
				throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
			}
	}},
	{"+=", [](std::vector<std::string>& line, std::string& type, Variables& variables) {
		size_t i = 2;
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  += for type bool.");                          
		} else if (type == "int") {
			int& value = variables.integers[line[0]].first;
			if (variables.integers.find(line[i]) != variables.integers.end()) {
				value += variables.integers[line[i]].first;
			} else {
				value += std::stoi(line[i]);
			}	
		} else if (type == "char") {
			throw std::invalid_argument("Invalid operation.  += for type char.");                          
		} else if (type == "string") {
			std::string& value = variables.strings[line[0]].first;
			if (variables.strings.find(line[i]) != variables.strings.end()) {
				value += variables.strings[line[i]].first;
			} else {
				if (line[2].front() !='\"' || line[2].back() != '\"') {
					throw std::invalid_argument("Invalid value. A stirng literal is excpectrd.");	
				}		
			}
			value += line[2];
		}
		++i;
		if (i >= line.size() || line[i] != ";") {
			throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
		}
	}},
	{"-=", [](std::vector<std::string>& line, std::string& type, Variables& variables) {
		size_t i = 2;
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  -= for type bool.");                          
		} else if (type == "int") {
			int& value = variables.integers[line[0]].first;
			if (variables.integers.find(line[i]) != variables.integers.end()) {
				value -= variables.integers[line[i]].first;
			} else {
				value -= std::stoi(line[i]);
			}	
		} else if (type == "char") {
			throw std::invalid_argument("Invalid operation.  -= for type char.");                          
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");                          
		} else if (type == "string") {
		}
		++i;
		if (i >= line.size() || line[i] != ";") {
				throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
		}
	}},
	{"++", [](std::vector<std::string>& line, std::string& type, Variables& variables){
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  -- for type bool.");                          
		} else if (type == "int") {
			int& value = variables.integers[line[0]].first;
			++value;	
		} else if (type == "char") {
			char& value = variables.characters[line[0]].first;
			++value;	
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");                          
		}
		if ( 2 >= line.size() || line[2] != ";") {
			throw std::invalid_argument("Unknown symbole \"" + line[2]+ "\".");                         
		}
	} },
	{"--", [](std::vector<std::string>& line, std::string& type, Variables& variables){
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation.  -- for type bool.");                          
		} else if (type == "int") {
			int& value = variables.integers[line[0]].first;
			--value;	
		} else if (type == "char") {
			char& value = variables.characters[line[0]].first;
			--value;	
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation.  -= for type string.");                          
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
		if (type2 != "NO") {
			std::string tmp = argument2;
			argument2 = argument1;
			argument1 = tmp;
		}
		if (type == "bool") {
			bool value = variables.booleans[argument1].first;
			if (argument2 == "true") {
				return value == true ? true : false;
			} else if ( argument2 == "false") {
				return value == false ? true : false;
			} else if (type2 == "bool") {
				return value == variables.booleans[argument2].first ? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2  + "\".");    
			}                                             
		} else if (type == "int") {
			int& value = variables.integers[argument1].first;
			if (type2 == "int") {
				return value == variables.integers[argument2].first ? true : false;
			} else {
				return value == std::stoi(argument2) ? true : false;
			}	
		} else if (type == "char") {
			char& value = variables.characters[argument1].first;
			if (type2 == "char") {
				return value == variables.characters[argument2].first ? true : false;
			} else if (argument2.size() == 3 && argument2[0] == '\'' && argument2[2] == '\'' ) {
				return value == argument2[1]? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2 + "\".");    
			}                                             
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
		throw std::invalid_argument("Unknown argument.");
		return false;
	} },
	{"!=", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type2 != "NO") {
			std::string tmp = argument2;
			argument2 = argument1;
			argument1 = tmp;
		}
		if (type == "bool") {
			bool value = variables.booleans[argument1].first;
			if (argument2 == "true") {
				return value != true ? true : false;
			} else if ( argument2 == "false") {
				return value != false ? true : false;
			} else if (type2 == "bool") {
				return value != variables.booleans[argument2].first ? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2  + "\".");    
			}                                             
		} else if (type == "int") {
			int& value = variables.integers[argument1].first;
			if (type2 == "int") {
				return value != variables.integers[argument2].first ? true : false;
			} else {
				return value != std::stoi(argument2) ? true : false;
			}	
		} else if (type == "char") {
			char& value = variables.characters[argument1].first;
			if (type2 == "char") {
				return value != variables.characters[argument2].first ? true : false;
			} else if (argument2.size() == 3 && argument2[0] == '\'' && argument2[2] == '\'' ) {
				return value != argument2[1]? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2 + "\".");    
			}                                             
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
		throw std::invalid_argument("Unknown argument.");
		return false;
	} },
	{"<", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation for boolean type.");
		} else if (type == "int") {
			int value = variables.integers[argument1].first;
			if (type2 == "int") {
				return value < variables.integers[argument2].first ? true : false;
			} else {
				return value < std::stoi(argument2) ? true : false;
			}	
		} else if (type == "char") {
			char value = variables.characters[argument1].first;
			if (type2 == "char") {
				return value < variables.characters[argument2].first ? true : false;
			} else if (argument2.size() == 3 && argument2[0] == '\'' && argument2[2] == '\'' ) {
				return value < argument2[1]? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2 + "\".");    
			}                                             
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		throw std::invalid_argument("THF <");
		return false;
	} },
	{">", [this](std::string& argument1, std::string& argument2, Variables& variables) -> bool {
		std::string type = isDeclared(variables, argument1);
		std::string type2 = isDeclared(variables, argument2);
		if (type == "bool") {
			throw std::invalid_argument("Invalid operation for boolean type.");
		} else if (type == "int") {
			int value = variables.integers[argument1].first;
			if (type2 == "int") {
				return value < variables.integers[argument2].first ? true : false;
			} else {
				return value < std::stoi(argument2) ? true : false;
			}	
		} else if (type == "char") {
			char value = variables.characters[argument1].first;
			if (type2 == "char") {
				return value < variables.characters[argument2].first ? true : false;
			} else if (argument2.size() == 3 && argument2[0] == '\'' && argument2[2] == '\'' ) {
				return value > argument2[1]? true : false;
			} else {
				  throw std::invalid_argument("Invalid argument \"" + argument2 + "\".");    
			}                                             
		} else if (type == "string") {
			throw std::invalid_argument("Invalid operation for string type.");	
		}
		throw std::invalid_argument("Unknown argument.");
		return false;
	} } 
	};

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
	}
	return "NO";
}

#endif //INIT_H
