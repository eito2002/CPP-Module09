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
	~RPN();
	static void              Calculate(const std::string &, std::stack<int> &);
	static const std::string OP;

  public:
	static void PushAndCalculateNumbers(const std::string &);
};

#endif
