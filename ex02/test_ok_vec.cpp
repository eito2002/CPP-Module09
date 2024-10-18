#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

struct Data {
	int         num;
	std::size_t pair_index;

	// Data(int n, std::size_t p) : num(n), pair_index(p) {}
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

std::ostream &operator<<(std::ostream &os, const DataPairVector &vec) {
	for (DataPairVector::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		os << "{ " << it->first.num << ", " << it->second.num << " }";
		if (std::next(it) != vec.end())
			os << ", ";
	}
	return os;
}

void BinarySearch(DataPairVector &sorted_vector, const DataPairVector &small_vector_to_insert) {
	for (DataPairVector::const_reverse_iterator it = small_vector_to_insert.rbegin();
		 it != small_vector_to_insert.rend();
		 ++it) {
		bool inserted = false;
		for (DataPairVector::iterator pos = sorted_vector.begin(); pos != sorted_vector.end();
			 ++pos) {
			if (it->first.num < pos->first.num) {
				DataPair pair = {it->first, it->first};
				sorted_vector.insert(pos, pair);
				inserted = true;
				break;
			}
		}
		// 一番大きい要素よりも大きい場合は終端に挿入
		if (!inserted) {
			DataPair pair = {it->first, it->first};
			sorted_vector.push_back(pair);
		}
	}
}

DataPairVector SplitPairVector(DataPairVector &pair_vector) {
	DataPairVector pairs;
	for (std::size_t i = 0; i + 1 < pair_vector.size(); i += 2) {
		Data     num1     = {pair_vector[i].second.num, i};
		Data     num2     = {pair_vector[i + 1].second.num, i + 1};
		DataPair num_pair = {num1, num2};
		// 元々のペアのインデックスを保持 e.g. { 20, 21 }, { 17, 19 }
		// -> { 19, 21 } でペアを作るが,
		// 19 の pair_index に 1 を, 21 の pair_index に 0 を保持
        // ペアを作る時のインデックスを保持することで後から取得できるように
		if (num1.num < num2.num) {
			num_pair = {num1, num2};
		} else {
			num_pair = {num2, num1};
		}
		pairs.push_back(num_pair);
		std::cout << "num_pair: { " << num_pair.first.num << ", " << num_pair.second.num << " }"
				  << std::endl;
        std::cout << num_pair.first.pair_index << std::endl;
        std::cout << num_pair.second.pair_index << std::endl;
	}
	std::cout << std::endl;
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
		DataPair pair = {data, data};
		data_pair_vector.push_back(pair);
	}
	return data_pair_vector;
}

DataPairVector
MakeSmallVector(DataPairVector &sorted, const DataPairVector &large, DataPairVector &init_nums) {
	DataPairVector small_vector;

    std::cout << __FUNCTION__ << std::endl;
    std::cout << "sorted: " << sorted << std::endl;
    std::cout << "large: " << large << std::endl;
	if (sorted.size() == 1) {
		std::cout << large.begin()->first.num << std::endl;
		small_vector.push_back(*large.begin());
	} else {
		for (std::size_t i = 0; i < sorted.size(); i++) {
			const std::size_t pre_index = sorted[i].first.pair_index;
            std::cout << "pre_index: " << pre_index << std::endl;
			sorted[i].first.pair_index  = large[pre_index].second.pair_index;
            std::cout << "sorted[i].first.pair_index: " << sorted[i].first.pair_index << std::endl;
			sorted[i].second.pair_index = large[pre_index].second.pair_index;
            std::cout << "sorted[i].second.pair_index: " << sorted[i].second.pair_index << std::endl;
			// 1個前の pair_index を次の pair_index に更新
			// e.g. sorted { 19, 19 }, { 21, 21 }
			// large: { 20, 21 }, { 17, 19 } で pre_index は 1, 0 (17, 20 を取得)
			// -> 次に使いたいペアは { 13, 19 }, { 9, 21 }
			// -> 19 から 13 を取得できるように, 21 から 9 を取得できるように
			DataPair small = {large[pre_index].first, large[pre_index].first};
			small_vector.push_back(small);
		}
	}
	// ペアが組めずに残った要素をsmallに追加
	if (init_nums.size() % 2 != 0) {
		Data last       = init_nums.back().second;
		last.pair_index = init_nums.size() - 1;
		DataPair pair   = {last, last};
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
	DataPairVector large_half_pairs = SplitPairVector(pair_vector);
	std::cout << "large_half_pairs: " << large_half_pairs << std::endl;

	DataPairVector sorted_pair_vector = MergeInsertionSortVector(large_half_pairs);
	std::cout << "sorted_pair_vector: " << sorted_pair_vector << std::endl;

	DataPairVector small_half_pairs =
		MakeSmallVector(sorted_pair_vector, large_half_pairs, pair_vector);

	std::cout << "small_half_pairs: " << small_half_pairs << std::endl;
	DataPair pair = {small_half_pairs.front().first, small_half_pairs.front().first};
	sorted_pair_vector.insert(sorted_pair_vector.begin(), pair);
	small_half_pairs.erase(small_half_pairs.begin());
	std::vector<DataPairVector> vectors = GroupVector(small_half_pairs);
	// for (std::vector<DataPairVector>::iterator itr = vectors.begin(); itr != vectors.end();
	// ++itr) {
	//     std::cout << "vectors: " << *itr << std::endl;
	// }
	// small_half_pairs の小さい方を挿入していく
	BinarySearch(sorted_pair_vector, small_half_pairs);

	return sorted_pair_vector;
}

std::vector<int> MergeInsertionSortVector(std::vector<int> &vec) {
	DataPairVector data_vector = ConvertToDataPairVector(vec);
	// std::cout << "data_vector: " << data_vector << std::endl;
	// exit(0);
	DataPairVector sorted_vector = MergeInsertionSortVector(data_vector);
	return ConvertToIntVector(sorted_vector);
}

int main() {
	std::vector<int> vec               = {9, 2,  21, 15, 20, 3,  7, 1,  6,  11, 17,
										  4, 19, 16, 10, 13, 18, 5, 12, 22, 8,  14};
	std::vector<int> sorted_int_vector = MergeInsertionSortVector(vec);

	std::cout << "sorted_vector: " << sorted_int_vector << std::endl;
}
