#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>

class Four
{
public:
    Four();                                              // Default constructor
    size_t getSize() const;
    unsigned char *getNumber() const;

    Four(const size_t &n, unsigned char t = 0);          // Fill constructor
    Four(const std::initializer_list<unsigned char> &t); // Initializer list constructor
    Four(const std::string t);                           // Copy string constructor
    Four(const Four &other);                             // Copy constructor
    Four(Four &&other) noexcept;                         // Move constructor

    std::ostream &print(std::ostream &os);

    Four& operator=(Four&& other) noexcept;                   // Assignment operator (=)
    Four operator+(const Four &other) const;             // Addition operator (+)
    Four operator-(const Four &other) const;             // Substraction operator (-)
    Four operator*(const Four &other) const;             // Multiplication operator (*)
    bool operator==(const Four &other) const;            // Equal operator (==)
    bool operator!=(const Four &other) const;            // Not equal operator (!=)
    bool operator<(const Four &other) const;             // Less operator (<)
    bool operator<=(const Four &other) const;            // Less or equal operator (<=)
    bool operator>(const Four other) const;              // Greater operator (>)
    bool operator>=(const Four other) const;             // Greater or equal operator (>=)

    ~Four() noexcept; //* Destructor
private:
    size_t size;
    unsigned char *number;
};

bool isFourDigit(const char &c);