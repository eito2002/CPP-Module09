#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	RPN rpn;
	try {
		rpn.PushAndCalculateNumbers(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
