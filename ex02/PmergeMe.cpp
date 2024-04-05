#include "PmergeMe.hpp"

void insertionSort(std::vector<int>& vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		int key = vec[i];
		size_t j = i;
		while (j > 0 && vec[j - 1] > key)
		{
			std::swap(vec[j], vec[j - 1]);
			j--;
		}
	}
}

void merge(std::vector<int>& vec, size_t left, size_t mid, size_t right)
{
	std::vector<int> temp;
	size_t i = left, j = mid + 1;
	while (i <= mid && j <= right)
	{
		if (vec[i] < vec[j])
			temp.push_back(vec[i++]);
		else
			temp.push_back(vec[j++]);
	}
	while (i <= mid) temp.push_back(vec[i++]);
	while (j <= right) temp.push_back(vec[j++]);
	for (size_t k = 0; k < temp.size(); ++k)
		vec[left + k] = temp[k];
}

void mergeSort(std::vector<int>& vec, size_t left, size_t right)
{
	if (left >= right) return;
	if (right - left <= INSERTION_THRESHOLD)
		insertionSort(vec);
	else
	{
		size_t mid = left + (right - left) / 2;
		mergeSort(vec, left, mid);
		mergeSort(vec, mid + 1, right);
		merge(vec, left, mid, right);
	}
}

void mergeSort(std::vector<int>& vec)
{
	mergeSort(vec, 0, vec.size() - 1);
}



void insertionSort(std::deque<int>& deq)
{
	for (size_t i = 1; i < deq.size(); i++)
	{
		int key = deq[i];
		size_t j = i;
		while (j > 0 && deq[j - 1] > key)
		{
			std::swap(deq[j], deq[j - 1]);
			j--;
		}
	}
}

void merge(std::deque<int>& deq, std::deque<int>::iterator left, \
			std::deque<int>::iterator mid, std::deque<int>::iterator right)
{
	(void)deq;
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

void mergeSort(std::deque<int>& deq, std::deque<int>::iterator left, \
				std::deque<int>::iterator right)
{
	size_t size = std::distance(left, right);
	if (size <= 1) return;
	if (size <= INSERTION_THRESHOLD)
		insertionSort(deq);
	else
	{
		std::deque<int>::iterator mid = left;
		std::advance(mid, size / 2);
		mergeSort(deq, left, mid);
		mergeSort(deq, mid, right);
		merge(deq, left, mid, right);
	}
}

void mergeSort(std::deque<int>& deq)
{
	mergeSort(deq, deq.begin(), deq.end());
}
