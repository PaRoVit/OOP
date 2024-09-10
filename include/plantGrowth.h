#pragma once

#include <stdexcept>

class NegativeValueException : public std::invalid_argument {
public:
    NegativeValueException() : 
        std::invalid_argument("incorrect input, height must be greater than 0") {}
};

class InvalidRangeException : public std::out_of_range {
public:
    InvalidRangeException() : 
        std::out_of_range("incorrect input, the upward growth should be greater than the downward growth") {}
};

int plantGrowth(int upSpeed, int downSpeed, int desiredHeight);
