#include "../include/Four.hpp"

bool isFourDigit(const char &c)
{
    return ('0' <= c && c <= '3');
}

Four::Four() : size(0), number{nullptr}
{
}

size_t Four::getSize() const
{
    return size;
}

unsigned char *Four::getNumber() const
{
    return number;
}

Four::Four(const size_t &n, unsigned char t)
{
    // std::cout << "Fill constructor" << std::endl;
    number = new unsigned char[n];
    for (size_t i = 0; i < n; i++)
        number[i] = t;
    size = n;
}

Four::Four(const std::initializer_list<unsigned char> &t)
{
    // std::cout << "Initializer list constructor" << std::endl;
    number = new unsigned char[t.size()];
    size = t.size();
    size_t i{size};
    for (unsigned char c : t)
    {
        if (!isFourDigit(c))
        {
            throw std::logic_error("Four digit must be between 0 and 3");
        }
        number[--i] = c;
    }
}

Four::Four(const std::string t)
{
    // std::cout << "Copy string constructor" << std::endl;
    size = t.size();
    number = new unsigned char[size];
    for (size_t i = size - 1, j = 0; j < size; i--, j++)
    {
        if (!isFourDigit(t[i]))
        {
            throw std::logic_error("Four digit must be between 0 and 3");
        }
        number[i] = t[j];
    }
}

Four::Four(const Four &other)
{
    // std::cout << "Copy constructor" << std::endl;
    size = other.size;
    number = new unsigned char[size];
    for (size_t i = 0; i < size; i++)
    {
        number[i] = other.number[i];
    }
}

Four::Four(Four &&other) noexcept
{
    // std::cout << "Move constructor" << std::endl;
    size = other.size;
    number = other.number;  

    other.size = 0;
    other.number = nullptr;
}

// operators

Four Four::operator=(const Four &other)
{
    if (&other != this)
    {
        delete[] number;
        size = other.size;
        number = new unsigned char[size];
        for (size_t i = 0; i < size; i++)
        {
            number[i] = other.number[i];
        }
    }
    return *this;
}

Four Four::operator+(const Four &other) const
{
    size_t resultSize = std::max(other.size, size) + 1;
    std::string result(resultSize, '0');
    int carry = 0;
    for (size_t i = 0; i < resultSize; i++)
    {
        int d1 = (i < size) ? (number[i] - '0') : 0;
        int d2 = (i < other.size) ? (other.number[i] - '0') : 0;

        int sum = d1 + d2 + carry;
        result[i] = (sum % 4) + '0';
        carry = sum / 4;
    }
    if (carry > 0)
    {
        result[resultSize - 1] = carry + '0';
    }
    if (result[resultSize - 1] == '0')
    {
        result.erase(resultSize - 1, 1);
    }
    std::reverse(result.begin(), result.end());
    return Four(result);
}

Four Four::operator-(const Four &other) const
{
    if (*this < other)
    {
        throw std::logic_error("Difference can't be negative");
    }
    size_t resultSize = std::max(other.size, size) + 1;
    std::string result(resultSize, '0');
    int carry = 0;
    for (size_t i = 0; i < resultSize; i++)
    {
        int d1 = (i < size) ? (number[i] - '0') : 0;
        int d2 = (i < other.size) ? (other.number[i] - '0') : 0;

        int diff = d1 - d2 - carry;
        if (diff < 0)
        {
            diff +=4 ;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        result[i] = diff + '0';
    }
    size_t nonZeroPos = result.find_last_not_of('0');
    if (nonZeroPos != std::string::npos)
    {
        result.erase(nonZeroPos + 1);
    }
    else
    {
        result = "0";
    }
    std::reverse(result.begin(), result.end());
    return Four(result);
}

Four Four::operator*(const Four &other) const
{
    size_t resultSize = size + other.size;  // Максимальный возможный размер результата
    std::string result(resultSize, '0');    // Строка для хранения результата, заполненная нулями

    // Выполняем умножение "в столбик"
    for (size_t i = 0; i < size; i++)
    {
        int d1 = number[i] - '0';  // Первая цифра для умножения
        int carry = 0;  // Перенос для сложения

        for (size_t j = 0; j < other.size; j++)
        {
            int d2 = other.number[j] - '0';  // Вторая цифра для умножения
            int product = d1 * d2 + (result[i + j] - '0') + carry;  // Промежуточное произведение с переносом

            result[i + j] = (product % 4) + '0';  // Сохраняем остаток от деления на 4 как цифру
            carry = product / 4;  // Остаток для переноса
        }

        if (carry > 0)
        {
            result[i + other.size] += carry;  // Добавляем перенос на следующую позицию
        }
    }
    size_t nonZeroPos = result.find_last_not_of('0');
    if (nonZeroPos != std::string::npos)
    {
        result.erase(nonZeroPos + 1);
    }
    else
    {
        result = "0";
    }
    std::reverse(result.begin(), result.end());
    return Four(result);
}

bool Four::operator==(const Four &other) const
{
    if (size != other.size)
    {
        return false;
    }
    for (size_t i = 0; i < size; i++)
    {
        if (number[i] != other.number[i])
        {
            return false;
        }
    }
    return true;
}

bool Four::operator!=(const Four &other) const
{
    if (*this == other)
    {
        return false;
    }
    return true;
}

bool Four::operator<(const Four &other) const
{
    if (&other == this)
    {
        return false;
    }

    if (size < other.size)
    {
        return true;
    }
    else if (size > other.size)
    {
        return false;
    }
    else
    {
        for (size_t i = size; i--;)
        {
            if (number[i] < other.number[i])
            {
                return true;
            }
            else if (number[i] > other.number[i])
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        return false;
    }
}

bool Four::operator<=(const Four &other) const
{
    if (*this > other)
    {
        return false;
    }
    return true;
}

bool Four::operator>(const Four other) const
{
    if (*this < other || *this == other)
    {
        return false;
    }
    return true;
}

bool Four::operator>=(const Four other) const
{
    if (*this < other)
    {
        return false;
    }
    return true;
}

std::ostream &Four::print(std::ostream &os)
{
    for (size_t i = size; i--;)
    {
        os << number[i];
    }
    os << std::endl;
    return os;
}

Four::~Four() noexcept
{
    if (size > 0)
    {
        size = 0;
        delete[] number;
        number = nullptr;
    }
}