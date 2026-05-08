#include "PmergeMe.hpp"

int numOfComparisons = 0;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

long jacobsthalGenerator(long n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    long prev = 0, curr = 1;
    for (long i = 2; i <= n; i++)
    {
        long next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
    return curr;
}
