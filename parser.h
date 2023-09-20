#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdexcept>
#include <stack>

#include "loader.h"

struct Parser
{
	Parser(std::vector<std::string>&);
	bool hasMain(size_t);
	void scopeParser(const char, const char, const size_t) const;
	bool hasIostream();
	bool variabelParser(size_t) const;
	bool variableTypeParser(size_t) const;
	void commentParser(size_t);
	void semicolonParser(size_t) const;
	void parsCurlyBraces();
	void pars();
	
	//helper
	void removeSpace(size_t);
	void trimString(std::string&);
	std::vector<std::string>& data;
	// std::map<std::string, bool> flag

};

Parser::Parser(std::vector<std::string>& d) : data{d} {}

void Parser::pars()
{
	size_t i = hasIostream() ? 1 : 0;
	std::cout << data[i] << std::endl;
	hasMain(i);
	++i;	
	for ( ; i < data.size() - 1; ++i) {
		commentParser(i);
		trimString(data[i]);
		scopeParser('(', ')', i);
		scopeParser('[', ']', i);
		semicolonParser(i);
	}


}

bool Parser::hasMain(size_t mainLine)
{
	removeSpace(mainLine);
	std::cout << data[mainLine] << std::endl; 
	if (data[mainLine] != "intmain(){") {
		throw std::invalid_argument("The program does not have a main.");
	} else {
		removeSpace(data.size() - 1);
		if (data.back() != "}") {
			std::cout << data.back() << std::endl;	
			throw std::invalid_argument("The function main does not have a closing scope.");
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
	std::cout << line << " And the last symbol is " << end << "	" << (end == ';') << std::endl;
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
				if (braces.size() > 1) {
					throw std::invalid_input("The } is excpected in line " + std::to_string(i) + ".");
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


void Parser::trimString(std::string& str) {
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
	std::cout << data[pos] << std::endl;
}
#endif //PARSER_H
