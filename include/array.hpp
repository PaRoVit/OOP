#pragma once

#include "figures.hpp"

#include <iostream>

namespace lab3 {

class Array {
private:
    size_t pSize, capacity;
    Figure** data;

    void setCapacity(size_t value);

    static Figure** reallocate(Figure** oldData, size_t oldSize, size_t newSize);

public:

    Array();
    Array(size_t n);
    ~Array();

    Array(const Array&);
    Array(Array&&);

    Figure* & operator[] (size_t ind);
    Figure* const & operator[] (size_t ind) const;

    size_t size() const;
    void resize(size_t newSize);
    void pushBack(Figure* figure);
    void erase(size_t ind);
};

}