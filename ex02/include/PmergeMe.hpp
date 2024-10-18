#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <list>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class PmergeMe {
  private:
	PmergeMe();
	DISALLOW_COPY_AND_ASSIGN(PmergeMe);
	~PmergeMe();
	static bool checkSorted();

  public:
	static void printResult(int argc, char *argv[]);

	static std::list<int> MergeInsertionSortList(std::list<int> &list);
};

#endif
