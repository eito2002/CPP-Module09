#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <vector>
# include <list>
# include <algorithm>
# include <iostream>
# include <sstream>
# include <ctime>

class PmergeMe
{
private:
	std::vector<int> vector_;
	std::list<int> list_;
	clock_t startTimeVec_;
	clock_t startTimeLis_;
	double durationVec_;
	double durationLis_;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void printResult(int argc, char* argv[]);
	bool checkSorted();

	void insertionSortVector();
	void mergeSortVector(size_t left, size_t right);
	void mergeSortVector(int argc, char* argv[]);

	void insertionSortList();
	void mergeSortList(std::list<int>::iterator left, std::list<int>::iterator right);
	void mergeSortList(int argc, char* argv[]);

	static const int INSERTION_THRESHOLD = 10;
};

#endif
