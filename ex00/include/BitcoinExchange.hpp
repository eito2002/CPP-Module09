#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <string>
#include <utility> // std::pair

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                                         \
	TypeName(const TypeName &);                                                                    \
	void operator=(const TypeName &)

class BitcoinExchange {
  private:
	typedef std::map<std::string, float>        BTCDataMap;
	typedef std::pair<std::string, std::string> DateValuePair;

	BTCDataMap data_;
	DISALLOW_COPY_AND_ASSIGN(BitcoinExchange);
	void ParseDataFile(const std::string &);

  public:
	BitcoinExchange(const std::string &);
	~BitcoinExchange();
	void CalculateLine(const std::string &);
};

#endif
