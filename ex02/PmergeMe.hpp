#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <vector>
# include <deque>
# include <algorithm>

# define INSERTION_THRESHOLD 0

void insertionSort(std::vector<int>& vec);
void merge(std::vector<int>& vec, size_t left, size_t mid, size_t right);
void mergeSort(std::vector<int>& vec, size_t left, size_t right);
void mergeSort(std::vector<int>& vec);

void insertionSort(std::deque<int>& deq);
void merge(std::deque<int>& deq, std::deque<int>::iterator left, \
			std::deque<int>::iterator mid, std::deque<int>::iterator right);
void mergeSort(std::deque<int>& deq, std::deque<int>::iterator left, \
				std::deque<int>::iterator right);
void mergeSort(std::deque<int>& deq);
#endif
