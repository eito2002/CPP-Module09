#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class BitcoinExchange {
	typedef std::map<std::string, float> BTCDataMap;

  private:
	BTCDataMap data_;

	DISALLOW_COPY_AND_ASSIGN(BitcoinExchange);

	void ParseDataFile(const std::string &);
	bool checkError(std::string date, std::string value_str, size_t pos);
	bool isValidDate(const std::string &date);
	bool isValidValue(const std::string &value);

  public:
	BitcoinExchange(const std::string &);
	~BitcoinExchange();
	void calculateLine(const std::string &line);
};

#endif
