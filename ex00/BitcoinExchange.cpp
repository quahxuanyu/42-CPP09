#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        this->_btcData = other._btcData;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadData(std::ifstream &fileStream) {
    std::string line;
    std::string key;
    float value;

    std::getline(fileStream, line); // Skip header
    while (std::getline(fileStream, line)) {
        size_t pos = line.find(',');
        key = line.substr(0, pos);
        value = strtof(line.substr(pos + 1).c_str(), NULL);
        _btcData.insert(std::make_pair(key, value));
    }
}

/**
 * lower_bound return first iterator whoose key is NOT less that the specified key
 * -- moves the iterator down
 * 
 */
double BitcoinExchange::getExchangeRate(const std::string &date) const {
    if (_btcData.count(date) > 0) {
        return _btcData.at(date);
    }
    return (--(_btcData.lower_bound(date)))->second;
}