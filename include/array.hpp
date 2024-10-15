#pragma once

#include "figures.hpp"

#include <iostream>
#include <memory>


class Array {
private:
    std::unique_ptr<Figure*[]> data; // Умный указатель для управления динамическим массивом
    size_t _size;                     // Текущее количество фигур
    size_t capacity;                  // Вместимость массива

    void resize(size_t newSize);      // Изменение размера массива

public:
    Array();                          // Конструктор
    Array(const Array& other);        // Конструктор копирования
    Array(Array&& other) noexcept;    // Конструктор перемещения
    ~Array();                         // Деструктор

    Array& operator=(const Array& other); // Присваивание копированием
    Array& operator=(Array&& other) noexcept; // Присваивание перемещением

    size_t size() const;              // Возвращает текущее количество фигур
    void pushBack(Figure* fig);       // Добавляет фигуру
    void erase(size_t index);         // Удаляет фигуру по индексу
    Figure* operator[](size_t index) const; // Получение фигуры по индексу
};

