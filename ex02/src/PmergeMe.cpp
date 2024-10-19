#include "PmergeMe.hpp"
#include <iostream>

namespace SortVector {

// static int comparison_count_vec = 0;

struct Data {
	int         num;
	std::size_t pair_index;

	// 比較演算子のオーバーロード
	bool operator<(const Data &other) const {
		// ++comparison_count_vec;
		return num < other.num;
	}
	bool operator>(const Data &other) const {
		// ++comparison_count_vec;
		return num > other.num;
	}
	bool operator==(const Data &other) const {
		// ++comparison_count_vec;
		return num == other.num && pair_index == other.pair_index;
	}
};

typedef std::pair<Data, Data> DataPair;
typedef std::vector<DataPair> DataPairVector;
typedef std::vector<Data>     DataVector;

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
		os << *it;
		if (std::next(it) != v.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const Data &data) {
	os << "num: " << data.num << ", pair_index: " << data.pair_index;
	return os;
}

std::ostream &operator<<(std::ostream &os, const DataVector &v) {
	for (DataVector::const_iterator it = v.begin(); it != v.end(); ++it) {
		os << it->num;
		if (std::next(it) != v.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<DataVector> &v) {
	for (std::vector<DataVector>::const_iterator it = v.begin(); it != v.end(); ++it) {
		os << *it;
		if (std::next(it) != v.end())
			os << ", ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const DataPairVector &vec) {
	for (DataPairVector::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		os << "{ " << it->first.num << ", " << it->second.num << " }";
		if (std::next(it) != vec.end())
			os << ", ";
	}
	return os;
}

std::vector<DataPairVector> GroupVector(const DataPairVector &vec) {
	std::vector<DataPairVector> vectors;
	int                         group_count = 0;
	int                         group_size  = 0;

	DataPairVector::const_iterator it = vec.begin();
	while (it != vec.end()) {
		DataPairVector tmp_vector;
		group_size = std::pow(2, group_count + 1) - group_size;
		for (int j = 0; j < group_size && it != vec.end(); ++j, ++it) {
			tmp_vector.push_back(*it);
		}
		vectors.push_back(tmp_vector);
		++group_count;
	}
	return vectors;
}

void BinarySearch(
	DataPairVector       &sorted_vector,
	const DataPairVector &small_vector_to_insert,
	std::size_t           search_end_base
) {
	std::size_t inserted_before = 0;
	for (std::size_t i = small_vector_to_insert.size(); i > 0; --i) {
		std::size_t search_start_idx = 0;
		std::size_t search_end_idx   = i + search_end_base + inserted_before + 1;
		if (search_end_idx >= sorted_vector.size()) {
			search_end_idx = sorted_vector.size();
		}

		// 二分探索
		while (search_start_idx < search_end_idx) {
			std::size_t mid = search_start_idx + (search_end_idx - search_start_idx) / 2;
			if (small_vector_to_insert[i - 1].first < sorted_vector[mid].first) {
				search_end_idx = mid;
			} else {
				search_start_idx = mid + 1;
			}
		}

		sorted_vector.insert(
			sorted_vector.begin() + search_start_idx,
			DataPair(small_vector_to_insert[i - 1].first, small_vector_to_insert[i - 1].first)
		);
		// e.g. sorted_list: { 11, 11 }, { 17, 17 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 }
		// に lists: { 13, 19 }, { 7, 20 } を挿入する場合
		// 7 は 11 の前に挿入、この時のdistanceは 1
		// ({ 7, 7 }, { 11, 11 }, { 17, 17 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 })
		// 次の挿入する 13 のend_indexは 19 の位置であり、元々は 2 だったが 7 を挿入したため
		// inserted_beforeを 1 増やして 3 になる
		//  -> next_end が 2 なので inserted_before を増やすのは insert_index が 0, 1, 2まで
		std::size_t next_search_end_idx = i + search_end_base + inserted_before;
		if (search_start_idx <= next_search_end_idx) {
			inserted_before += 1;
		}
	}
}

DataPairVector SplitPairVector(DataPairVector &pair_vector) {
	DataPairVector pairs;
	for (std::size_t i = 0; i + 1 < pair_vector.size(); i += 2) {
		Data     num1 = {pair_vector[i].second.num, i};
		Data     num2 = {pair_vector[i + 1].second.num, i + 1};
		DataPair num_pair(num1, num2);
		// 元々のペアのインデックスを保持 e.g. { 20, 21 }, { 17, 19 }
		// -> { 19, 21 } でペアを作るが,
		// 19 の pair_index に 1 を, 21 の pair_index に 0 を保持
		// ペアを作る時のインデックスを保持することで後から取得できるように
		if (num1 < num2) {
			num_pair = DataPair(num1, num2);
		} else {
			num_pair = DataPair(num2, num1);
		}
		pairs.push_back(num_pair);
	}
	return pairs;
}

std::vector<int> ConvertToIntVector(const DataVector &vec) {
	std::vector<int> int_vector;
	for (DataVector::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		int_vector.push_back(it->num);
	}
	return int_vector;
}

DataPairVector ConvertToDataPairVector(const std::vector<int> &int_vector) {
	DataPairVector data_pair_vector;
	for (std::size_t i = 0; i < int_vector.size(); ++i) {
		Data     data = {int_vector[i], i};
		DataPair pair(data, data);
		data_pair_vector.push_back(pair);
	}
	return data_pair_vector;
}

DataPairVector
MakeSmallVector(DataPairVector &sorted, const DataPairVector &large, DataPairVector &init_nums) {
	DataPairVector small_vector;

	if (sorted.size() == 1) {
		small_vector.push_back(*large.begin());
	} else {
		for (std::size_t i = 0; i < sorted.size(); i++) {
			const std::size_t pre_index = sorted[i].first.pair_index;
			sorted[i].first.pair_index  = large[pre_index].second.pair_index;
			sorted[i].second.pair_index = large[pre_index].second.pair_index;
			// 1個前の pair_index を次の pair_index に更新
			// e.g. sorted { 19, 19 }, { 21, 21 }
			// large: { 20, 21 }, { 17, 19 } で pre_index は 1, 0 (17, 20 を取得)
			// -> 次に使いたいペアは { 13, 19 }, { 9, 21 }
			// -> 19 から 13 を取得できるように, 21 から 9 を取得できるように
			DataPair small(large[pre_index].first, large[pre_index].first);
			small_vector.push_back(small);
		}
	}
	// ペアが組めずに残った要素をsmallに追加
	if (init_nums.size() % 2 != 0) {
		Data last       = init_nums.back().second;
		last.pair_index = init_nums.size() - 1;
		DataPair pair(last, last);
		small_vector.push_back(pair);
	}

	return small_vector;
}

std::vector<int> ConvertToIntVector(const DataPairVector &vec) {
	std::vector<int> int_vector;
	for (DataPairVector::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		int_vector.push_back(it->first.num);
	}
	return int_vector;
}

DataPairVector MergeInsertionSortVector(DataPairVector &pair_vector) {

	if (pair_vector.size() == 1) {
		DataPairVector return_vector;
		return_vector.push_back(DataPair(pair_vector.front().second, pair_vector.front().second));
		return return_vector;
	}
	DataPairVector large_half_pairs   = SplitPairVector(pair_vector);
	DataPairVector sorted_pair_vector = MergeInsertionSortVector(large_half_pairs);
	DataPairVector small_half_pairs =
		MakeSmallVector(sorted_pair_vector, large_half_pairs, pair_vector);
	DataPair pair(small_half_pairs.front().first, small_half_pairs.front().first);
	sorted_pair_vector.insert(sorted_pair_vector.begin(), pair);
	small_half_pairs.erase(small_half_pairs.begin());
	std::vector<DataPairVector> vectors         = GroupVector(small_half_pairs);
	std::size_t                 search_end_base = 0;
	for (std::vector<DataPairVector>::iterator itr = vectors.begin(); itr != vectors.end(); ++itr) {
		BinarySearch(sorted_pair_vector, *itr, search_end_base);
		search_end_base += itr->size() * 2;
	}

	return sorted_pair_vector;
}

std::vector<int> MergeInsertionSortVector(std::vector<int> &vec) {
	DataPairVector data_vector   = ConvertToDataPairVector(vec);
	DataPairVector sorted_vector = MergeInsertionSortVector(data_vector);
	return ConvertToIntVector(sorted_vector);
}

} // namespace SortVector

std::vector<int> PmergeMe::MergeInsertionSortVector(std::vector<int> &vec) {
	return SortVector::MergeInsertionSortVector(vec);
}

namespace SortList {

// static int comparison_count_list = 0;

struct Data {
	int                                          num;
	std::list< std::pair<Data, Data> >::iterator pair_itr;

	// 比較演算子のオーバーロード
	bool operator<(const Data &other) const {
		// ++comparison_count_list;
		return num < other.num;
	}
	bool operator>(const Data &other) const {
		// ++comparison_count_list;
		return num > other.num;
	}
	bool operator==(const Data &other) const {
		// ++comparison_count_list;
		return num == other.num && pair_itr == other.pair_itr;
	}
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

std::ostream &operator<<(std::ostream &os, const DataPairList &list) {
	for (DataPairList::const_iterator it = list.begin(); it != list.end(); ++it) {
		os << "{ " << it->first.num << ", " << it->second.num << " }";
		if (++DataPairList::const_iterator(it) != list.end())
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

void BinarySearch(
	DataPairList &sorted_list, const DataPairList &small_list_to_insert, std::size_t search_end_base
) {
	std::size_t inserted_before = 0;
	for (DataPairList::const_reverse_iterator it = small_list_to_insert.rbegin();
		 it != small_list_to_insert.rend();
		 ++it) {
		DataPairList::iterator search_start_itr = sorted_list.begin();
		std::size_t search_end_idx = std::distance(small_list_to_insert.begin(), it.base()) +
									 search_end_base + inserted_before + 1;
		DataPairList::iterator search_end_itr;
		if (search_end_idx >= sorted_list.size()) {
			search_end_itr = sorted_list.end();
		} else {
			search_end_itr = std::next(sorted_list.begin(), search_end_idx);
		}

		// 二分探索
		while (search_start_itr != search_end_itr) {
			DataPairList::iterator mid = search_start_itr;
			std::advance(mid, std::distance(search_start_itr, search_end_itr) / 2);
			if (it->first < mid->first) {
				search_end_itr = mid;
			} else {
				search_start_itr = ++mid;
			}
		}
		sorted_list.insert(search_start_itr, DataPair(it->first, it->first));
		// e.g. sorted_list: { 11, 11 }, { 17, 17 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 }
		// に lists: { 13, 19 }, { 7, 20 } を挿入する場合
		// 7 は 11 の前に挿入、この時のdistanceは 1
		// ({ 7, 7 }, { 11, 11 }, { 17, 17 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 })
		// 次の挿入する 13 のend_indexは 19 の位置であり、元々は 2 だったが 7 を挿入したため
		// inserted_beforeを 1 増やして 3 になる
		// -> next_end_idx が 2 なので inserted_before を増やすのは distance が 1, 2, 3まで
		std::size_t next_search_end_idx =
			std::distance(small_list_to_insert.begin(), std::next(it).base()) + search_end_base +
			inserted_before + inserted_before + 1;
		if (static_cast<std::size_t>(std::distance(sorted_list.begin(), search_end_itr)) <=
			next_search_end_idx + 1) {
			inserted_before += 1;
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
		if (num1 < num2) {
			num_pair = DataPair(num1, num2);
		} else {
			num_pair = DataPair(num2, num1);
		}
		pairs.push_back(num_pair);
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
	DataPairList small_half_pairs = MakeSmallList(sorted_pair_list, large_half_pairs, pair_list);
	DataPair     pair(small_half_pairs.front().first, small_half_pairs.front().first);
	sorted_pair_list.insert(sorted_pair_list.begin(), pair);
	small_half_pairs.pop_front();
	std::list<DataPairList> lists = GroupList(small_half_pairs);
	// small_half_pairs の小さい方を挿入していく
	std::size_t search_end_base = 0;
	for (std::list<DataPairList>::iterator itr = lists.begin(); itr != lists.end(); ++itr) {
		BinarySearch(sorted_pair_list, *itr, search_end_base);
		// 挿入した分 + もともとの要素数によるスタート位置のズレ
		// e.g. sorted_list: { 11, 11 }, { 17, 17 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 }
		// lists: { 13, 19 }, { 7, 20 }
		// lists: { 9, 21 }, { 18, 22 }
		// を挿入する場合、一個目の挿入後は
		// sorted_list: { 7, 7 }, { 11, 11 }, { 13, 13 }, { 17, 17 }, { 19, 19 }, { 20, 20 },
		// { 21, 21 }, { 22, 22 }
		// 18 の二分探索範囲を 22 までにするために search_end_base を 4 加算する
		search_end_base += itr->size() * 2;
	}

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
