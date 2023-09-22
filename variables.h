#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <map>
#include <utility>

struct Variables
{	//		name		value 	type
	std::map<std::string, std::pair<bool, std::string>> booleans;
	std::map<std::string, std::pair<char, std::string>> characters;
	std::map<std::string, std::pair<int, std::string>> integers;
	std::map<std::string, std::pair<std::string, std::string>> strings;
};

/*
struct VariableTypes{
	std::map<std::string,
*/	

#endif //VARIABLES_H
