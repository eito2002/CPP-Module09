#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <map>
# include <iostream>
# include <limits>

class BitcoinExchange
{
private:
	std::map<std::string, float>* data_;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void calculateLine(const std::string& line);
};

#endif
