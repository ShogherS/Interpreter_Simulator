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
	std::map<std::string, std::vector<bool>> boolArr;
	std::map<std::string, std::vector<char>> charArr;
	std::map<std::string, std::vector<int>> intArr;
	std::map<std::string, std::vector<std::string>> stringArr;
	
};

/*
struct VariableTypes{
	std::map<std::string,
*/	

#endif //VARIABLES_H
