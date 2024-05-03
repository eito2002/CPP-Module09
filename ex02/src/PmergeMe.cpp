#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::printResult(int argc, char* argv[])
{
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;
	mergeSortVector(argc, argv);
	mergeSortDeque(argc, argv);
	if (checkSorted())
	{
		std::cout << "After:  ";
		for (std::vector<int>::iterator it = vector_.begin(); it != vector_.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Time to process a range of " << vector_.size() << " elements with std::vector : " << \
					durationVec_ << " milli seconds" << std::endl;
		std::cout << "Time to process a range of " << deque_.size() << " elements with std::deque : " << \
					durationDeq_ << " milli seconds" << std::endl;
	}
	else
		std::cout << "Error: not sorted" << std::endl;
}

bool PmergeMe::checkSorted()
{
	if (vector_.size() != deque_.size())
		return false;
	for (size_t i = 0; i < vector_.size(); i++)
		if (vector_[i] != deque_[i])
			return false;
	return true;
}

void PmergeMe::insertionSortVector()
{
	for (size_t i = 1; i < vector_.size(); i++)
	{
		int key = vector_[i];
		size_t j = i;
		while (j > 0 && vector_[j - 1] > key)
		{
			std::swap(vector_[j], vector_[j - 1]);
			j--;
		}
	}
}

void PmergeMe::mergeSortVector(size_t left, size_t right)
{
	if (left >= right) return;
	if (right - left <= INSERTION_THRESHOLD)
		insertionSortVector();
	else
	{
		size_t mid = left + (right - left) / 2;
		mergeSortVector(left, mid);
		mergeSortVector(mid + 1, right);
	}
}

void PmergeMe::mergeSortVector(int argc, char* argv[])
{
	this->startTimeVec_ = clock();
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss(argv[i]);
		int num;
		while (ss >> num)
			vector_.push_back(num);
	}
	mergeSortVector(0, this->vector_.size() - 1);
	this->durationVec_ = (double)(clock() - startTimeVec_);
}

void PmergeMe::insertionSortDeque()
{
	for (size_t i = 1; i < deque_.size(); i++)
	{
		int key = deque_[i];
		size_t j = i;
		while (j > 0 && deque_[j - 1] > key)
		{
			std::swap(deque_[j], deque_[j - 1]);
			j--;
		}
	}
}

void PmergeMe::mergeSortDeque(std::deque<int>::iterator left, \
									std::deque<int>::iterator right)
{
	size_t size = std::distance(left, right);
	if (size <= 1) return;
	if (size <= INSERTION_THRESHOLD)
		insertionSortDeque();
	else
	{
		std::deque<int>::iterator mid = left;
		for (size_t i = 0; i < size / 2; i++)
			mid++;
		mergeSortDeque(left, mid);
		mergeSortDeque(mid, right);
	}
}

void PmergeMe::mergeSortDeque(int argc, char* argv[])
{
	this->startTimeDeq_ = clock();
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss(argv[i]);
		int num;
		while (ss >> num)
			deque_.push_back(num);
	}
	mergeSortDeque(deque_.begin(), deque_.end());
	this->durationDeq_ = (double)(clock() - startTimeDeq_);
}
