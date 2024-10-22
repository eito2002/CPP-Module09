#include "BitcoinExchange.hpp"
#include <cstdlib> // std::atof
#include <fstream>
#include <iostream>
#include <sstream>

namespace {

std::string Trim(const std::string &str, const std::string &to_trim) {
	std::size_t first = str.find_first_not_of(to_trim);
	if (first == std::string::npos) {
		return "";
	}
	std::size_t last = str.find_last_not_of(to_trim);
	return str.substr(first, last - first + 1);
}

std::pair<std::string, std::string> SplitStringToPair(const std::string &str, char delimiter) {
	size_t pos = str.find(delimiter);
	if (pos == std::string::npos || str.find(delimiter, pos + 1) != std::string::npos) {
		return std::make_pair(str, "");
	}
	std::string first  = str.substr(0, pos);
	std::string second = str.substr(pos + 1);
	return std::make_pair(first, second);
}

bool StrIsNumeric(const std::string &str) {
	if (str.empty()) {
		return false;
	}
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it)) {
			return false;
		}
	}
	return true;
}

} // namespace

BitcoinExchange::BitcoinExchange(const std::string &file_path) {
	ParseDataFile(file_path);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::ParseDataFile(const std::string &file_path) {
	std::ifstream ifs(file_path.c_str());
	if (!ifs.is_open()) {
		throw std::runtime_error("cannot open file");
	}
	std::string line;
	std::getline(ifs, line); // skip the first line
	while (std::getline(ifs, line)) {
		size_t      delim_pos = line.find(',');
		std::string date      = line.substr(0, delim_pos);
		float       value     = std::atof(line.substr(delim_pos + 1).c_str());
		data_[date]           = value;
	}
}

bool BitcoinExchange::IsValidDate(const std::string &date) {
	std::stringstream ss(date);
	std::string       year, month, day;
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	if (year.length() != 4 || month.length() != 2 || day.length() != 2) {
		return false;
	} else if (!StrIsNumeric(year) || !StrIsNumeric(month) || !StrIsNumeric(day)) {
		return false;
	}

	int year_int, month_int, day_int;
	std::stringstream(year) >> year_int;
	std::stringstream(month) >> month_int;
	std::stringstream(day) >> day_int;
	if (year_int < YEAR_MIN || month_int < MONTH_MIN || month_int > MONTH_MAX ||
		day_int < DAY_MIN || day_int > DAY_MAX) {
		return false;
	} else if (year_int == YEAR_MIN && month_int == MONTH_MIN &&
			   day_int == DAY_MIN) { // for 2009-01-01
		return false;
	}
	return true;
}

bool BitcoinExchange::IsValidValue(const std::string &value) {
	std::stringstream ss(value);
	float             float_value;
	char              remaining;
	if (!(ss >> float_value) || (ss >> remaining)) {
		return false;
	}
	return true;
}

bool BitcoinExchange::CheckError(const std::string &date, const std::string &value_str) {
	float value = std::atof(value_str.c_str());
	if (!IsValidDate(date)) {
		std::cerr << "Error: bad input"
				  << " => " << date << std::endl;
		return false;
	}
	if (value <= 0 || !IsValidValue(value_str)) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	} else if (value > VALUE_MAX) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::CalculateLine(const std::string &line) {
	DateValuePair date_value_pair = SplitStringToPair(line, '|');
	std::string   date            = Trim(date_value_pair.first, " \t");
	std::string   value_str       = Trim(date_value_pair.second, " \t");
	float         value           = std::atof(value_str.c_str());

	if (!CheckError(date, value_str)) {
		return;
	}
	BTCDataMap::iterator it = data_.lower_bound(date);
	if (it == data_.end() || it->first != date) {
		if (it != data_.begin()) {
			// DBに存在しない日付の場合または最後の日付の場合、それに前の日付でそれに最も近いを使用する
			std::cout << date << " => " << value << " = " << value * (*--it).second << std::endl;
		} else {
			// DBの一番最初より前、実際には他のところで弾かれる
			std::cerr << "Error: date out of range" << std::endl;
		}
	} else {
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
}
