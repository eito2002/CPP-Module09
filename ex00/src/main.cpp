#include "BitcoinExchange.hpp"
#include <cstdlib> // EXIT_*
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return EXIT_FAILURE;
	}

	std::string   filename = argv[1];
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return EXIT_FAILURE;
	}

	std::string     line;
	BitcoinExchange bit("cpp_09/data.csv");
	std::getline(file, line); // skip the first line
	while (std::getline(file, line)) {
		if (!line.empty()) {
			bit.CalculateLine(line);
		}
	}
	file.close();
	return EXIT_SUCCESS;
}
