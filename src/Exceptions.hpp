
#pragma once

#include "string"

class Exceptions {

public:
    class StackIsEmpty : public std::range_error
    {
    public:
        explicit StackIsEmpty();
        const char    *what() const noexcept override;
    };

    class StackHasLessTwoElements : public std::range_error
    {
    public:
        explicit StackHasLessTwoElements();
        const char    *what() const noexcept override;
    };

    class Overflow : public std::overflow_error
    {
    public:
        explicit Overflow();
        const char    *what() const noexcept override;
    };

    class Underflow : public std::underflow_error
    {
    public:
        explicit Underflow();
        const char    *what() const noexcept override;
    };

class DivideZero : public std::invalid_argument
    {
    public:
        explicit DivideZero();
        const char    *what() const noexcept override;
    };

    class ModuleZero : public std::invalid_argument
    {
    public:
        explicit ModuleZero();
        const char    *what() const noexcept override;
    };
};



