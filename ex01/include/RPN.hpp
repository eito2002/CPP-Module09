#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class RPN {
  private:
	std::stack<int> stack_;
	DISALLOW_COPY_AND_ASSIGN(RPN);
	void Calculate(const std::string &);

  public:
	static const std::string OP;
	RPN();
	~RPN();
	void PushAndCalculateNumbers(const std::string &);
};

#endif
