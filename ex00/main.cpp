#include "BitcoinExchange.hpp"

static bool	isLeapYear(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool validate_value(float value)
{
    if (value < 0)
    {
        throw std::runtime_error("not a positive number.");
    }
    if (value > 1000)
    {
        throw std::runtime_error("too large a number.");
    }
    return true;
}

bool validate_date(std::string date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        throw std::runtime_error("invalid date format => " + date);

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
        throw std::runtime_error("invalid date => " + date);

    int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year))
        daysInMonths[1] = 29;
    
    if (day > daysInMonths[month - 1]) // ensure number of days is valid for the month
        throw std::runtime_error("invalid date => " + date);
    
    if (year == 2009 && month < 1 && day < 2) // ensure date is not before 2009-01-01
        throw std::runtime_error("date before 2009-01-01 => " + date);
    
    return true;
}

void run_analysis(BitcoinExchange &btc, std::ifstream &inputStream)
{
    std::string line;

    std::getline(inputStream, line); // Skip header
    while (std::getline(inputStream, line))
    {
        try
        {
            size_t post = line.find('|');
            if (post == std::string::npos)
            {
                throw std::runtime_error("bad input => " + line);
            }

            std::string date = line.substr(0, post - 1);
            validate_date(date);

            float value = strtof(line.substr(post + 1).c_str(), NULL);
            validate_value(value);
            
            std::cout << date << " => " << value << " = " << btc.getExchangeRate(date) * value << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }
    std::ifstream dataFile("data.csv");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not open data.csv " << argv[1] << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }
    
    BitcoinExchange btc;

    btc.loadData(dataFile);
    run_analysis(btc, inputFile);
}