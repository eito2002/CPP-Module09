#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}

	try {
		RPN(std::string(argv[1]));
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
	return 0;
}
