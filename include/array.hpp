#pragma once

#include <iostream>
#include <memory>

template <typename T>
class Array {
private:
    std::unique_ptr<T[]> data;  // Умный указатель для динамического массива
    size_t _size;               // Текущее количество элементов
    size_t capacity;            // Вместимость массива

    void resize(size_t newSize); // Изменение размера массива

public:
    Array();                             // Конструктор
    Array(const Array& other);           // Конструктор копирования
    Array(Array&& other) noexcept;       // Конструктор перемещения
    ~Array();                            // Деструктор

    Array& operator=(const Array& other);    // Присваивание копированием
    Array& operator=(Array&& other) noexcept; // Присваивание перемещением

    size_t size() const;               // Возвращает текущее количество элементов
    void pushBack(const T& elem);      // Добавляет элемент
    void erase(size_t index);          // Удаляет элемент по индексу
    T& operator[](size_t index) const; // Получение элемента по индексу
};

// Конструктор
template <typename T>
Array<T>::Array() : _size(0), capacity(2) {
    data = std::make_unique<T[]>(capacity);
}

// Конструктор копирования
template <typename T>
Array<T>::Array(const Array& other) : _size(other._size), capacity(other.capacity) {
    data = std::make_unique<T[]>(capacity);
    for (size_t i = 0; i < _size; i++) {
        data[i] = other.data[i];  // Копируем элементы
    }
}

// Конструктор перемещения
template <typename T>
Array<T>::Array(Array&& other) noexcept : _size(other._size), capacity(other.capacity), data(std::move(other.data)) {
    other._size = 0;
    other.capacity = 0;
}

// Деструктор
template <typename T>
Array<T>::~Array() {
    // Удалять элементы не нужно, так как unique_ptr автоматически очистит память
}

// Присваивание копированием
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        _size = other._size;
        capacity = other.capacity;
        data = std::make_unique<T[]>(capacity);

        for (size_t i = 0; i < _size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Присваивание перемещением
template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        _size = other._size;
        capacity = other.capacity;
        data = std::move(other.data);
        other._size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Возвращает размер
template <typename T>
size_t Array<T>::size() const {
    return _size;
}

// Добавление элемента
template <typename T>
void Array<T>::pushBack(const T& elem) {
    if (_size == capacity) {
        resize(capacity * 2);  // Увеличиваем массив при необходимости
    }
    data[_size++] = elem;  // Добавляем элемент
}

// Удаление элемента по индексу
template <typename T>
void Array<T>::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    for (size_t i = index; i < _size - 1; i++) {
        data[i] = data[i + 1];  // Сдвиг элементов
    }
    _size--;
}

// Получение элемента по индексу
template <typename T>
T& Array<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

// Изменение размера массива
template <typename T>
void Array<T>::resize(size_t newSize) {
    auto newData = std::make_unique<T[]>(newSize);
    for (size_t i = 0; i < _size; i++) {
        newData[i] = data[i];  // Перенос данных
    }
    data = std::move(newData);
    capacity = newSize;
}
