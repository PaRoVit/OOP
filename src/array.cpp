#include "../include/array.hpp"

namespace lab3 {
// установка нового размера массива
void Array::setCapacity(size_t value) {
    data = reallocate(data, pSize, value);
    capacity = value;
}
// перераспределение памяти для нового массива
Figure** Array::reallocate(Figure** oldData, size_t oldSize, size_t newSize) {
    Figure** data = new Figure* [newSize]; // выделение нового массива указателей
    for (size_t i = 0; i < std::min(oldSize, newSize); i++) { // копируем всё из старого
        data[i] = oldData[i];
    }
    if (oldData != nullptr) {
        delete [] oldData; // удаляем всё из предыдущего 
    }
    return data;
}
// конструктор пустого массива с нулевыми размерами
Array::Array() : pSize(0), capacity(0), data(nullptr) { }
// контруктор для массива заданного размера
Array::Array(size_t n) : pSize(n), capacity(n) {
    data = reallocate(nullptr, 0, n);
}
// деструктор
Array::~Array() {
    delete [] data;
}
// конструктор копирования
Array::Array(const Array& other) {
    data = reallocate(nullptr, 0, other.size());// выделение новой памяти
    for (size_t i = 0; i < other.size(); i++) {
        data[i] = other.data[i]; // копируем указатели
    }
    pSize = other.size(); // копируем размер
    capacity = other.capacity; // копируем ёмкость 
}

// конструктор перемещения
Array::Array(Array&& other) {
    data = other.data; // перемещение указателя на данные
    pSize = other.size(); // копирует количесво элементов
    capacity = other.capacity; // копируем ёмкость
    other.data = nullptr; // устанавливаем указатель на данные в другом объякте
}
// оператор индексирования для изменения
Figure* & Array::operator[] (size_t ind) {
    return data[ind];
}
// оператор индексирования для чтения
Figure* const & Array::operator[] (size_t ind) const {
    return data[ind];
}
// возврат кол-ва элементов
size_t Array::size() const {
    return pSize;
}
// изменение размера
void Array::resize(size_t newSize) {
    if (newSize > capacity) {
        setCapacity(newSize);
    }
    pSize = newSize;
}
// добавление элемента в к онец
void Array::pushBack(Figure* figure) {
    resize(pSize + 1);
    (*this)[pSize - 1] = figure;
}
// удаление по индексу
void Array::erase(size_t ind) {
    for (size_t i = ind + 1; i < pSize; i++) {
        data[i - 1] = data[i];
    }
    if (ind < pSize) {
        pSize--;
    }
}

}