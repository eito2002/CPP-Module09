#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <map>
# include <iostream>
# include <limits>
# include <algorithm>
# include <sstream>

class BitcoinExchange
{
typedef std::map<std::string, float> BTCDataMap;

private:
	BTCDataMap data_;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void calculateLine(const std::string& line);
	bool checkError(std::string date, std::string value_str, size_t pos);
	bool isValidDate(const std::string& date);
	bool isValidValue(const std::string& value);
};

#endif
