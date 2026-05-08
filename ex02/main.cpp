#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>

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
    std::cout << "Before: ";
    pmergeme.printVector();

    std::cout << "After:" << std::endl;

    // Time vector sort
    clock_t startVector = clock();
    pmergeme.fordJohnsonSortVector(1);
    clock_t endVector = clock();

    pmergeme.printVector();

    // Time deque sort
    pmergeme.fillDeque(inputs);
    clock_t startDeque = clock();
    pmergeme.fordJohnsonSortDeque(1);
    clock_t endDeque = clock();

    // Calculate times in microseconds
    double timeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000.0;
    double timeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : " << timeDeque << " us" << std::endl;

    return 0;
}