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

  public:
	BitcoinExchange(const std::string &);
	~BitcoinExchange();
	void CalculateLine(const std::string &line);
};

#endif
