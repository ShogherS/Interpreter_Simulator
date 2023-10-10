// Member function 'print' definition
void Parser::print()const
{
	std::cout << "\n____________CODE____________" << std::endl;
	for (size_t i{}; i < code.size(); ++i) {
		std::cout <<i <<": " ;
		for (auto& word : code[i]) {
			std::cout << word << " " ;
		}
		std::cout << std::endl;
	}
	std::cout << "_____________________________________\n______________Variables__________________" << std::endl;
	
	for (auto& item : variables.booleans) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.integers) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.characters) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.doubles) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}for (auto& item : variables.strings) {
		std::cout << "Variable name: " << item.first << " value: " << item.second.first << " type: " << item.second.second << std::endl; 
	}
	for (auto& item : variables.charArr) {
		std::cout << "Char array: " << item.first << ": " ;
		for (const auto c : item.second) {
			std::cout << c << ' ';
		}
		std::cout << std::endl;
	} 
	for (auto& item : variables.intArr) {
		std::cout << "Int array: " << item.first << ": ";
		for (int i : item.second) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
	for (auto& item : variables.doubleArr) {
		std::cout << "Double array: " << item.first << ": ";
		for (double i : item.second) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
}

