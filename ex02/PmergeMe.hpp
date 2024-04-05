#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <vector>
# include <deque>
# include <algorithm>
# include <iostream>
# include <sstream>

# define INSERTION_THRESHOLD 10

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

	bool checkSorted(const std::vector<int>& vec, const std::deque<int>& deq);
	void printResult(int argc, char* argv[]);
	void sort(int argc, char* argv[]);
	bool checkSorted();

	void insertionSortVector();
	void mergeVector(size_t left, size_t mid, size_t right);
	void mergeSortVector(size_t left, size_t right);
	void mergeSortVector(int argc, char* argv[]);

	void insertionSortDeque();
	void mergeDeque(std::deque<int>::iterator left, \
				std::deque<int>::iterator mid, std::deque<int>::iterator right);
	void mergeSortDeque(std::deque<int>::iterator left, std::deque<int>::iterator right);
	void mergeSortDeque(int argc, char* argv[]);
};

#endif
