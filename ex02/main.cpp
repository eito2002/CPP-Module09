#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	// if (argc <= 1)
	// {
	// 	std::cerr << "Usage: " << argv[0] << " <space-separated integers>" << std::endl;
	// 	return 1;
	// }

	std::vector<int> vector_;
	std::deque<int> deque_;
	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss(argv[i]);
		int num;
		while (ss >> num)
		{
			vector_.push_back(num);
			deque_.push_back(num);
		}
	}
	for (std::vector<int>::iterator it = vector_.begin(); it != vector_.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (std::deque<int>::iterator it = deque_.begin(); it != deque_.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	mergeSort(vector_);
	mergeSort(deque_);
	for (std::vector<int>::iterator it = vector_.begin(); it != vector_.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (std::deque<int>::iterator it = deque_.begin(); it != deque_.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	return 0;
}
