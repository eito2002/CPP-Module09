#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class RPN {
  private:
	DISALLOW_COPY_AND_ASSIGN(RPN);
	void                    Calculate(const std::string &);
	std::stack<std::string> stack_;

  public:
	RPN();
	~RPN();
	void                     PushAndCalculateNumbers(const std::string &);
	static const std::string OP;
};

#endif
