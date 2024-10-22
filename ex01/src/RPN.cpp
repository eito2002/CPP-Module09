#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

const std::string RPN::OP = "+-/*";

RPN::RPN() {}

RPN::~RPN() {}

void RPN::PushAndCalculateNumbers(const std::string &line) {
	std::stack<int>   stack;
	std::stringstream iss(line);
	std::string       token;

	while (iss >> token) {
		if (token.length() >= 2) {
			throw std::runtime_error("Error: Invalid token length");
		} else if (std::isdigit(token[0])) {
			stack.push(std::atoi(token.c_str()));
		} else if (OP.find(token[0]) != std::string::npos) {
			if (stack.size() < 2) {
				throw std::runtime_error("Error: Not enough operands for operation");
			}
			Calculate(token, stack);
		} else {
			throw std::runtime_error("Error: Invalid token");
		}
	}
	if (stack.size() != 1) {
		throw std::runtime_error("Error: Invalid RPN expression");
	}
	std::cout << stack.top() << std::endl;
}

static int Add(int a, int b) {
	return a + b;
}

static int Subtract(int a, int b) {
	return a - b;
}

static int Multiply(int a, int b) {
	return a * b;
}

static int Divide(int a, int b) {
	if (b == 0) {
		throw std::runtime_error("Error: Division by zero");
	}
	return a / b;
}

static void CheckOverFlow(int a, int b, char op) {
	switch (op) {
	case '+':
		if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
			(b < 0 && a < std::numeric_limits<int>::min() - b)) {
			throw std::overflow_error("Error: Overflow");
		}
		break;
	case '-':
		if ((b < 0 && a > std::numeric_limits<int>::max() + b) ||
			(b > 0 && a < std::numeric_limits<int>::min() + b)) {
			throw std::overflow_error("Error: Overflow");
		}
		break;
	case '*':
		if ((a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) ||
			(a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) ||
			(a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) ||
			(a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b)) {
			throw std::overflow_error("Error: Overflow");
		}
		break;
	case '/':
		if (a == std::numeric_limits<int>::min() && b == -1) {
			throw std::overflow_error("Error: Overflow");
		}
		break;
	default:
		break;
	}
}

void RPN::Calculate(const std::string &op, std::stack<int> &stack) {
	int b = stack.top();
	stack.pop();
	int a = stack.top();
	stack.pop();
	typedef int (*FuncPtr)(int, int);
	FuncPtr funcs[] = {&Add, &Subtract, &Divide, &Multiply};
	for (int i = 0; i < 4; ++i) {
		if (op[0] == OP[i]) {
			CheckOverFlow(a, b, op[0]);
			stack.push((funcs[i])(a, b));
		}
	}
}
