#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		if (std::atoi(argv[i]) <= 0 || !std::strcmp(argv[i], "")) {
			std::cout << "Error" << std::endl;
			return 1;
		}
		for (int j = 0; argv[i][j]; j++) {
			if (!std::isdigit(argv[i][j])) {
				std::cout << "Error" << std::endl;
				return 1;
			}
		}
	}
	std::list<int> list;
	for (int i = 1; i < argc; i++) {
		list.push_back(std::atoi(argv[i]));
	}
	std::list<int> sorted_list = PmergeMe::MergeInsertionSortList(list);
	for (std::list<int>::iterator it = sorted_list.begin(); it != sorted_list.end(); ++it) {
		std::cout << *it;
		if (++std::list<int>::iterator(it) != sorted_list.end())
			std::cout << ", ";
	}

    std::vector<int> vec;
    for (int i = 1; i < argc; i++) {
        vec.push_back(std::atoi(argv[i]));
    }
    std::cout << std::endl << std::endl;
    std::vector<int> sorted_vec = PmergeMe::MergeInsertionSortVector(vec);
    for (std::vector<int>::iterator it = sorted_vec.begin(); it != sorted_vec.end(); ++it) {
        std::cout << *it;
        if (++std::vector<int>::iterator(it) != sorted_vec.end())
            std::cout << ", ";
    }
	return 0;
}
