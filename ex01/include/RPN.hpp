#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <sstream>
# include <iostream>

class RPN
{
private:
	static std::stack<std::string> stack_;
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

public:
	static int add(int a, int b);
	static int subtract(int a, int b);
	static int multiply(int a, int b);
	static int devide(int a, int b);

	static void pushNumbers(std::string line);
	static void calculate(const std::string& op);

	static const std::string OP;
};

#endif
