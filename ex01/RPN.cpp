#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

static bool validChar(const std::string &input)
{
    if (input.find_first_not_of("0123456789") == std::string::npos) // find_first_not_of returns npos if all characters are in the set
        return true;
    else if (input.find_first_not_of("+-*/") == std::string::npos)
        return true;
    return false;
}

static bool validNum(double num)
{
    if (num < 0 || num > 9)
        return false;
    return true;
}

static bool isOperator(const std::string &input)
{
    if (input == "+" || input == "-" || input == "*" || input == "/")
        return true;
    return false;
}

static bool isOperand(const std::string &input)
{
    if (input.find_first_not_of("0123456789") == std::string::npos)
        return true;
    return false;
}

static double ft_stod(const std::string &input)
{
    double num = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        num = num * 10 + (input[i] - '0');
    }
    return num;
}

void RPN::calculate(const std::string &input)
{
    std::istringstream ss(input);
    std::string token;
    double num;

    while (ss >> token)
    {
        if (!validChar(token))
        {
            std::cerr << "Error: Invalid character in input." << std::endl;
            return;
        }

        if (isOperand(token))
        {
            num = ft_stod(token);
            if (!validNum(num))
            {
                std::cerr << "Error: Invalid number in input." << std::endl;
                return;
            }
            _stack.push(num);
        }

        if (isOperator(token))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error: Not enough operands for operator." << std::endl;
                return;
            }
            double b = _stack.top();
            _stack.pop();
            double a = _stack.top();
            _stack.pop();
            double result;

            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else if (token == "/")
            {
                if (b == 0)
                {
                    std::cerr << "Error: Division by zero." << std::endl;
                    return;
                }
                result = a / b;
            }
            _stack.push(result);
        }
    }

    if (_stack.size() != 1)
    {
        std::cerr << "Error: Too many operands left after processing." << std::endl;
        return;
    }
    std::cout << _stack.top() << std::endl;
}