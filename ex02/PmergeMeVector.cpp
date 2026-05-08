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

void PmergeMe::fordJohnsonSortVector(int unitSize)
{
    int numOfUnits = _vector.size() / unitSize;
    // BASE CASE
    if (numOfUnits < 2)
        return;

    bool hasStraggler = numOfUnits % 2 == 1;

    vector_t::iterator start = _vector.begin();
    vector_t::iterator boundaryForPairs = advanceIter(_vector.begin(), (numOfUnits - (hasStraggler ? 1 : 0)) * unitSize);

    for (vector_t::iterator it = start; it != boundaryForPairs; std::advance(it, 2 * unitSize))
    {
        vector_t::iterator firstUnit = advanceIter(it, unitSize - 1);
        vector_t::iterator secondUnit = advanceIter(it, unitSize * 2 - 1);
        numOfComparisons++;
        if (*firstUnit > *secondUnit)
            swapUnits(firstUnit, unitSize);
    }
    fordJohnsonSortVector(unitSize * 2);

    iter_vector main;
    iter_vector pend;
    main.insert(main.end(), advanceIter(_vector.begin(), unitSize - 1));
    main.insert(main.end(), advanceIter(_vector.begin(), (unitSize * 2) - 1));
    for (int i = 4; i <= numOfUnits; i += 2)
    {
        pend.insert(pend.end(), advanceIter(_vector.begin(), unitSize * (i - 1) - 1));
        main.insert(main.end(), advanceIter(_vector.begin(), unitSize * i - 1));
    }

    if (hasStraggler)
    {
        pend.insert(pend.end(), advanceIter(_vector.begin(), unitSize * numOfUnits - 1));
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

        iter_vector::iterator pendIt = pend.begin() + jacobsthalDiff - 1;
        long int boundIndex = currJacobsthal + insertedNums;
        while (numOfUnitInsertions--)
        {
            iter_vector::iterator boundIt = main.begin() + boundIndex - offset;
            iter_vector::iterator idx = std::upper_bound(main.begin(), boundIt, *pendIt, compare<vector_t::iterator>);
            iter_vector::iterator inserted = main.insert(idx, *pendIt);
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
        iter_vector::iterator currPend = pend.begin() + i;
        iter_vector::iterator currBound = advanceIter(main.begin(), main.size() - pend.size() + i + hasStraggler);
        iter_vector::iterator idx = std::upper_bound(main.begin(), currBound, *currPend, compare<vector_t::iterator>);
        main.insert(idx, *currPend);
    }

    vector_t copy;
    copy.reserve(_vector.size());
    for (iter_vector::iterator it = main.begin(); it != main.end(); it++)
    {
        for (int i = 0; i < unitSize; i++)
        {
            vector_t::iterator unitStart = *it;
            std::advance(unitStart, -unitSize + i + 1);
            copy.insert(copy.end(), *unitStart);
        }
    }

    vector_t::iterator containerIt = _vector.begin();
    vector_t::iterator copyIt = copy.begin();
    while (copyIt != copy.end())
    {
        *containerIt = *copyIt;
        containerIt++;
        copyIt++;
    }
}