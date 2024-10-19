#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <list>
#include <vector>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

/**
 * @brief Merge Insertion Sort Vector and List
 *
 * @details This class provides methods to perform merge-insertion sort on both
 * vectors and lists. The merge-insertion sort is a hybrid sorting algorithm that
 * combines the merge sort and insertion sort algorithms. In the situations
 * where the cost-of-comparison greatly outweighs the cost-of-overhead of the algorithm,
 * Merge Insertion Sort can be useful because it minimizes the number of comparisons.
 *
 * Merge Insertion Sort is a comparison sort that minimizes the worst-case number
 * of comparisons for small N. It has been proven optimal for N < 18, and likely
 * optimal for N < 47. Although it has a better worst-case for small N than most
 * other algorithms, its implementation results in worse performance on actual
 * computers than simpler algorithms like quicksort, timsort, and merge sort.
 *
 * The algorithm works as follows:
 * 1. Given an unsorted list, group the list into pairs. If the list is odd, the
 *    last element is unpaired.
 * 2. Each pair is sorted (using a single comparison each) into what we will call
 *    [a b] pairs.
 * 3. The pairs are sorted recursively based on the `a` of each, and we call the
 *    pairs [a1 b1], [a2 b2], etc. If the list was odd, the unpaired element is
 *    considered the last `b`.
 * 4. We call the chain of `a`s the "main-chain".
 * 5. The `b`s are then inserted into the main-chain using binary-search-insertion,
 *    following an order based on the Jacobsthal numbers to minimize the number of
 *    comparisons.
 *
 * The class provides two static methods:
 * - MergeInsertionSortList: Sorts a list of integers using merge-insertion sort.
 * - MergeInsertionSortVector: Sorts a vector of integers using merge-insertion sort.
 *
 * The class is designed to be non-copyable and non-assignable to prevent
 * unintended copying or assignment.
 *
 * @see https://en.wikipedia.org/wiki/Merge-insertion_sort
 * @see https://github.com/decidedlyso/merge-insertion-sort/blob/master/README.md
 */
class PmergeMe {
  private:
	PmergeMe();
	DISALLOW_COPY_AND_ASSIGN(PmergeMe);
	~PmergeMe();

  public:
	static std::list<int>   MergeInsertionSortList(std::list<int> &);
	static std::vector<int> MergeInsertionSortVector(std::vector<int> &);
};

namespace utils {

template <typename Iterator>
Iterator next(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
	std::advance(it, n);
	return it;
}

template <typename Iterator>
Iterator prev(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
	std::advance(it, -n);
	return it;
}

} // namespace utils

#endif
