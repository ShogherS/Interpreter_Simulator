//#include "parser.h"
bool Parser::toBool(std::string& rhs, size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs);
	bool val{};
	if (type2 == "bool") {
		val = variables.booleans[rhs].first;
	} else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
	}
	return val;
}

char Parser::toChar(std::string& rhs, size_t line, Variables& variables)
{
	std::string type2 = isDeclared(rhs); 
	char val{};
	if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
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

int Parser::toInt(std::string& rhs, const size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs); 
	int val{};
	if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	}  else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else if (type2 == "double") {
		val = variables.doubles[rhs].first;
	} else {
		try {
			val = std::stoi(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
	}
	return val;
}	

double Parser::toDouble(std::string& rhs, const size_t line, Variables&  variables)
{
	std::string type2 = isDeclared(rhs); 
	double val{};
	if (type2 == "double") {
		val = variables.doubles[rhs].first;	
	} else if (type2 == "int") {
		val = variables.integers[rhs].first;
	} else if (type2 == "char"){
		val = variables.characters[rhs].first;
	} else if (type2 == "bool") {
		val = variables.characters[rhs].first;
	} else if (rhs.size() == 3 && rhs[0] == '\'' &&  rhs[2] == '\'') {
		val = rhs[1];
	}  else if (rhs == "true" || rhs == "false") {
		val = rhs == "true" ? true : false;
	} else {
		try {
			val = std::stod(rhs);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Conversion failed: invalid argument in line " + std::to_string(line) + ".");
		}
	}
	return val;
}	
