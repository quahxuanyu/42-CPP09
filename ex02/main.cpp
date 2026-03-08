#include "PmergeMe.hpp"

bool validateNum(const std::string &input)
{
    if (input.empty())
        return false;
    if (input.find_first_not_of("0123456789") != std::string::npos)
        return false;
    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }

    std::string inputs;

    for (int i = 1; i < argc; i++)
    {
        if (!validateNum(argv[i]))
        {
            std::cerr << "Error: Invalid number in input." << std::endl;
            return 1;
        }
        inputs += argv[i];
        if (i < argc - 1)
            inputs += " ";
    }

    PmergeMe pmergeme;

    pmergeme.fillVector(inputs);
    pmergeme.printVector();
    return 0;
}