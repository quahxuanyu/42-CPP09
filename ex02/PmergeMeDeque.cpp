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

void PmergeMe::fordJohnsonSortDeque(int unitSize)
{
    int numOfUnits = _deque.size() / unitSize;
    // BASE CASE
    if (numOfUnits < 2)
        return;

    bool hasStraggler = numOfUnits % 2 == 1;

    deque_t::iterator start = _deque.begin();
    deque_t::iterator boundaryForPairs = advanceIter(_deque.begin(), (numOfUnits - (hasStraggler ? 1 : 0)) * unitSize);

    for (deque_t::iterator it = start; it != boundaryForPairs; std::advance(it, 2 * unitSize))
    {
        deque_t::iterator firstUnit = advanceIter(it, unitSize - 1);
        deque_t::iterator secondUnit = advanceIter(it, unitSize * 2 - 1);
        numOfComparisons++;
        if (*firstUnit > *secondUnit)
            swapUnits(firstUnit, unitSize);
    }
    fordJohnsonSortDeque(unitSize * 2);

    iter_deque main;
    iter_deque pend;
    main.insert(main.end(), advanceIter(_deque.begin(), unitSize - 1));
    main.insert(main.end(), advanceIter(_deque.begin(), (unitSize * 2) - 1));
    for (int i = 4; i <= numOfUnits; i += 2)
    {
        pend.insert(pend.end(), advanceIter(_deque.begin(), unitSize * (i - 1) - 1));
        main.insert(main.end(), advanceIter(_deque.begin(), unitSize * i - 1));
    }

    if (hasStraggler)
    {
        pend.insert(pend.end(), advanceIter(_deque.begin(), unitSize * numOfUnits - 1));
    }

    long prevJacobsthal = jacobsthalGenerator(2);
    int insertedNums = 0;
    int k = 3;
    while (true)
    {
        long currJacobsthal = jacobsthalGenerator(k);
        long jacobsthalDiff = currJacobsthal - prevJacobsthal;
        int offset = 0;
        if (jacobsthalDiff > static_cast<long>(pend.size()))
            break;
        long numOfUnitInsertions = jacobsthalDiff;

        iter_deque::iterator pendIt = pend.begin() + jacobsthalDiff - 1;
        long int boundIndex = currJacobsthal + insertedNums;
        while (numOfUnitInsertions--)
        {
            iter_deque::iterator boundIt = main.begin() + boundIndex - offset;
            iter_deque::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, compare<deque_t::iterator>);
            iter_deque::iterator inserted = main.insert(idx, *pendIt);
            pendIt = pend.erase(pendIt);
            if (pendIt != pend.begin())
                pendIt--;
            offset += ((inserted - main.begin()) == boundIndex);
        }
        prevJacobsthal = currJacobsthal;
        insertedNums += jacobsthalDiff;
        k++;
    }

    for (long unsigned int i = 0; i < pend.size(); i++)
    {
        iter_deque::iterator currPend = pend.begin() + i;
        iter_deque::iterator currBound = advanceIter(main.begin(), main.size() - pend.size() + i + hasStraggler);
        iter_deque::iterator idx = std::upper_bound(main.begin(), currBound, *currPend, compare<deque_t::iterator>);
        main.insert(idx, *currPend);
    }

    deque_t copy;
    for (iter_deque::iterator it = main.begin(); it != main.end(); it++)
    {
        for (int i = 0; i < unitSize; i++)
        {
            deque_t::iterator unitStart = *it;
            std::advance(unitStart, -unitSize + i + 1);
            copy.insert(copy.end(), *unitStart);
        }
    }

    deque_t::iterator containerIt = _deque.begin();
    deque_t::iterator copyIt = copy.begin();
    while (copyIt != copy.end())
    {
        *containerIt = *copyIt;
        containerIt++;
        copyIt++;
    }
}