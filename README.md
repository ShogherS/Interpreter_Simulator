# Interpreter_Simulator
Interpretation Simulation Program

## Overview

This Interpretation Simulation Program is designed to simulate and interpret code written in a c++ language. It includes functions for parsing, executing, and simulating code, making it a powerful tool for understanding code behavior.

## Introduction

The Interpreter Simulate Program is a C++ educational project designed to load and parse code from a text file, simulating an interpreter's step-by-step execution. This README provides detailed information on the program's functions and how to use it effectively.

## Features

The Interpreter Simulate Program offers the following features:

Code Loading: The program can load code from a text file, allowing you to analyze and simulate its execution.

Step-by-Step Parsing: It parses the loaded code step by step, simulating an interpreter's execution, and checks for errors and issues during the process.

Variable Declaration: The program detects and handles variable declarations for various data types, including bool, int, char, string, ans arrays of char and int.

Operations: It supports various operations like =, +=, and -= for different data types.

Array Support: The program can handle array declarations and operations, including element access and assignments.

Conditional Statements: It can process conditional statements like if and while, simulating their execution based on given conditions.

Output: The program can simulate basic output operations, including std::cout.

Error Handling: It provides detailed error messages and validation checks for various aspects of the code, helping users identify and correct issues.


## Usage
How to Use
To run the Interpreter Simulate Program, you need:

1. The program rads the code from the text file. Here is the exsample of the code that the program can excecute:

```
int main() {
	int i = 0;
	int j = 5;
	int arr[5] = {1,2,3,4,5,12,45,56};
	if (i < j) {
		if (i == 3) {
			break;
		}
		std::cout << arr[i] << std::endl;
		++i; // i += 1
	}
	return 0;
}
```

2. The next step is to download all files of the current repositry to your computer. Clone or download the program's source code to your local machine.
   * loader.h
     
   * parser.h
     
   * parser.cpp
     
   * init.h
     
   * variables.h

3. The next step is to crete a .cpp file and include loader.h and parser.cpp files. Open a terminal or command prompt and navigate to the directory containing the program's source code. Aftervards you need to creale an instance of Loader class, it has a constructor with a string as a parameter. Its main role is to load the text file that with the code and sawe it. Next the Parser clss steps in, it also has a constructor with a parameter and a method pars which compiles the ocde. And at last you can chek the status of all the delatred vairables in your code calling the print method.

```
#include "loader.h"
#include "parser.cpp
int main()
{
	Loader loader("code.txt");
	Parser parser(loader.code);
	parser.pars();
}
```
4. Compile the program using your C++ compiler.

5. Run the program, providing the name of the text file containing your code as a command-line argument. Once the program is running, it will load and parse the code step by step, simulating the execution. You will see output and error messages in the terminal, helping you understand how the code is being processed.



## Structure

*Loader struct
*Variagles struct
*Init struct
*Parser struct
*Loader struct

### Loader Class

The Loader struct is responsible for loading code from a file into the program. It includes the following components:

cpp
```
struct Loader
{
	std::vector<std::string> code;
	// Vector to store lines of code from a file.
	Loader(const std::string& filename);
	// Constructor that loads code from a file into the 'code' vector.
};
```

Constructor Definition
The Loader struct defines a constructor that loads code from a specified file into the code vector. Here's how it works:

The constructor opens the file specified by filename for reading using std::ifstream.
It checks if the file was successfully opened and throws a std::runtime_error if the opening fails.
The constructor uses a temporary variable line to read each line of the file.
It reads each line from the file and stores it in the code vector, ignoring empty lines.
Finally, the constructor closes the file when done reading.
This Loader struct is used to initialize the code vector with the content of the code file, which is then processed by the Parser class for step-by-step execution.
Interpreting Error Messages
If the program encounters errors in the code, it will provide detailed error messages, including the line number and the nature of the error. Use these messages to identify and fix issues in your code.

## Customizing the Program
You can customize the program's behavior by modifying the code in the Parser class and the associated lambdas that handle various operations. Be sure to follow the program's code structure and comments for guidance.

## Conclusion

The Interpreter Simulate Program is a valuable educational tool for understanding how code is executed step by step. By loading your code and using this program, you can gain insights into the inner workings of an interpreter and learn to identify and correct errors in your programs.
