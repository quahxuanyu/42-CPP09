#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <sstream>

extern int numOfComparisons;
typedef std::vector<int>	vector_t;
typedef std::vector<std::vector<int>::iterator>	iter_vector;
typedef std::deque<int>	deque_t;
typedef std::deque<std::deque<int>::iterator>	iter_deque;

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void fillVector(std::string &input);
        void fillDeque(std::string &input);

        void printVector(void);
        void printDeque(void);

        void fordJohnsonSortVector(int unitSize);
        void fordJohnsonSortDeque(int unitSize);
};

template <typename T>
T advanceIter(T it, int steps)
{
	std::advance(it, steps);
	return (it);
}

template <typename T>
void	swapUnits(T firstUnit, int unitSize)
{
	T	start = advanceIter(firstUnit, -unitSize + 1);
	T	end = advanceIter(start, unitSize);
	while (start != end)
	{
		std::iter_swap(start, advanceIter(start, unitSize));
		start++;
	}
}

template <typename T>
bool	compare(T left, T right)
{
	numOfComparisons++;
	return (*left < *right);
}

long jacobsthalGenerator(long n);

#endif