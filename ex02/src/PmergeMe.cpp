#include "PmergeMe.hpp"
#include <iostream>

void PmergeMe::printResult(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	// std::cout << "Before: ";
	// for (int i = 1; i < argc; i++)
	// 	std::cout << argv[i] << " ";
	// std::cout << std::endl;
	// mergeSortVector(argc, argv);
	// mergeSortList(argc, argv);
	// if (checkSorted())
	// {
	// 	std::cout << "After:  ";
	// 	for (std::vector<int>::iterator it = vector_.begin(); it != vector_.end(); it++)
	// 		std::cout << *it << " ";
	// 	std::cout << std::endl;
	// 	std::cout << "Time to process a range of " << vector_.size() << " elements with std::vector
	// : " << \ 				durationVec_ << " micro seconds" << std::endl;
	// 	std::cout << "Time to process a range of " << list_.size() << " elemens with std::list : "
	// << \ 				durationLis_ << " micro seconds" << std::endl;
	// }
	// else
	// 	std::cout << "Error: not sorted" << std::endl;
}

bool PmergeMe::checkSorted() {
	// if (vector_.size() != list_.size())
	// 	return false;
	// std::list<int>::iterator it = list_.begin();
	// for (size_t i = 0; i < vector_.size(); i++, it++)
	// 	if (vector_[i] != *it)
	// 		return false;
	return true;
}

