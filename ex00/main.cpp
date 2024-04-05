#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string filename = argv[1];
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string line;
	BitcoinExchange bit;
	std::getline(file, line);
	while (std::getline(file, line))
		if (line != "")
			bit.calculateLine(line);
	file.close();
	return 0;
}
