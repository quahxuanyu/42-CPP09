#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <sstream>


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

        void fordJohnsonSortVector(void);
        void fordJohnsonSortDeque(void);
};

#endif