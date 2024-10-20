#pragma once

#include "point.hpp"

#include <algorithm>

template <typename T>
class Figure {
public:
    virtual ~Figure() {};
    virtual Figure* clone() const = 0;
    virtual Point<T> geometricCenter() const = 0;
    virtual operator double () const = 0; 
};

template <typename T>
class Triangle : public Figure<T> {
private:
    Point<T> point1, point2, point3;
public:
    Triangle() = default;
    Triangle(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3) {
        if ((point3.x - point1.x) * (point2.y - point1.y) == (point2.x - point1.x) * (point3.y - point1.y)) {
            throw std::invalid_argument("Bad points.");
        }
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;
    }

    Triangle(const Triangle &tr) = default;
    Triangle(Triangle &&tr) = default;
    
    Triangle& operator=(const Triangle &tr) = default;
    Triangle& operator=(Triangle &&tr) = default;

    bool operator==(const Triangle<T> &other) {
        return point1 == other.point1 && point2 == other.point2 && point3 == other.point3;
    }

    operator T () const override{
        T a = Point<T>::distance(point1, point2);
        T b = Point<T>::distance(point2, point3);
        T c = Point<T>::distance(point3, point1);
        T p = (a + b + c) / 2;  
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    Point<T> geometricCenter() const {
        return Point<T>{(point1.x + point2.x + point3.x) / 3, 
                    (point1.y + point2.y + point3.y) / 3};
    }

    Triangle* clone() const override {
        return new Triangle(*this);
    }

    friend std::ostream& operator<<(std::ostream &stream, const Triangle<T> &tr) {
        stream << "Triangle[ " << tr.point1 << ", " << tr.point2 << ", " << tr.point3 << " ]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Triangle<T> &tr) {
        Point<T> p1, p2, p3;
        stream >> p1 >> p2 >> p3;
        tr = Triangle<T>(p1, p2, p3);
        return stream;
    }  
};

template <typename T>
class Square : public Figure<T> {
private:
    Point<T> point1, point2;
public:
    Square() = default;

    Square(const Point<T>& point1, const Point<T>& point2) {
        if ((std::abs(std::abs(point1.x - point2.x) - std::abs(point1.y - point2.y)) >= EPS) || 
            (std::abs(point1.x - point2.x) <= EPS && std::abs(point1.y - point2.y) <= EPS)) {
            throw std::invalid_argument("Bad points.");
        }

        this->point1 = point1;
        this->point2 = point2;
    }

    Square(const Square &sq) = default;

    Square(Square &&sq) = default;
    
    Square& operator=(const Square &sq) = default;

    Square& operator=(Square &&sq) = default;

    bool operator==(const Square<T> &other) {
        return point1 == other.point1 && point2 == other.point2;
    }

    operator T () const override{
        return std::pow(Point<T>::distance(point1, point2), 2) / 2;
    }

    Point<T> geometricCenter() const {
        return Point<T>::mid(point1, point2);
    }

    Square* clone() const override {
        return new Square(*this); 
    }

    friend std::ostream& operator<<(std::ostream &stream, const Square<T> &sq) {
        T deltaX = sq.point2.x - sq.point1.x, deltaY = sq.point2.y - sq.point1.y; 
        stream << "Square[ " << sq.point1 << ", " << sq.point1 + Point<T>{deltaX, 0} << ", " <<
                sq.point1 + Point<T>{0, deltaY} << ", " << sq.point2 << " ]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Square<T> &sq) {
        Point<T> p1, p2;
        stream >> p1 >> p2;
        sq = Square<T>(p1, p2);
        return stream;
    }
};

template <typename T>
class Rectangle : public Figure<T> {
private:
    Point<T> point1, point2;
public:
    Rectangle() = default;

    Rectangle(const Point<T>& point1, const Point<T>& point2) {
        if (abs(point1.x - point2.x) <= EPS || abs(point1.y - point2.y) <= EPS ) {
            throw std::invalid_argument("Bad points.");
        }
        this->point1 = point1;
        this->point2 = point2;
    }

    Rectangle(const Rectangle &rect) = default;

    Rectangle(Rectangle &&rect) = default;
    
    Rectangle& operator=(const Rectangle &rect) = default;

    Rectangle& operator=(Rectangle &&rect) = default;

    bool operator==(const Rectangle<T> &other) {
        return point1 == other.point1 && point2 == other.point2;
    }

    operator T () const {
        return abs(point1.y - point2.y) * abs(point1.x - point2.x);
    }

    Point<T> geometricCenter() const {
        return Point<T>{(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
    }

    Rectangle* clone() const override {
        return new Rectangle(*this); 
    }

    friend std::ostream& operator<<(std::ostream &stream, const Rectangle<T> &rect) {
        stream << "Rectangle[ " << rect.point1 << ", " << rect.point1 + Point<T>{Point<T>::distance(rect.point1, rect.point2), 0} << ", " <<
                rect.point2 << ", " << rect.point1 + Point<T>{0, Point<T>::distance(rect.point1, rect.point2)} << " ]";
        return stream;
    }

    friend std::istream& operator>>(std::istream &stream, Rectangle<T> &rect) {
        Point<T> p1, p2;
        stream >> p1 >> p2;
        rect = Rectangle<T>(p1, p2);
        return stream;
    }
};