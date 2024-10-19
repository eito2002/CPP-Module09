#include <iostream>
#include <list>
#include <utility>

struct Data {
	int                       num;
	std::list<Data>::iterator pair_itr;

	bool operator==(const Data &other) const {
		return num == other.num;
	}

	friend std::ostream &operator<<(std::ostream &os, const Data &data) {
		os << "num: " << data.num;
		if (data.pair_itr != std::list<Data>::iterator()) {
			os << ", pair_itr->num: " << data.pair_itr->num;
		}
		return os;
	}
};

void sort_pair(std::pair<Data, Data> &p) {
	if (p.first.num > p.second.num)
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
	int                        group_count = 0;
	int                        group_size  = 0;

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

std::list<Data> SplitList(
	std::list<Data>                  &list
) {
    std::list<Data> large_list;
    std::cout << "list: " << list << std::endl;
    std::list<std::pair<Data, Data>> pairs;
	std::pair<Data, Data>     pair;
	std::list<Data>::iterator it = list.begin();
	while (it != list.end()) {
		std::list<Data>::iterator first_it = it;
		Data                      first    = *it;
		++it;
		if (it != list.end()) {
			std::list<Data>::iterator second_it = it;
			Data                      second    = *it;
			Data                      small;
			Data                      large;
			// sort_pair(pair);
			if (first.num <= second.num) {
				small = {first.num, second_it};
				large = {second.num, first_it};
			} else {
				small = {second.num, first_it};
				large = {first.num, second_it};
			}
			pair = std::pair<Data, Data>(small, large);
			large_list.push_back(large);
            std::cout << "large: " << large << std::endl;
			// small_list.push_back(small);
            // std::cout << "small: " << small << std::endl;
			pairs.push_back(pair);
			std::cout << "{ " << pair.first.num << ", " << pair.second.num << " }" << std::endl;
			++it;
        }
		// } else {
		//     pairs.push_back(pair);
		// }
	}
    return large_list;
}

std::list<int> ConvertToIntList(const std::list<Data> &list) {
	std::list<int> int_list;
	for (std::list<Data>::const_iterator it = list.begin(); it != list.end(); ++it) {
		int_list.push_back(it->num);
	}
	return int_list;
}

std::list<Data> ConvertToDataList(const std::list<int> &int_list) {
	std::list<Data> data_list;
	for (std::list<int>::const_iterator it = int_list.begin(); it != int_list.end(); ++it) {
		Data data;
		data.num = *it;
		data_list.push_back(data);
	}
	return data_list;
}

Data FindPairMate(const Data &data, const std::list<std::pair<Data, Data>> &pairs) {
	for (const auto &pair : pairs) {
		if (pair.first == data) {
			return pair.second;
		}
		if (pair.second == data) {
			return pair.first;
		}
	}
	return Data{-1, std::list<Data>::iterator()};
}

void BinaryInsertionSort(
	std::list<Data>                  &small_list,
	std::list<Data>                  &large_list,
	std::list<std::pair<Data, Data>> &pairs
) {
	typedef std::list<Data>::iterator Itr;

	large_list.push_front(small_list.front());
	small_list.pop_front();

	std::list<std::list<Data>> lists = GroupList(small_list);
	for (std::list<std::list<Data>>::iterator it = lists.begin(); it != lists.end(); ++it) {
		for (std::list<Data>::reverse_iterator it2 = it->rbegin(); it2 != it->rend(); ++it2) {
			Data mate = FindPairMate(*it2, pairs);
			Itr  search_end =
				std::find_if(large_list.begin(), large_list.end(), [&mate](const Data &d) {
					return d == mate;
				});
			Itr pos = std::lower_bound(
				large_list.begin(),
				search_end,
				*it2,
				[](const Data &a, const Data &b) { return a.num < b.num; }
			);
			large_list.insert(pos, *it2);
		}
	}
}

void TmpSort(std::list<Data> &small_list, std::list<Data> &large_list) {
    small_list.clear();
	std::list<Data> tmp_list;
	for (std::list<Data>::iterator it = large_list.begin(); it != large_list.end(); ++it) {
		std::cout << (*it) << std::endl;
        small_list.push_back(*it->pair_itr);
	}
	large_list.push_front(small_list.front());
    small_list.pop_front();
}

std::list<Data> MakeSmallList(std::list<Data> &sorted_list, std::list<Data> &large_list) {
    std::list<Data> small_list;

    if (sorted_list.size() == 1) {
        small_list.push_back(*large_list.begin()->pair_itr);
    } else {
        for (std::list<Data>::iterator it = sorted_list.begin(); it != sorted_list.end(); ++it) {
            // std::cout << it->pair_itr->num << std::endl;
            small_list.push_back(*it->pair_itr);
        }
    }
    return small_list;
}

std::list<Data> MergeInsertionSortlist(std::list<Data> &list) {
	typedef std::list<Data>::iterator Itr;

	if (list.size() == 2) {
        if (list.front().num > list.back().num) {
            std::swap(list.front(), list.back());
        }
		return list;
    }
	std::list<Data>                  large_list = SplitList(list);

    // large_list = sorted_list

	std::cout << large_list << std::endl;
	std::cout << std::endl;
	std::list<Data> sorted_list = MergeInsertionSortlist(large_list);
	// SortSmallList(small_list, large_list);
    // std::cout << "test: " << sorted_list.front().pair_itr->pair_itr->num << std::endl;
    // pair の pair ... -> size 1 になるまで
    for (std::list<Data>::iterator it = large_list.begin(); it != large_list.end(); ++it) {
        std::cout << "large_list: " << *it << std::endl;
    }
    for (std::list<Data>::iterator it = sorted_list.begin(); it != sorted_list.end(); ++it) {
        std::cout << "sorted_list: " << *it << std::endl;
    }
    std::cout << "sorted_list:    " << sorted_list << std::endl;

	std::list<Data>                  small_list = MakeSmallList(sorted_list, large_list);
    std::cout << "small_list:     " << small_list << std::endl;
    sorted_list.push_front(*sorted_list.front().pair_itr);
    small_list.pop_front();

    for (std::list<Data>::iterator it = sorted_list.begin(); it != sorted_list.end(); ++it) {
        std::cout << "sorted_list: " << *it << std::endl;
    }
    std::cout << "sorted_list:    " << sorted_list << std::endl;
	std::cout << "large_list:     " << large_list << std::endl;
	std::cout << "small_list:     " << small_list << std::endl;
	std::cout << std::endl;
    return sorted_list;
}

std::list<int> MergeInsertionSortList(std::list<int> &list) {
    std::list<Data> data_list = ConvertToDataList(list);
    std::list<Data> sorted_list = MergeInsertionSortlist(data_list);
    return ConvertToIntList(sorted_list);
}

int main() {
	// std::list<Data> list = {1, 3, 4, 10, 15, 12, 33, 23, 6};
	// std::list<Data> list = {1, 3, 4, 10, 15, 12, 33, 23, 13, 21, 64, 52, 90, 100, 120, 36};
	// std::list<int> list = {125, 32, 43343, 1212, 1, 2, 22, 272};
	std::list<int>  list      = {9, 2,  21, 15, 20, 3,  7, 1,  6,  11, 17,
								 4, 19, 16, 10, 13, 18, 5, 12, 22, 8,  14};
	std::list<Data> data_list = ConvertToDataList(list);
	MergeInsertionSortlist(data_list);
	// std::cout << list << std::endl;
}
