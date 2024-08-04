#include "BitcoinExchange.hpp"
#include <fstream>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string filename = argv[2];
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	std::string line;
	BitcoinExchange bit(argv[1]);
	std::getline(file, line);
	while (std::getline(file, line))
		if (line != "")
			bit.calculateLine(line);
	file.close();
	return 0;
}
