#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class RPN {
  private:
	RPN();
	DISALLOW_COPY_AND_ASSIGN(RPN);
	std::stack<std::string> stack_;

  public:
	RPN(const std::string &);
	~RPN();
	void pushNumbers(const std::string &);
	void calculate(const std::string &);

	static const std::string OP;
};

#endif
