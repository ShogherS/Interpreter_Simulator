#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
struct Loader
{
    std::vector<std::string> code; // Vector to store lines of code from a file.

    // Constructor that loads code from a file into the 'code' vector.
    Loader(const std::string& filename);
};

// Constructor definition
Loader::Loader(const std::string& filename)
{
    // Open the file specified by 'filename' for reading.
    std::ifstream file(filename);

    // Check if the file was successfully opened.
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file.");
    }

    std::string line; // Temporary variable to store each line of the file.

    // Read each line from the file and store it in the 'code' vector.
    while (std::getline(file, line)) {
        if (!line.empty()) { // Check if the line is not empty.
            code.push_back(line); // Add the non-empty line to the 'code' vector.
        }
    }

    file.close(); // Close the file when done reading.
}

#endif	//LOADER_H
