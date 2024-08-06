#include "RPN.hpp"

const std::string RPN::OP = "+-/*";

RPN::RPN(const std::string &line) {
	pushNumbers(line);
}

RPN::~RPN() {}

void RPN::pushNumbers(std::string line) {
	std::stringstream iss(line);
	std::string       token;
	while (iss >> token) {
		if (token.length() >= 2) {
			std::cout << "Error" << std::endl;
			std::exit(EXIT_FAILURE);
		} else if (std::isdigit(token[0]))
			stack_.push(token);
		else if (std::strchr(RPN::OP.c_str(), token[0]) && stack_.size() >= 2)
			calculate(token);
	}
	if (stack_.size() == 1)
		std::cout << stack_.top() << std::endl;
	else {
		std::cout << "Error" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

int add(int a, int b) {
	return a + b;
}

int subtract(int a, int b) {
	return a - b;
}

int multiply(int a, int b) {
	return a * b;
}

int divide(int a, int b) {
	if (b == 0) {
		std::cout << "Error" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return a / b;
}

void RPN::calculate(const std::string &op) {
	int b = std::atoi(stack_.top().c_str());
	stack_.pop();
	int a = std::atoi(stack_.top().c_str());
	stack_.pop();
	typedef int (*FuncPtr)(int, int);
	FuncPtr funcs[] = {&add, &subtract, &divide, &multiply};
	for (int i = 0; i < 4; ++i) {
		if (op[0] == RPN::OP[i]) {
			std::stringstream ss;
			ss << (funcs[i])(a, b);
			stack_.push(ss.str());
		}
	}
}
