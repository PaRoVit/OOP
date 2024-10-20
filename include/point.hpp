#pragma once

#include <iostream>
#include <vector>
#include <cmath>

inline const double EPS = 1e-6;


template <typename T>
class Point {
public:
    T x, y;

    Point() : x(0), y(0) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}

    // расстояние между точками
    static T distance(const Point<T> &p1, const Point<T> &p2) {
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    // середина между точками
    static Point<T> mid(const Point<T> &p1, const Point<T> &p2) {
        return Point<T>{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    }
};

template <typename T>
Point<T> operator+(const Point<T> &p1, const Point<T> &p2) {
    return Point<T>{p1.x + p2.x, p1.y + p2.y};
}

// унарный минус
template <typename T>
Point<T> operator-(const Point<T> &p) {
    return Point<T>{-p.x, -p.y};
}

// вычитание при помощи унарного минуса
template <typename T>
Point<T> operator-(const Point<T> &p1, const Point<T> &p2) {
    return p1 + (-p2);
}

// умножение на скаляр
template <typename T>
Point<T> operator*(const Point<T> &p, const T l) {
    return Point<T>{p.x * l, p.y * l};
}

// умножение на скаляр 
template <typename T>
Point<T> operator*(const T l, const Point<T> &p) {
    return p * l;
}

template <typename T>
bool operator==(const Point<T> &p1, const Point<T> &p2) {
    return (std::abs(p1.x - p2.x) < EPS) && (std::abs(p1.y - p2.y) < EPS);
}

template <typename T>
bool operator<(const Point<T> &p1, const Point<T> &p2) {
    if (p1.x == p2.x) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

template <typename T>
std::ostream& operator<<(std::ostream &stream, const Point<T> &p) {
    stream << "(" << p.x << "; " << p.y << ")";
    return stream;
}

template <typename T>
std::istream& operator>>(std::istream &stream, Point<T> &p) {
    stream >> p.x >> p.y;
    return stream;
}