#pragma once

#include <iostream>
#include <vector>
#include <cmath>

inline const double EPS = 1e-6;


struct Point {
    double x, y;
    // расстояние между точками 
    static double distance(const Point &p1, const Point &p2) {
        return std::sqrt(std::pow(p2.x - p1.x, 2) +
                         std::pow(p2.y - p1.y, 2));
    }

    // середина между точками
    static Point mid(const Point &p1, const Point &p2) {
        return Point{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    }
};

Point operator+(const Point &p1, const Point &p2);
Point operator-(const Point &p);
Point operator-(const Point &p1, const Point &p2);
Point operator*(const Point &p, const double x);
Point operator*(const double x, const Point &p);
bool operator==(const Point &p1, const Point &p2);
bool operator<(const Point &p1, const Point &p2);
std::ostream& operator<<(std::ostream &stream, const Point &p);
std::istream& operator>>(std::istream &stream, Point &p);