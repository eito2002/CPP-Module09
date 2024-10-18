#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <algorithm>
#include <ctime>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class PmergeMe {
  private:
	std::vector<int> vector_;
	std::list<int>   list_;
	clock_t          startTimeVec_;
	clock_t          startTimeLis_;
	double           durationVec_;
	double           durationLis_;

	PmergeMe();
	DISALLOW_COPY_AND_ASSIGN(PmergeMe);
	~PmergeMe();
	static bool checkSorted();

  public:
	static void printResult(int argc, char *argv[]);

	static std::list<int> MergeInsertionSortList(std::list<int> &list);
};

#endif
