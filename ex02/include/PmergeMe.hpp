#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <vector>
# include <deque>
# include <algorithm>
# include <iostream>
# include <sstream>
# include <ctime>

class PmergeMe
{
private:
	std::vector<int> vector_;
	std::deque<int> deque_;
	clock_t startTimeVec_;
	clock_t startTimeDeq_;
	double durationVec_;
	double durationDeq_;

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

	void insertionSortDeque();
	void mergeSortDeque(std::deque<int>::iterator left, std::deque<int>::iterator right);
	void mergeSortDeque(int argc, char* argv[]);

	static const int INSERTION_THRESHOLD = 10;
};

#endif
