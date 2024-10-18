#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <list>
#include <vector>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class PmergeMe {
  private:
	PmergeMe();
	DISALLOW_COPY_AND_ASSIGN(PmergeMe);
	~PmergeMe();

  public:
	static std::list<int>   MergeInsertionSortList(std::list<int> &list);
	static std::vector<int> MergeInsertionSortVector(std::vector<int> &vec);
};

#endif
