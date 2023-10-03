#include "loader.h"
#include "parser.cpp"

int main()
{
	Loader loader("code4.txt");
//	Loader loader("code3.txt");
//	Loader loader("code2.txt");
//	Loader loader("code1.txt");
//	Loader loader("code.txt");
	Parser parser(loader.code);
	parser.pars();
}
