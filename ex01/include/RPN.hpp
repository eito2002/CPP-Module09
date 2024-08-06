#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>

class RPN {
  private:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);

	std::stack<std::string> stack_;

  public:
	RPN(const std::string &);
	~RPN();
	// int add(int a, int b);
	// int subtract(int a, int b);
	// int multiply(int a, int b);
	// int divide(int a, int b);

	void pushNumbers(std::string line);
	void calculate(const std::string &op);

	static const std::string OP;
};

#endif
