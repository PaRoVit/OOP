#include "../include/array.hpp"


Array::Array() : _size(0), capacity(2) {
    data = std::make_unique<Figure*[]>(capacity);
}

Array::Array(const Array& other) : _size(other._size), capacity(other.capacity) {
    data = std::make_unique<Figure*[]>(capacity);
    for (size_t i = 0; i < _size; i++) {
        data[i] = other.data[i]->clone(); 
    }
}

Array::Array(Array&& other) noexcept : _size(other._size), capacity(other.capacity), data(std::move(other.data)) {
    other._size = 0;
    other.capacity = 0;
}

Array::~Array() {
    for (size_t i = 0; i < _size; i++) {
        delete data[i]; 
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        for (size_t i = 0; i < _size; i++) {
            delete data[i];
        }

        _size = other._size;
        capacity = other.capacity;
        data = std::make_unique<Figure*[]>(capacity);

        for (size_t i = 0; i < _size; i++) {
            data[i] = other.data[i]->clone();
        }
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < _size; i++) {
            delete data[i]; 
        }

        _size = other._size;
        capacity = other.capacity;
        data = std::move(other.data); 
        other._size = 0;
        other.capacity = 0;
    }
    return *this;
}

size_t Array::size() const {
    return _size; 
}

void Array::pushBack(Figure* fig) {
    if (_size == capacity) {
        resize(capacity * 2); 
    }
    data[_size++] = fig; 
}

void Array::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range."); 
    }
    delete data[index]; 
    for (size_t i = index; i < _size - 1; i++) {
        data[i] = data[i + 1]; 
    }
    _size--; 
}

Figure* Array::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index]; 
}

void Array::resize(size_t newSize) {
    auto newData = std::make_unique<Figure*[]>(newSize); 
    for (size_t i = 0; i < _size; i++) {
        newData[i] = data[i]; 
    }
    data = std::move(newData); 
    capacity = newSize; 
}