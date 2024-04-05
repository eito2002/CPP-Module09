#include "RPN.hpp"

std::stack<std::string> RPN::stack_;
const std::string RPN::OP = "+-/*";

void RPN::pushNumbers(std::string line)
{
	std::stringstream iss(line);
	std::string token;
	while (iss >> token)
	{
		if (token.length() >= 2)
		{
			std::cout << "Error" << std::endl;
			return;
		}
		else if (std::isdigit(token[0]))
			stack_.push(token);
		else if (std::strchr(RPN::OP.c_str(), token[0]) && stack_.size() >= 2)
			calculate(token);
	}
	if (stack_.size() == 1)
		std::cout << stack_.top() << std::endl;
	else
		std::cout << "Error" << std::endl;
}

int RPN::add(int a, int b)
{
	return a + b;
}

int RPN::subtract(int a, int b)
{
	return a - b;
}

int RPN::multiply(int a, int b)
{
	return a * b;
}

int RPN::devide(int a, int b)
{
	if (b == 0)
	{
		std::cout << "Error" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return a / b;
}

void RPN::calculate(const std::string& op)
{
	int b = std::atoi(stack_.top().c_str());
	stack_.pop();
	int a = std::atoi(stack_.top().c_str());
	stack_.pop();
	typedef int (*FuncPtr)(int, int);
	FuncPtr funcs[] = {&RPN::add, &RPN::subtract, &RPN::devide, &RPN::multiply};
	for (int i = 0; i < 4; i++)
	{
		if (op[0] == RPN::OP[i])
		{
			std::stringstream ss;
			ss << (funcs[i])(a, b);
			stack_.push(ss.str());
		}
	}
}
