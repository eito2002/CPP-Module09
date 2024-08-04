#include "BitcoinExchange.hpp"
#include <fstream>

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

static bool StrIsNumeric(const std::string &str) {
	for (size_t i = 0; i < str.length(); ++i)
		if (!std::isdigit(str[i]))
			return false;
	return true;
}

bool BitcoinExchange::IsValidDate(const std::string &date) {
	std::stringstream ss(date);
	std::string       year, month, day;
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	if (!StrIsNumeric(year) || !StrIsNumeric(month) || !StrIsNumeric(day))
		return false;
	int yearInt, monthInt, dayInt;
	std::stringstream(year) >> yearInt;
	std::stringstream(month) >> monthInt;
	std::stringstream(day) >> dayInt;
	if (yearInt < 0 || monthInt < 1 || monthInt > 12 || dayInt < 1 || dayInt > 31)
		return false;
	return true;
}

bool BitcoinExchange::IsValidValue(const std::string &value) {
	std::stringstream ss(value);
	float             floatValue;
	char              remaining;
	if (!(ss >> floatValue) || (ss >> remaining))
		return false;
	return true;
}

bool BitcoinExchange::CheckError(std::string date, std::string value_str, size_t pos) {
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
