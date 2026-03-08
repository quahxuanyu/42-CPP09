#include "PmergeMe.hpp"

void PmergeMe::fillVector(std::string &input)
{
    std::istringstream stream(input);
    std::string numStr;

    while (std::getline(stream, numStr, ' '))
    {
        int num = strtol(numStr.c_str(), NULL, 10);
        this->_vector.push_back(num);
    }
}

void PmergeMe::printVector(void)
{
    for (size_t i = 0; i < _vector.size(); i++)
    {
        std::cout << this->_vector[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::fordJohnsonSortVector(void)
{
    // to be made
}