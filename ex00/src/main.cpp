#include "BitcoinExchange.hpp"
#include <fstream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string   filename = argv[1];
	std::ifstream file(filename.c_str());
	if (!file) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string     line;
	BitcoinExchange bit("cpp_09/data.csv");
	std::getline(file, line);
	while (std::getline(file, line))
		if (line != "")
			bit.CalculateLine(line);
	file.close();
	return 0;
}
