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
	mergeSortList(argc, argv);
	if (checkSorted())
	{
		std::cout << "After:  ";
		for (std::vector<int>::iterator it = vector_.begin(); it != vector_.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Time to process a range of " << vector_.size() << " elements with std::vector : " << \
					durationVec_ << " micro seconds" << std::endl;
		std::cout << "Time to process a range of " << list_.size() << " elemens with std::list : " << \
					durationLis_ << " micro seconds" << std::endl;
	}
	else
		std::cout << "Error: not sorted" << std::endl;
}

bool PmergeMe::checkSorted()
{
	if (vector_.size() != list_.size())
		return false;
	std::list<int>::iterator it = list_.begin();
	for (size_t i = 0; i < vector_.size(); i++, it++)
		if (vector_[i] != *it)
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
	this->durationVec_ = (double)(clock() - startTimeVec_) * 1000000 / CLOCKS_PER_SEC;
}

void PmergeMe::insertionSortList()
{
	for (std::list<int>::iterator it = ++list_.begin(); it != list_.end(); it++)
	{
		int key = *it;
		std::list<int>::iterator jt = it;
		std::list<int>::iterator prev_jt = jt;
		--prev_jt;
		while (jt != list_.begin() && *prev_jt > key)
		{
			std::swap(*jt, *prev_jt);
			jt--;
			prev_jt--;
		}
	}
}

void PmergeMe::mergeSortList(std::list<int>::iterator left, \
									std::list<int>::iterator right)
{
	size_t size = std::distance(left, right);
	if (size <= 1) return;
	if (size <= INSERTION_THRESHOLD)
		insertionSortList();
	else
	{
		std::list<int>::iterator mid = left;
		for (size_t i = 0; i < size / 2; i++)
			mid++;
		mergeSortList(left, mid);
		mergeSortList(mid, right);
	}
}

void PmergeMe::mergeSortList(int argc, char* argv[])
{
	this->startTimeLis_ = clock();
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss(argv[i]);
		int num;
		while (ss >> num)
			list_.push_back(num);
	}
	mergeSortList(list_.begin(), list_.end());
	this->durationLis_ = (double)(clock() - startTimeLis_) * 1000000 / CLOCKS_PER_SEC;
}
