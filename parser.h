#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <functional>


#include "loader.h"
#include "variables.h"
#include "init.h"

struct Parser
{
	Parser(std::vector<std::string>&);
	bool hasMain(size_t);
	void scopeParser(const char, const char, const size_t) const;
	bool hasIostream();
	bool variableParser(size_t&);
	bool variableTypeParser(size_t) const;
	void commentParser(size_t);
	void semicolonParser(size_t) const;
	void parsCurlyBraces();
	void pars();
	
	//helper
	void processData();
	void removeSpace(size_t);
	void trimString(std::string&);
	void print()const;
	std::string isDeclared(const size_t, const size_t);
	std::vector<std::string>& data;
	std::vector<std::vector<std::string>> code;

//helper function to check the line
	void checkRedefinition(const size_t line) const;	
	void checkSemicolon(const size_t line)const;
	//variables
	Variables variables;
	Init init;
	bool break_flag;
};

Parser::Parser(std::vector<std::string>& d) : data{d}, break_flag{false} { code.resize(data.size() - 2); }

void Parser::pars()
{
	size_t i = hasIostream() ? 1 : 0;
	size_t ioFlag = i;
	hasMain(i);
	++i;	
	for ( ; i < data.size() - 1; ++i) {
		commentParser(i);
		trimString(data[i]);
		scopeParser('(', ')', i);
		scopeParser('[', ']', i);
		semicolonParser(i);
	}
	parsCurlyBraces();
	processData();
	for (size_t i{}; i < code.size() - ioFlag; ++i) {
		variableParser(i);
	}
	print();
}

bool Parser::hasMain(size_t mainLine)
{
	removeSpace(mainLine);
	if (data[mainLine] != "intmain(){") {
		throw std::invalid_argument("The program does not have a main.");
	} else {
		removeSpace(data.size() - 1);
		if (data.back() != "}") {
			throw std::invalid_argument("The function main does not have a closing scope.");
		}
	}
	return true;
}

bool Parser::variableParser(size_t& line)
{
	std::vector<std::string>& current = code[line];
	std::cout << current[0]  << "____tins line is excecuted. Line : " << line <<std::endl;
	if (current[1].back() == ']') {
	} else if (current[0] == "bool") {
		checkRedefinition(line);
		std::string type2 = isDecleared(line, 3);
//		if (type2 == "bool") {
			


		if (current[3] != "true" && current[3] != "false") {
			throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ", true or false is excpected.");
		}
		bool val = current[3] == "true" ? true : false;
		std::pair<bool, std::string> p (val, "bool");
		variables.booleans[current[1]] = p;
		
		checkSemicolon(line);
	} else if (current[0] == "char") {
		checkRedefinition(line);	
		if (current[3].size() != 3 || current[3][0] != '\'' || current[3][2] != '\'') {
			throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ", a single character is excpected.");
		}
		checkSemicolon(line);
		char val = current[3][1];
		std::pair<char, std::string> p (val, "char");
		variables.characters[current[1]] = p;
	} else if (current[0] == "int") {
		checkRedefinition(line);
		int value = std::stoi(current[3]);
		checkSemicolon(line);
		std::pair<int, std::string> p(value, "int");
		variables.integers[current[1]] = p;		

	} else if (current[0] == "string") {
		checkRedefinition(line);
		
		size_t count{4};
		while (count < current.size() &&  current[3].back() != '\"') {
			current[3] += " " + current[count];
			++count;
		}
		if (current[3].front() !='\"' || current[3].back() != '\"') {
			throw std::invalid_argument("Invalid value in line " + std::to_string(line) + ". A stirng literal is excpectrd.");	
	}
		if (count != current.size() - 1 || current[count] != ";") {
			throw std::invalid_argument("Invalid argument at line " + std::to_string(line) + ".");
		}
		std::pair<std::string, std::string> p (current[3], "string");
		variables.strings[current[1]] = p;

	} else if (current[0] == "float") {
	
	} else if (current[0] == "double") {
	
	} else if (init.ifwh.contains(current[0])) {
		bool flag = init.ifwh[current[0]](code,variables, line);
		std::cout << "The flag is : "<< flag << " in line " << line << std::endl;
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
				std::cout <<"the end of condition statement is " << fline << std::endl;
				break;
			}
		}
		
		size_t sline = line;
		while (flag && !break_flag) {
			std::cout << line << std::endl;
			while (line < fline) {
				++line;
				if (code[line][0] == "break") {
					break_flag = true;
					flag = false;
					break;
				}
				variableParser(line);	
			}
			if (break_flag) {
					std::cout << "break happend" << std::endl;
				flag = false;
				break;
			} 
			if (current[0] == "if") break;
			line = sline;
			flag = init.ifwh["while"](code,variables,line);
		}
		if (!flag) {
			line = fline;
		}
	} else if (current[0] == "{") {
	
	} else if (current[0] == "}") {
	
	} else if (current[0] == "return") {
		line = code.size();	
	} else if (current[0] == "std::cout") {
	
	} else if (current[0] == "std::cin") {
	
	} else if (current[0] == "break"){
		
	} else {
		std::string varType = isDeclared(line, 0);
		if (varType == "NO") {	
			throw std::invalid_argument("Use of undeclared identifier " + std::to_string(line) + ".");
		}
		if (init.operations.find(current[1]) != init.operations.end()) {
			init.operations[current[1]](current, varType, variables);
		} else {
			throw std::invalid_argument("Unknown argument at line " + std::to_string(line) + "."); 
		}
	}
	return true;
}

