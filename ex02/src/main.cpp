#include "PmergeMe.hpp"
#include <cstdlib> // EXIT_*, std::atoi
#include <cstring> // std::strcmp
#include <iostream>

namespace {

typedef std::vector<int> IntVector;
typedef std::list<int>   IntList;

bool CheckArgsIsError(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return true;
	}
	for (int i = 1; i < argc; i++) {
		if (std::atoi(argv[i]) <= 0 || !std::strcmp(argv[i], "")) {
			std::cerr << "Error" << std::endl;
			return true;
		}
		for (int j = 0; argv[i][j]; j++) {
			if (!std::isdigit(argv[i][j])) {
				std::cerr << "Error" << std::endl;
				return true;
			}
		}
	}
	return false;
}

bool IsSorted(const IntVector &vector, const IntList &list) {
	if (vector.size() != list.size()) {
		return false;
	}
	IntList::const_iterator it = list.begin();
	for (size_t i = 0; i < vector.size(); i++, it++) {
		if (vector[i] != *it) {
			return false;
		}
	}
	return true;
}

IntVector ConvertToIntVector(char *argv[], int argc) {
	IntVector vector;
	for (int i = 1; i < argc; i++) {
		vector.push_back(std::atoi(argv[i]));
	}
	return vector;
}

IntList ConvertToIntList(char *argv[], int argc) {
	IntList list;
	for (int i = 1; i < argc; i++) {
		list.push_back(std::atoi(argv[i]));
	}
	return list;
}

void PrintBefore(int argc, char *argv[]) {
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;
}

void PrintResult(
	const IntVector &sorted_vector,
	const IntList   &sorted_list,
	double           duration_vec,
	double           duration_list
) {
	if (IsSorted(sorted_vector, sorted_list)) {
		std::cout << "After:  ";
		for (IntVector::const_iterator it = sorted_vector.begin(); it != sorted_vector.end();
			 it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Time to process a range of " << sorted_vector.size()
				  << " elements with std::vector: " << duration_vec << " micro seconds "
				  << std::endl;
		std::cout << "Time to process a range of " << sorted_list.size()
				  << " elements with std::list: " << duration_list << " micro seconds" << std::endl;
	} else {
		std::cerr << "Error: not sorted" << std::endl;
	}
}

void SortAndPrintResult(int argc, char *argv[]) {
	PrintBefore(argc, argv);

	IntVector vector = ConvertToIntVector(argv, argc);
	IntList   list   = ConvertToIntList(argv, argc);

	clock_t         start_vec     = clock();
	const IntVector sorted_vector = PmergeMe::MergeInsertionSortVector(vector);
	clock_t         end_vec       = clock();
	double duration_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000;

	clock_t       start_list  = clock();
	const IntList sorted_list = PmergeMe::MergeInsertionSortList(list);
	clock_t       end_list    = clock();
	double duration_list = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC * 1000000;

	PrintResult(sorted_vector, sorted_list, duration_vec, duration_list);
}

} // namespace

int main(int argc, char *argv[]) {
	if (CheckArgsIsError(argc, argv)) {
		return EXIT_FAILURE;
	}

	SortAndPrintResult(argc, argv);
	return EXIT_SUCCESS;
}
