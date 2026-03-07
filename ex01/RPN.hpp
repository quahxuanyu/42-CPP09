#ifndef RPN_HPP
#define RPN_HPP

#include <algorithm>
#include <stack>
#include <iostream>
#include <sstream>

class RPN
{
    private:
        std::stack<double> _stack;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        void calculate(const std::string &input);
};

#endif