namespace SortList {

#include <list>
#include <utility>

struct Data {
	int                                          num;
	std::list< std::pair<Data, Data> >::iterator pair_itr;
};

typedef std::pair<Data, Data> DataPair;
typedef std::list<DataPair>   DataPairList;
typedef std::list<Data>       DataList;

std::ostream &operator<<(std::ostream &os, const std::list<int> &l) {
	for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << *it;
		if (++std::list<int>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const Data &data) {
	os << "num: " << data.num << ", pair_itr: " << &(*data.pair_itr);
	return os;
}

std::ostream &operator<<(std::ostream &os, const DataList &l) {
	for (DataList::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << it->num;
		if (++DataList::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::list<DataList> &l) {
	for (std::list<DataList>::const_iterator it = l.begin(); it != l.end(); ++it) {
		os << *it;
		if (++std::list<DataList>::const_iterator(it) != l.end())
			os << ", ";
	}
	return os;
}

std::list<DataPairList> GroupList(const DataPairList &list) {
	std::list<DataPairList> lists;
	int                     group_count = 0;
	int                     group_size  = 0;

	DataPairList::const_iterator it = list.begin();
	while (it != list.end()) {
		DataPairList tmp_list;
		group_size = std::pow(2, group_count + 1) - group_size;
		for (int j = 0; j < group_size && it != list.end(); ++j, ++it) {
			tmp_list.push_back(*it);
		}
		lists.push_back(tmp_list);
		++group_count;
	}
	return lists;
}

std::ostream &operator<<(std::ostream &os, const DataPairList &list) {
	for (DataPairList::const_iterator it = list.begin(); it != list.end(); ++it) {
		os << "{ " << it->first.num << ", " << it->second.num << " }";
		if (++DataPairList::const_iterator(it) != list.end())
			os << ", ";
	}
	return os;
}

void BinarySearch(DataPairList &sorted_list, const DataPairList &small_list_to_insert) {
	for (DataPairList::const_reverse_iterator it = small_list_to_insert.rbegin();
		 it != small_list_to_insert.rend();
		 ++it) {
		bool inserted = false;
		for (DataPairList::iterator pos = sorted_list.begin(); pos != sorted_list.end(); ++pos) {
			if (it->first.num < pos->first.num) {
				DataPair pair(it->first, it->first);
				sorted_list.insert(pos, pair);
				inserted = true;
				break;
			}
		}
		// 一番大きい要素よりも大きい場合は終端に挿入
		if (!inserted) {
			DataPair pair(it->first, it->first);
			sorted_list.push_back(pair);
		}
	}
}

DataPairList SplitPairList(DataPairList &pair_list) {
	DataPairList pairs;
	for (DataPairList::iterator it = pair_list.begin();
		 it != pair_list.end() && std::next(it) != pair_list.end();
		 std::advance(it, 2)) {
		Data     num1 = {it->second.num, it};
		Data     num2 = {std::next(it)->second.num, std::next(it)};
		DataPair num_pair(num1, num2);
		// 元々のベアのイテレーターを保持 e.g. { 9, 21 }, { 13, 19 }
		// -> { 19, 21 } でペアを作るが,
		// 19 の pair_itr に　{ 13, 19 } を, 21 の pair_itr に　{ 9, 21 } を保持
		if (num1.num < num2.num) {
			num_pair = DataPair(num1, num2);
		} else {
			num_pair = DataPair(num2, num1);
		}
		pairs.push_back(num_pair);
		// std::cout << "num_pair: { " << num_pair.first.num << ", " << num_pair.second.num << " }"
		// 		  << std::endl;
	}
	return pairs;
}

std::list<int> ConvertToIntList(const std::list<Data> &list) {
	std::list<int> int_list;
	for (std::list<Data>::const_iterator it = list.begin(); it != list.end(); ++it) {
		int_list.push_back(it->num);
	}
	return int_list;
}

DataPairList ConvertToDataPairList(const std::list<int> &int_list) {
	DataPairList data_pair_list;
	for (std::list<int>::const_iterator it = int_list.begin(); it != int_list.end(); ++it) {
		std::pair<Data, Data> data_pair;
		data_pair.first.num       = *it;
		data_pair.first.pair_itr  = data_pair_list.begin();
		data_pair.second.num      = *it;
		data_pair.second.pair_itr = data_pair_list.begin();
		data_pair_list.push_back(data_pair);
	}
	return data_pair_list;
}

DataPairList
MakeSmallList(DataPairList &sorted, const DataPairList &large, DataPairList &init_nums) {
	DataPairList small_list;

	if (sorted.size() == 1) {
		small_list.push_back(*large.begin());
	} else {
		for (DataPairList::iterator it = sorted.begin(); it != sorted.end(); ++it) {
			const DataPairList::iterator pre_itr = it->first.pair_itr; // firstでもsecondでも良い
			// std::cout << "pre_itr: " <<   pre_itr->first.num << std::endl;
			small_list.push_back(*pre_itr);
			it->first.pair_itr  = pre_itr->second.pair_itr;
			it->second.pair_itr = pre_itr->second.pair_itr;
			// 1個前の pair_itr を次の pair_itr に更新
			// e.g. sorted { 19, 19 }, { 21, 21 }
			// 今回は { 17, 19 }, { 20, 21 } のペアを使ったため pre_itr は 17, 20
			// -> 次に使いたいペアは { 13, 19 }, { 9, 21 }
			// -> 19 から 13 を取得できるように, 21 から 9 を取得できるように
		}
	}
	// ペアが組めずに残った要素をsmallに追加
	if (init_nums.size() % 2 != 0) {
		Data last     = std::prev(init_nums.end())->second;
		last.pair_itr = std::prev(init_nums.end());
		DataPair pair(last, last);
		small_list.push_back(pair);
	}

	return small_list;
}

std::list<int> ConvertToIntList(const DataPairList &list) {
	std::list<int> int_list;
	for (DataPairList::const_iterator it = list.begin(); it != list.end(); ++it) {
		int_list.push_back(it->first.num);
	}
	return int_list;
}

DataPairList MergeInsertionSortList(DataPairList &pair_list) {

	if (pair_list.size() == 1) {
		DataPairList return_list;
		return_list.push_back(DataPair(pair_list.front().second, pair_list.front().second));
		return return_list;
	}
	DataPairList large_half_pairs = SplitPairList(pair_list);

	DataPairList sorted_pair_list = MergeInsertionSortList(large_half_pairs);
	// std::cout << "sorted_pair_list: " << sorted_pair_list << std::endl;
	DataPairList small_half_pairs = MakeSmallList(sorted_pair_list, large_half_pairs, pair_list);
	// std::cout << "small_half_pairs: " << small_half_pairs << std::endl;
	DataPair pair(small_half_pairs.front().first, small_half_pairs.front().first);
	sorted_pair_list.insert(sorted_pair_list.begin(), pair);
	small_half_pairs.pop_front();
	std::list<DataPairList> lists = GroupList(small_half_pairs);
	// for (std::list<DataPairList>::iterator itr = lists.begin(); itr != lists.end(); ++itr) {
	// 	std::cout << "lists: " << *itr << std::endl;
	// }
	// small_half_pairs の小さい方を挿入していく
	BinarySearch(sorted_pair_list, small_half_pairs);

	return sorted_pair_list;
}

std::list<int> MergeInsertionSortList(std::list<int> &list) {
	DataPairList data_list   = ConvertToDataPairList(list);
	DataPairList sorted_list = MergeInsertionSortList(data_list);
	return ConvertToIntList(sorted_list);
}

} // namespace SortList

std::list<int> PmergeMe::MergeInsertionSortList(std::list<int> &list) {
	return SortList::MergeInsertionSortList(list);
}
