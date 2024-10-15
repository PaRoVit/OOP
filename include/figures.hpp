#pragma once

#include "point.hpp"

#include <algorithm>


class Figure {
public:
    virtual ~Figure() {};
    virtual Figure* clone() const = 0;
    virtual Point geometricCenter() const = 0;
    virtual operator double () const = 0; 
};

class Triangle : public Figure {
private:
    Point point1, point2, point3;
public:
    Triangle() = default;
    Triangle(const Point& point1, const Point& point2, const Point& point3);
    Triangle(const Triangle &tr);
    Triangle(Triangle &&tr);
    
    Triangle& operator=(const Triangle &tr);
    Triangle& operator=(Triangle &&tr);

    bool operator==(const Triangle &other);

    operator double () const override;
    Point geometricCenter() const override;

    Triangle* clone() const override {
        return new Triangle(*this);
    }

    friend std::ostream& operator<<(std::ostream &stream, const Triangle &sq);
    friend std::istream& operator>>(std::istream &stream, Triangle &sq);   
};

class Square : public Figure {
private:
    Point point1, point2;
public:
    Square() = default;
    Square(const Point& point1, const Point& point2);
    Square(const Square &sq);
    Square(Square &&sq);
    
    Square& operator=(const Square &sq);
    Square& operator=(Square &&sq);

    bool operator==(const Square &other);

    operator double () const override;
    Point geometricCenter() const override;

    Square* clone() const override {
        return new Square(*this); 
    }

    friend std::ostream& operator<<(std::ostream &stream, const Square &sq);
    friend std::istream& operator>>(std::istream &stream, Square &sq);
};

class Rectangle : public Figure {
private:
    Point point1, point2;
public:
    Rectangle() = default;
    Rectangle(const Point& point1, const Point& point2);
    Rectangle(const Rectangle &rect);
    Rectangle(Rectangle &&rect);
    
    Rectangle& operator=(const Rectangle &rect);
    Rectangle& operator=(Rectangle &&rect);

    bool operator==(const Rectangle &other);

    operator double () const override;
    Point geometricCenter() const override;

    Rectangle* clone() const override {
        return new Rectangle(*this); 
    }

    friend std::ostream& operator<<(std::ostream &stream, const Rectangle &rect);
    friend std::istream& operator>>(std::istream &stream, Rectangle &rect);
};