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
		std::cout << "Error: not sorted";
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

void PmergeMe::mergeVector(size_t left, size_t mid, size_t right)
{
	std::vector<int> temp;
	size_t i = left, j = mid + 1;
	while (i <= mid && j <= right)
	{
		if (vector_[i] < vector_[j])
			temp.push_back(vector_[i++]);
		else
			temp.push_back(vector_[j++]);
	}
	while (i <= mid) temp.push_back(vector_[i++]);
	while (j <= right) temp.push_back(vector_[j++]);
	for (size_t k = 0; k < temp.size(); ++k)
		vector_[left + k] = temp[k];
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
		mergeVector(left, mid, right);
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

void PmergeMe::mergeDeque(std::deque<int>::iterator left, \
			std::deque<int>::iterator mid, std::deque<int>::iterator right)
{
	(void)deque_;
	std::deque<int> temp;
	std::deque<int>::iterator i = left, j = mid;
	while (i != mid && j != right)
	{
		if (*i < *j)
			temp.push_back(*(i++));
		else
			temp.push_back(*(j++));
	}
	while (i != mid) temp.push_back(*(i++));
	while (j != right) temp.push_back(*(j++));
	std::copy(temp.begin(), temp.end(), left);
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
		std::advance(mid, size / 2);
		mergeSortDeque(left, mid);
		mergeSortDeque(mid, right);
		mergeDeque(left, mid, right);
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
