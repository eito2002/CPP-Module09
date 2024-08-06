#include "RPN.hpp"
#include <iostream>
#include <sstream>

const std::string RPN::OP = "+-/*";

RPN::RPN() {}

RPN::~RPN() {}

void RPN::PushAndCalculateNumbers(const std::string &line) {
	std::stringstream iss(line);
	std::string       token;

	stack_ = std::stack<int>();
	while (iss >> token) {
		if (token.length() >= 2) {
			throw std::runtime_error("Error");
		} else if (std::isdigit(token[0])) {
			stack_.push(std::atoi(token.c_str()));
		} else if (OP.find(token[0]) != std::string::npos && stack_.size() >= 2)
			Calculate(token);
	}
	if (stack_.size() == 1)
		std::cout << stack_.top() << std::endl;
	else {
		throw std::runtime_error("Error");
	}
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
		throw std::runtime_error("Error");
	}
	return a / b;
}

static void CheckOverFlow(int a, int b, char op) {
	switch (op) {
	case '+':
		if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
			(b < 0 && a < std::numeric_limits<int>::min() - b))
			throw std::overflow_error("Error");
		break;
	case '-':
		if ((b < 0 && a > std::numeric_limits<int>::max() + b) ||
			(b > 0 && a < std::numeric_limits<int>::min() + b))
			throw std::overflow_error("Error");
		break;
	case '*':
		if ((a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) ||
			(a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) ||
			(a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b) ||
			(a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b))
			throw std::overflow_error("Error");
		break;
	case '/':
		if (a == std::numeric_limits<int>::min() && b == -1)
			throw std::overflow_error("Error");
		break;
	default:
		break;
	}
}

void RPN::Calculate(const std::string &op) {
	int b = stack_.top();
	stack_.pop();
	int a = stack_.top();
	stack_.pop();
	typedef int (*FuncPtr)(int, int);
	FuncPtr funcs[] = {&Add, &Subtract, &Divide, &Multiply};
	for (int i = 0; i < 4; ++i) {
		if (op[0] == OP[i]) {
			CheckOverFlow(a, b, op[0]);
			stack_.push((funcs[i])(a, b));
		}
	}
}
