#include "BitcoinExchange.hpp"

bool validate_value(float value)
{

}

bool validate_date(std::string date)
{
    
    throw std::exception();
}

void run_analysis(BitcoinExchange &btc, std::ifstream &inputStream)
{
    std::string line;

    std::getline(inputStream, line); // Skip header
    while (std::getline(inputStream, line))
    {
        size_t post = line.find('|');
        std::string date = line.substr(0, post - 1);
        float value = strtof(line.substr(post + 2).c_str(), NULL);

        try
        {

        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << " => " << line << std::endl;
            continue;
        }


        std::cout << date << " => " << value << " = " << btc.getExchangeRate(date) * value << std::endl;
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