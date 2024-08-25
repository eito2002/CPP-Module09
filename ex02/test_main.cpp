#include <iostream>
#include <list>
#include <utility>

template <typename T>
void sort_pair(std::pair<T, T> &p) {
	if (p.first > p.second)
		std::swap(p.first, p.second);
}

std::ostream &operator<<(std::ostream &os, const std::list<int> &l) {
	for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << *it;
		if (++std::list<int>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<std::list<int>> &l) {
	for (std::list<std::list<int>>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << *it;
		if (++std::list<std::list<int>>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::list<std::list<int>> GroupList(const std::list<int> &list) {
	std::list<std::list<int>> lists;
	int                       group_count = 0;
	int                       group_size  = 0;

	std::list<int>::const_iterator it = list.begin();
	while (it != list.end()) {
		std::list<int> tmp_list;
		group_size = std::pow(2, group_count + 1) - group_size;
		for (int j = 0; j < group_size && it != list.end(); ++j, ++it) {
			tmp_list.push_back(*it);
		}
		lists.push_back(tmp_list);
		++group_count;
	}
	return lists;
}

void MergeInsertionSortlist(std::list<int> &list) {
	typedef std::list<int>::iterator Itr;

	if (list.size() == 1)
		return;
	std::list<int> large_list;
	std::list<int> small_list;
	Itr            it = list.begin();
	while (it != list.end()) {
		int first = *it;
		++it;
		if (it != list.end()) {
			int                 second = *it;
			std::pair<int, int> pair(first, second);
		    std::cout << "{" << pair.first << ", " << pair.second << "}" << std::endl;
			sort_pair(pair);
			large_list.push_back(pair.second);
			small_list.push_back(pair.first);
            ++it;
		} else {
			small_list.push_back(first);
		}
	}

	std::cout << large_list << std::endl;
	std::cout << small_list << std::endl;
	std::cout << std::endl;
	MergeInsertionSortlist(large_list);
	large_list.push_front(small_list.front());
	small_list.pop_front();
	std::list<std::list<int>> lists = GroupList(small_list);
	for (std::list<std::list<int>>::iterator it = lists.begin(); it != lists.end(); ++it) {
		for (std::list<int>::reverse_iterator it2 = it->rbegin(); it2 != it->rend(); ++it2) {
			bool inserted = false;
			for (Itr it3 = large_list.begin(); it3 != large_list.end(); ++it3) {
				if (*it3 >= *it2) {
					large_list.insert(it3, *it2);
					inserted = true;
					break;
				}
			}
			if (!inserted) {
				large_list.push_back(*it2);
			}
		}
	}

	list = large_list;
	std::cout << large_list << std::endl;
	std::cout << small_list << std::endl;
	std::cout << std::endl;
}

int main() {
	std::list<int> list = {1, 3, 4, 10, 15, 12, 33, 23, 6};
	// std::list<int> list = {1, 3, 4, 10, 15, 12, 33, 23, 13, 21, 64, 52, 90, 100, 120, 36};
	MergeInsertionSortlist(list);
	std::cout << list << std::endl;
}
