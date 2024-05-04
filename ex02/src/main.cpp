#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		if (std::atoi(argv[i]) <= 0 || !std::strcmp(argv[i], ""))
		{
			std::cout << "Error" << std::endl;
			return 1;
		}
		for (int j = 0; argv[i][j]; j++)
		{
			if (!std::isdigit(argv[i][j]))
			{
				std::cout << "Error" << std::endl;
				return 1;
			}
		}
	}
	PmergeMe p;
	p.printResult(argc, argv);
	return 0;
}