void Parser::scopeParser(const char open, const char close, const size_t pos) const
{
	size_t countOfOpen{}, countOfClose{};
	for (const char current : data[pos]) {
		if ( current == open) {
			++countOfOpen;
		} else if (current == close) {
			++countOfClose;
		}
		if (countOfOpen < countOfClose) {
			throw std::invalid_argument("An inappropriate " + std::to_string(close) + " scope in line " + std::to_string(pos));
		}
	}
	if (countOfOpen != countOfClose) {
		throw std::invalid_argument("A " + std::to_string(open) + " scope in line " + std::to_string(pos) + "is not closed.");
	}
}
void Parser::commentParser(size_t pos)
{
	size_t position = data[pos].find("//");
	if (position != std::string::npos) {
		data[pos].erase(position, data[pos].length());
	}
}

void Parser::semicolonParser(const size_t pos) const
{
	std::string& line = data[pos];
	char end = line.back();
	if (end == ';' ||  end == '{' || end == '}' ) {
		return;
	}
	throw std::invalid_argument("An semicolon is missing in line " + std::to_string(pos) + ".");
}

void Parser::parsCurlyBraces()
{
	std::stack<char> braces;
	for (size_t i{}; i < data.size(); ++i) {
		for (const char c : data[i]) {
			if (c == '{') {
				braces.push('{');
			} else if ( c == '}') {
				if (braces.empty()) {
					throw std::invalid_argument("The } is excpected in line " + std::to_string(i) + ".");
				}
				braces.pop();
			}
		}
	}	
	if (!braces.empty()) {
			throw std::invalid_argument("Curly braces missconsamptin.");
	}
}

bool Parser::hasIostream()
{
	std::string& iostream = data[0];
	removeSpace(0);
	return data[0] == "#include<iostream>" ? true : false;
}
	
void Parser::processData()
{
	size_t i = hasIostream() ? 2 : 1;
	size_t j{};
	while (i < data.size() - 1) {
		std::istringstream lineStream(data[i]);
		std::string current;
			while (lineStream >> current) {
				//std::cout << "its ok before this line" << std::endl;
				code[j].push_back(current);
			}
		if (code[j].back().back() == ';') {
			code[j].back().pop_back();
			code[j].push_back(";");
		}
		// --num
		if (code[j].size() > 1 && code[j][0].starts_with("--")) {
			std::string name = code[j][0].substr(2);
			code[j].insert(code[j].begin(), name);
			code[j][1] = "--";
		}
		// num--
		if (code[j].size() > 1 && code[j][0].ends_with("--")) {
			std::string name = code[j][0].substr(0, (code[j][0].size() - 2));
			code[j].insert(code[j].begin(), name);
			code[j][1] = "--";
		}
		//--num
		if (code[j].size() > 1 && code[j][0].ends_with("++")) {
			std::string name = code[j][0].substr(0, (code[j][0].size() - 2));
			code[j].insert(code[j].begin(), name);
			code[j][1] = "++";
		}
		// ++num
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

void Parser::print()const
{
	std::cout << "____________CODE____________" << std::endl;
	for (size_t i{}; i < code.size(); ++i) {
		std::cout <<i <<": " ;
		for (auto& word : code[i]) {
			std::cout << word << " " ;
		}
		std::cout << std::endl;
	}
	std::cout << "_____________________________________\n______________Variagles__________________" << std::endl;
	
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
}
void Parser::checkSemicolon(const size_t line)const
{
	if (code[line][4] != ";") {
		throw std::invalid_argument("Unknown symbole " + code[line][4] + " in line " + std::to_string(line) + ".");}
}
std::string Parser::isDeclared(const size_t line, const size_t pos)
{
	const std::string& key = code[line][pos];
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
void Parser::checkRedefinition(const size_t line) const	
{
	if (code[line][0] == "bool") {
		if (variables.booleans.contains(code[line][1])) {
		throw std::invalid_argument("Redefinition in line " + std::to_string(line) + " .");
		}
	} else if (code[line][0] == "char") {
		if (variables.characters.contains(code[line][1])) {
			throw std::invalid_argument("Redefinition in line " + std::to_string(line) + " .");
		}
	} else if (code[line][0] == "int") {
		if (variables.integers.contains(code[line][1])) {
			throw std::invalid_argument("Redefinition in line " + std::to_string(line) + " .");
		}
	} else if (code[line][0] == "string") {
		if (variables.strings.contains(code[line][1])) {
			throw std::invalid_argument("Redefinition in line " + std::to_string(line) + " .");
		}
	}
	if (code[line][2] != "=") {
		throw std::invalid_argument("In line " + std::to_string(line) + " = is expected");
	}
}

#endif //PARSER_H
