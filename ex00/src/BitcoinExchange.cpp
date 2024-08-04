#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

static bool strIsNumeric(const std::string& str)
{
	for (size_t i = 0; i < str.length(); ++i)
		if (!std::isdigit(str[i]))
			return false;
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	std::stringstream ss(date);
	std::string year, month, day;
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	if (!strIsNumeric(year) || !strIsNumeric(month) || !strIsNumeric(day))
		return false;
	int yearInt, monthInt, dayInt;
	std::stringstream(year) >> yearInt;
	std::stringstream(month) >> monthInt;
	std::stringstream(day) >> dayInt;
	if (yearInt < 0 || monthInt < 1 || monthInt > 12 || dayInt < 1 || dayInt > 31)
		return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value)
{
	std::stringstream ss(value);
	float floatValue;
	char remaining;
	if (!(ss >> floatValue) || (ss >> remaining))
		return false;
	return true;
}

bool BitcoinExchange::checkError(std::string date, std::string value_str, size_t pos)
{
	float value = std::atof(value_str.c_str());
	if (pos == std::string::npos || !isValidDate(date))
	{
		std::cout << "Error: bad input" << " => " << date << std::endl;
		return false;
	}
	if (value <= 0 || value_str.find('|') != std::string::npos || !isValidValue(value_str))
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	else if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::calculateLine(const std::string& line)
{
	size_t pos = line.find_first_of('|');
	std::string date = line.substr(0, pos - 1);
	std::string value_str = line.substr(pos + 2);
	float value = std::atof(value_str.c_str());
	if (!checkError(date, value_str, pos))
		return ;
	for (std::map<std::string, float>::iterator it = this->data_.begin(); \
				it != this->data_.end(); it++)
	{
		std::map<std::string, float>::iterator next = it;
		++next;
		if ((next != this->data_.end() && it->first <= date && date < next->first) || \
			(it->first == date))
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
}
