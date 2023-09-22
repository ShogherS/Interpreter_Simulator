#ifndef INIT_H
#define INIT_H

#include <map>
#include <string>
#include <functional>

#include "variables.h"

struct Init
{
	Init(Varaiables& v) : vars{v} {}
	
	std::map<std::string, std::functional<void(std::vector<std::string>&)>> operations {
		 {"=", [](std::vector<std::string>& line, std::string type) {
				size_t i = 2;
				if (type == "bool") {
					bool& value = variables.booleans[0].first;
					if (line[i] == "true") {
						value = true;
					} else if ( line[i] == "false") {
						value == false;
					} else if (variables.booleans.find(line[i]) != variables.booleans.end()) {
						value = variables.booleans.[line[i]].first;
					} else {
						  throw std::invalid_argument("Invalid argument \"" + line[i] + "\".");    
					}                                             
					++i;
					if (line[i] !== ";") {
						throw std::invalid_argument("Unknown symbole \"" + line[i]+ "\".");                         
					}
				} else if (type == "int") {
				
				} else if (type == "char") {
				
				} else if (type == "string") {
				
				}

		}  }
	/*
	{"+=", },
	{"-=", },
	{"++", },
	{"--", },
	{"==", },
	{"<", },
	{}
	*/
	};
	Variables& vars;
};
#endif //INIT_H
