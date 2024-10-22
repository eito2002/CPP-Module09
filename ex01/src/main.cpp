#include "RPN.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		RPN::PushAndCalculateNumbers(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
