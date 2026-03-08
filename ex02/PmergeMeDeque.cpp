#include "PmergeMe.hpp"

void PmergeMe::fillDeque(std::string &input)
{
    std::istringstream stream(input);
    std::string numStr;

    while (std::getline(stream, numStr, ' '))
    {
        int num = strtol(numStr.c_str(), NULL, 10);
        this->_deque.push_back(num);
    }
}

void PmergeMe::printDeque(void)
{
    for (size_t i = 0; i < _deque.size(); i++)
    {
        std::cout << this->_deque[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::fordJohnsonSortDeque(void)
{
    // to be made
}