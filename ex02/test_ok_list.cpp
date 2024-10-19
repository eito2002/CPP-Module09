#include <algorithm>
#include <iostream>
#include <list>
#include <utility>

struct Data {
	int                                        num;
	std::list<std::pair<Data, Data>>::iterator pair_itr;
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

std::size_t BinarySearch(
	DataPairList &sorted_list, const DataPairList &small_list_to_insert, std::size_t search_end_base
) {
	std::cout << __FUNCTION__ << std::endl;
	std::cout << "search_end_base: " << search_end_base << std::endl;
	std::size_t inserted_before = 0;
	for (DataPairList::const_reverse_iterator it = small_list_to_insert.rbegin();
		 it != small_list_to_insert.rend();
		 ++it) {
		DataPairList::iterator search_start_itr = sorted_list.begin();
		std::size_t            search_end_idx =
			std::distance(small_list_to_insert.begin(), it.base()) + search_end_base + 1;
		std::cout << "search_end_idx: " << search_end_idx << std::endl;
        DataPairList::iterator search_end_itr;
        if (search_end_idx + inserted_before >= sorted_list.size()) {
            search_end_itr = sorted_list.end();
        } else {
            search_end_itr = std::next(sorted_list.begin(), search_end_idx + inserted_before);
        }

		std::cout << "to_insert: " << it->first.num << std::endl;
		std::cout << "search_end: " << search_end_itr->first.num << std::endl;

		// 二分探索を手動で実装
		while (search_start_itr != search_end_itr) {
			DataPairList::iterator mid = search_start_itr;
			std::advance(mid, std::distance(search_start_itr, search_end_itr) / 2);
			if (it->first.num < mid->first.num) {
				search_end_itr = mid;
			} else {
				search_start_itr = ++mid;
			}
		}
		std::size_t next_search_end_idx =
			std::distance(small_list_to_insert.begin(), std::next(it).base()) + search_end_base + 1;
		std::cout << "next_search_end_idx: " << next_search_end_idx << std::endl;
		sorted_list.insert(search_start_itr, DataPair(it->first, it->first));
		if (std::distance(sorted_list.begin(), search_end_itr) <= next_search_end_idx) {
			inserted_before += 1;
		}
	}
	std::cout << "return inserted_before: " << inserted_before + 1 << std::endl;
	return inserted_before + 1;
}

DataPairList SplitPairList(DataPairList &pair_list) {
	DataPairList           pairs;
	DataPairList::iterator it = pair_list.begin();
	for (DataPairList::iterator it = pair_list.begin();
		 it != pair_list.end() && std::next(it) != pair_list.end();
		 std::advance(it, 2)) {
		Data     num1     = {it->second.num, it};
		Data     num2     = {std::next(it)->second.num, std::next(it)};
		DataPair num_pair = {num1, num2};
		// 元々のベアのイテレーターを保持 e.g. { 9, 21 }, { 13, 19 }
		// -> { 19, 21 } でペアを作るが,
		// 19 の pair_itr に　{ 13, 19 } を, 21 の pair_itr に　{ 9, 21 } を保持
		if (num1.num < num2.num) {
			num_pair = {num1, num2};
		} else {
			num_pair = {num2, num1};
		}
		pairs.push_back(num_pair);
		// std::cout << "num_pair: { " << num_pair.first.num << ", " << num_pair.second.num << " }"
		// 		  << std::endl;
		// std::cout << "pair_first: { " << num_pair.first.pair_itr->first.num << ", " <<
		// num_pair.first.pair_itr->second.num << " }" << std::endl; std::cout << "pair_second: { "
		// << num_pair.second.pair_itr->first.num << ", " << num_pair.second.pair_itr->second.num <<
		// " }" << std::endl;
	}
	std::cout << std::endl;
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
		std::cout << large.begin()->first.num << std::endl;
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
	std::cout << init_nums.size() % 2 << std::endl;
	if (init_nums.size() % 2 != 0) {
		Data last     = std::prev(init_nums.end())->second;
		last.pair_itr = std::prev(init_nums.end());
		DataPair pair = {last, last};
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
		return_list.push_back({pair_list.front().second, pair_list.front().second});
		return return_list;
	}
	DataPairList large_half_pairs = SplitPairList(pair_list);

	DataPairList sorted_pair_list = MergeInsertionSortList(large_half_pairs);
	std::cout << "sorted_pair_list: " << sorted_pair_list << std::endl;

	DataPairList small_half_pairs = MakeSmallList(sorted_pair_list, large_half_pairs, pair_list);

	std::cout << "small_half_pairs: " << small_half_pairs << std::endl;
	DataPair pair = {small_half_pairs.front().first, small_half_pairs.front().first};
	sorted_pair_list.insert(sorted_pair_list.begin(), pair);
	small_half_pairs.pop_front();
	std::list<DataPairList> lists = GroupList(small_half_pairs);
	for (std::list<DataPairList>::iterator itr = lists.begin(); itr != lists.end(); ++itr) {
		std::cout << "lists: " << *itr << std::endl;
	}
	// small_half_pairs の小さい方を挿入していく
	std::size_t search_end_base = 0;
	for (std::list<DataPairList>::iterator itr = lists.begin(); itr != lists.end(); ++itr) {
		search_end_base += BinarySearch(sorted_pair_list, *itr, search_end_base);
		search_end_base += itr->size();
	}

	return sorted_pair_list;
}

std::list<int> MergeInsertionSortList(std::list<int> &list) {
	DataPairList data_list   = ConvertToDataPairList(list);
	DataPairList sorted_list = MergeInsertionSortList(data_list);
	return ConvertToIntList(sorted_list);
}

int main() {
	// std::list<int> list = {1, 3, 4, 10, 15, 12, 33, 23, 6};
	// std::list<int> list = {1, 3, 4, 10, 15, 12, 33, 23, 13, 21, 64, 52, 90, 100, 120, 36};
	// std::list<int> list = {125, 32, 43343, 1212, 1, 2, 22, 272};
	std::list<int> list            = {9, 2,  21, 15, 20, 3,  7, 1,  6,  11, 17,
									  4, 19, 16, 10, 13, 18, 5, 12, 22, 8,  14};
	std::list<int> sorted_int_list = MergeInsertionSortList(list);

	std::cout << "sorted_list: " << sorted_int_list << std::endl;
	// std::cout << list << std::endl;
}
