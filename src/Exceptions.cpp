

#include "Exceptions.hpp"

const char* Exceptions::StackIsEmpty::what() const noexcept
{
    return std::runtime_error::what();
}

Exceptions::StackIsEmpty::StackIsEmpty() : std::range_error("Stack is empty")
{}

const char* Exceptions::StackHasLessTwoElements::what() const noexcept
{
    return std::runtime_error::what();
}

Exceptions::StackHasLessTwoElements::StackHasLessTwoElements() : std::range_error("Stack has less than 2 elements")
{}

const char* Exceptions::Underflow::what() const noexcept
{
    return std::runtime_error::what();
}

Exceptions::Underflow::Underflow() : std::underflow_error("Underflow")
{
}


const char* Exceptions::Overflow::what() const noexcept
{
    return std::runtime_error::what();
}

Exceptions::Overflow::Overflow() : std::overflow_error("Overflow")
{
}

const char* Exceptions::DivideZero::what() const noexcept
{
    return std::logic_error::what();
}

Exceptions::DivideZero::DivideZero() :  std::invalid_argument("Cant divide by zero")
{

}

const char* Exceptions::ModuleZero::what() const noexcept
{
    return std::logic_error::what();
}

Exceptions::ModuleZero::ModuleZero() :  std::invalid_argument("Cant module by zero")
{

}