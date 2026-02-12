#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

class BitcoinExchange {
    private:
        std::map<std::string, double> _btcData;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void loadData(std::ifstream &fileStream);
        double getExchangeRate(const std::string& date) const;
};

#endif

