#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {

#define YEAR_MIN  2009
#define MONTH_MIN 1
#define MONTH_MAX 12
#define DAY_MIN   1
#define DAY_MAX   31

bool StrIsNumeric(const std::string &str) {
	if (str.empty())
		return false;
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
		if (!std::isdigit(*it))
			return false;
	return true;
}

bool IsValidDate(const std::string &date) {
	std::stringstream ss(date);
	std::string       year, month, day;
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	if (year.length() != 4 || month.length() != 2 || day.length() != 2)
		return false;
	else if (!StrIsNumeric(year) || !StrIsNumeric(month) || !StrIsNumeric(day))
		return false;

	int year_int, month_int, day_int;
	std::stringstream(year) >> year_int;
	std::stringstream(month) >> month_int;
	std::stringstream(day) >> day_int;
	if (year_int < YEAR_MIN || month_int < MONTH_MIN || month_int > MONTH_MAX ||
		day_int < DAY_MIN || day_int > DAY_MAX)
		return false;
	else if (year_int == YEAR_MIN && month_int == MONTH_MIN && day_int == DAY_MIN) // for 2009-01-01
		return false;
	return true;
}

bool IsValidValue(const std::string &value) {
	std::stringstream ss(value);
	float             float_value;
	char              remaining;
	if (!(ss >> float_value) || (ss >> remaining))
		return false;
	return true;
}

bool CheckError(const std::string &date, const std::string &value_str, size_t pos) {
	float value = std::atof(value_str.c_str());
	if (pos == std::string::npos || !IsValidDate(date)) {
		std::cout << "Error: bad input"
				  << " => " << date << std::endl;
		return false;
	}
	if (value <= 0 || value_str.find('|') != std::string::npos || !IsValidValue(value_str)) {
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	} else if (value > 1000) {
		std::cout << "Error: too large a number." << std::endl;
		return false;
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

void BitcoinExchange::CalculateLine(const std::string &line) {
	size_t      pos       = line.find_first_of('|');
	std::string date      = line.substr(0, pos - 1);
	std::string value_str = line.substr(pos + 2);
	float       value     = std::atof(value_str.c_str());

	if (!CheckError(date, value_str, pos))
		return;
	BTCDataMap::iterator it = data_.lower_bound(date);
	if (it == data_.end())
		std::cout << date << " => " << value << " = " << value * (*--it).second << std::endl;
	else
		std::cout << date << " => " << value << " = " << value * (*it).second << std::endl;
}
