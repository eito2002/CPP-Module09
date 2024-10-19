#include <iostream>
#include <list>
#include <utility>

struct Data
{
    int num;
    std::list<int>::const_iterator pair_itr;
};


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

std::ostream &operator<<(std::ostream &os, const std::list<Data> &l) {
	for (std::list<Data>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << it->num;
		if (++std::list<Data>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<std::list<Data>> &l) {
	for (std::list<std::list<Data>>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << *it;
		if (++std::list<std::list<Data>>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::list<std::list<Data>> GroupList(const std::list<Data> &list) {
	std::list<std::list<Data>> lists;
	int                       group_count = 0;
	int                       group_size  = 0;

	std::list<Data>::const_iterator it = list.begin();
	while (it != list.end()) {
		std::list<Data> tmp_list;
		group_size = std::pow(2, group_count + 1) - group_size;
		for (int j = 0; j < group_size && it != list.end(); ++j, ++it) {
			tmp_list.push_back(*it);
		}
		lists.push_back(tmp_list);
		++group_count;
	}
	return lists;
}

#define END -1

typedef std::list<int>::const_iterator Itr;

void SplitList(const std::list<int> &list, std::list<Data> &small_list, std::list<Data> &large_list, std::list<std::pair<int, int>> &pairs) {
    std::pair<int, int> pair;
    std::list<int>::const_iterator it = list.begin();
    while (it != list.end()) {
        int first = *it;
        ++it;
        if (it != list.end()) {
            int                 second = *it;
            pair = std::pair<int, int>(first, second);
            sort_pair(pair);
            Data small = {pair.first, std::find(list.begin(), list.end(), pair.second)};
            Data large = {pair.second, std::find(list.begin(), list.end(), pair.first)};
            large_list.push_back(large);
            small_list.push_back(small);
            pairs.push_back(pair);
            std::cout << "{ " <<  pair.first << ", " << pair.second << " }" << std::endl;
            ++it;
        } else {
            pairs.push_back(pair);
            Data small = {pair.first, it};
            small_list.push_back(small);
        }
    }
}

int FindPairMate(int val, std::list<std::pair<int, int>>& pairs) {
    for (std::list<std::pair<int, int>>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it->first == val)
            return it->second;
    }
    return END;
}

// void BinaryInsertionSort(const std::list<Data> &small_list, std::list<Data> &large_list, std::list<std::pair<int, int>> &pairs) {
// 	typedef std::list<Data>::iterator Itr; //tmp

//     std::list<std::list<Data>> lists = GroupList(small_list);
// 	for (std::list<std::list<Data>>::iterator it = lists.begin(); it != lists.end(); ++it) {
// 		for (std::list<Data>::reverse_iterator it2 = it->rbegin(); it2 != it->rend(); ++it2) {
//             Itr search_end = std::find(large_list.begin(), large_list.end(), FindPairMate(*it2, pairs));
//             Itr pos = std::lower_bound(large_list.begin(), search_end, *it2);
// 			// large_list.insert(pos, *it2);
// 		}
// 	}
// }

std::list<Data> ConvertToDataList(const std::list<int> &list) {
    std::list<Data> data_list;
    for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
        Data data;
        data.num = *it;
        data_list.push_back(data);
    }
    return data_list;
}

std::list<int> ConvertToIntList(const std::list<Data> &list) {
    std::list<int> int_list;
    for (std::list<Data>::const_iterator it = list.begin(); it != list.end(); ++it) {
        int_list.push_back(it->num);
    }
    return int_list;
}

void MergeInsertionSortlist(std::list<int> &list) {
	typedef std::list<Data>::iterator Itr;

	if (list.size() == 1)
		return;
	std::list<Data> large_list;
	std::list<Data> small_list;
    std::list<std::pair<int, int>> pairs;
	SplitList(list, small_list, large_list, pairs);

	std::cout << large_list << std::endl;
	std::cout << small_list << std::endl;
	std::cout << std::endl;
    std::list<int> large_int_list = ConvertToIntList(large_list);
	std::cout << large_int_list << std::endl;
	std::cout << std::endl;
	MergeInsertionSortlist(large_int_list);
    std::cout << "large_list_front:      " << large_list.front().num << std::endl;
    std::cout << "large_list_front pair: " << *(large_list.front().pair_itr) << std::endl;
    large_int_list.push_front(*(large_list.front().pair_itr));
	large_list.push_front(small_list.front());
	small_list.pop_front();
    std::cout << "large_list_front:      " << large_list.front().num << std::endl;
    std::cout << "large_list_front pair: " << *(large_list.front().pair_itr) << std::endl;
	// BinaryInsertionSort(small_list, large_list, pairs);

    // large_list = ConvertToDataList(large_int_list);
	list = large_int_list;
	std::cout << "large_int_list: " << large_int_list << std::endl;
	std::cout << "large_list:     " << large_list << std::endl;
	std::cout << "small_list:     " << small_list << std::endl;
	std::cout << std::endl;
}

int main() {
	// std::list<Data> list = {1, 3, 4, 10, 15, 12, 33, 23, 6};
	// std::list<Data> list = {1, 3, 4, 10, 15, 12, 33, 23, 13, 21, 64, 52, 90, 100, 120, 36};
	std::list<int> list = {125, 32, 43343, 1212, 1, 2, 22, 272};
	MergeInsertionSortlist(list);
	// std::cout << list << std::endl;
}
