#include "loader.h"
#include "parser.cpp"

int main()
{
	std::string fileName;
	std::cout << "Enter the name if the file with the code" << std::endl;
	std::getline(std::cin, fileName);
	Loader loader(fileName);
	Parser parser(loader.code);
	parser.pars();
}
