#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>


struct Loader
{
	std::vector<std::string> code;
	Loader(const std::string&);
};

Loader::Loader(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open the file.");
	}
	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			code.push_back(line);
		}
	} 
	file.close();
}

#endif	//LOADER_H
