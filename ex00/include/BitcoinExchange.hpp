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

	bool IsValidDate(const std::string &date);
	bool IsValidValue(const std::string &value);
	bool CheckError(const std::string &date, const std::string &value_str);

	static const int YEAR_MIN  = 2009;
	static const int MONTH_MIN = 1;
	static const int MONTH_MAX = 12;
	static const int DAY_MIN   = 1;
	static const int DAY_MAX   = 31;
	static const int VALUE_MAX = 1000;

  public:
	BitcoinExchange(const std::string &);
	~BitcoinExchange();
	void CalculateLine(const std::string &);
};

#endif
