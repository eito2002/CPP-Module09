#include <cmath>
#include <iostream>
#include <list>

std::list<std::list<int>> GroupList(const std::list<int> &list) {
	std::list<std::list<int>> lists;
	int group_count = 0;
    int group_size = 0;

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

int main() {
	std::list<int> my_list     = {2, 2, 6, 10, 22, 33, 44, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132};
	int            group_count = 0;

	std::list<std::list<int>> grouped_list = GroupList(my_list);

	// for (const auto &group : grouped_list) {
	//     std::cout << "{ ";
	//     for (const auto &elem : group) {
	//         std::cout << elem << " ";
	//     }
	//     std::cout << "}" << std::endl;
	// }

	return 0;
}
