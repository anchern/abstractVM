

#include <vector>
#include <regex>
#include "Calculator.hpp"
#include "Exceptions.hpp"

namespace
{
    void    error(const std::string &string)
    {
        throw std::overflow_error(string);
    }

    template <class T>
    void    stackPop(std::stack<T> &stack)
    {
        if (!stack.empty())
            stack.pop();
        else
            error("Seems you try to crash me)");
    }

    template <class T>
    T stackTop(std::stack<T> &stack)
    {
        if (!stack.empty())
            return stack.top();
        else
            error("Seems you try to crash me)");
        return stack.top();
    }


    void    vectorPopBack(std::vector<SignOrNumber *> &input)
    {
        if (!input.empty())
            input.pop_back();
        else
            error("Seems you try to crash me)");
    }


    int checkSignedNumber(std::string &input, size_t i)
    {
        Sign sign;
        size_t  j;

        j = i;
        if (input[j] == ')' || input[j] == '(')
            return 2;
        if (i > 0)
            i--;
        while (i > 0 && input[i] == ' ')
            i--;
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            if (j + 1 < input.size() && isdigit(input[j + 1]))
            {
                if (input[j] == '+' || input[j] == '-')
                    return 1;
                return 0;
            }
            return 0;
        }
        return 2;
    }

    void skipNumber(std::string &input, size_t  &i)
    {
        while ((isdigit(input[i]) == 1 || input[i] == '.') && input[i] != ' ' &&  i < input.length())
            i++;
        if (input[i] != ' ')
            i--;
    }

    double   returnNumberAfterOperation(const double &number1, const double &number2, char sign)
    {
        if (sign == '^')
            return pow(number1, number2);
        if (sign == '+')
            return number1 + number2;
        if (sign == '-')
            return number2 - number1;
        if (sign == '*')
            return number1 * number2;
        if (sign == '/')
        {
            if (number1 == double(0))
            {
                throw Exceptions::DivideZero();
            }
            return number2 / number1;
        }
        return 0;
    }

    void bracketStuff(std::stack<SignOrNumber *> &operandStack, std::stack<SignOrNumber *> &mainStack)
    {
        SignOrNumber *topString = nullptr;

        topString = stackTop(operandStack);
        while (topString->getValue() != '(')
        {
            mainStack.push(topString);
            stackPop(operandStack);
            topString = stackTop(operandStack);
        }
        stackPop(operandStack);
    }

    void    checkAndPushNumber(std::stack<SignOrNumber *> &mainStack, std::string &input, size_t  &i)
    {
        size_t kek;
        std::string tmp = R"((\+|\-)?0*\.0{324,}[1-9]+)";
        std::regex regularkek(tmp);
        std::cmatch result;

        try
        {
            mainStack.push(new Number(std::stod(input.c_str() + i, &kek)));
        }
        catch (std::exception &e)
        {
            if (std::regex_match(input.c_str() + i, result, regularkek))
                throw std::logic_error("Value so small");
            if ((input.c_str() + i)[0] != '-')
                throw (Exceptions::Overflow());
            else
                throw (Exceptions::Underflow());
        }
    }

    void signStuff(std::stack<SignOrNumber *> &operandStack, std::stack<SignOrNumber *> &mainStack, size_t  &i, std::string &input)
    {
        SignOrNumber *tmpString = nullptr;
        Sign *sign1 = nullptr;
        Sign sign2;

        if (checkSignedNumber(input, i) == 1)
        {
            checkAndPushNumber(mainStack, input, i);
            i++;
            skipNumber(input, i);
            return;
        }
        else if (checkSignedNumber(input, i) == 0)
            error("Something went wrong");
        if (!operandStack.empty())
        {
            tmpString = stackTop(operandStack);
            sign1 = dynamic_cast<Sign *>(tmpString);
            sign2.setValue(input[i]);
            if (sign2 <= *sign1 && input[i] != '(')
            {
                mainStack.push(tmpString);
                stackPop(operandStack);
            }
        }
        sign1 = new Sign(input[i]);
        operandStack.push(static_cast<SignOrNumber *>(sign1));
    }

    std::vector<SignOrNumber *> makeResult(std::stack<SignOrNumber *> &operandStack, std::stack<SignOrNumber *> &mainStack)
    {
        std::vector<SignOrNumber *> result;

        while (!operandStack.empty())
        {
            mainStack.push(operandStack.top());
            operandStack.pop();
        }
        while (!mainStack.empty())
        {
            result.push_back(mainStack.top());
            mainStack.pop();
        }
        return result;
    }


}

std::vector<SignOrNumber *> Calculator::createPolishString(std::string &input)
{
    std::stack<SignOrNumber *> mainStack;
    std::stack<SignOrNumber *> operandStack;
    Sign sign2;

    for (size_t  i = 0; i < input.length(); i++)
    {
        if (input[i] == ')')
        {
            bracketStuff(operandStack, mainStack);
            continue;
        }
        if (sign2.checkSign(input[i]))
        {
            signStuff(operandStack, mainStack, i , input);
            continue;
        }
        if (input[i] == ' ')
            continue;
        if (isdigit(input[i]))
            {
                checkAndPushNumber(mainStack, input, i);
                skipNumber(input, i);
            }
    }
    return makeResult(operandStack, mainStack);
}

double    Calculator::calculatePolishString(std::string &string)
{
    std::stack<double > mainStack;
    std::vector<SignOrNumber *> input;
    double  tmp1;
    double  tmp2;
    Sign sign1;

    input = createPolishString(string);
    while (!input.empty())
    {
        if (!input[input.size() - 1]->getType())
        {
            tmp1 = stackTop(mainStack);
            stackPop(mainStack);
            tmp2 = stackTop(mainStack);
            stackPop(mainStack);
            mainStack.push(returnNumberAfterOperation(tmp1, tmp2, static_cast<char>(input[input.size() - 1]->getValue())));
            vectorPopBack(input);
            continue;
        }
        if (input[input.size() - 1]->getType())
        {
            mainStack.push(input[input.size() - 1]->getValue());
            vectorPopBack(input);
        }
    }
    return stackTop(mainStack);
}
