#include "../include/figures.hpp"


Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) {
    if ((point3.x - point1.x) * (point2.y - point1.y) == (point2.x - point1.x) * (point3.y - point1.y)) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
    this->point3 = point3;
}

Triangle::Triangle(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
}

Triangle::Triangle(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
}

Triangle& Triangle::operator=(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
    return *this;
}

Triangle& Triangle::operator=(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
    return *this;
}

Triangle::operator double () const {
    double a = Point::distance(point1, point2);
    double b = Point::distance(point2, point3);
    double c = Point::distance(point3, point1);
    double p = (a + b + c) / 2;  
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

Point Triangle::geometricCenter() const {
    return Point{(point1.x + point2.x + point3.x) / 3, 
                 (point1.y + point2.y + point3.y) / 3};
}

bool Triangle::operator==(const Triangle &other) {
    return point1 == other.point1 && point2 == other.point2 && point3 == other.point3;
}

std::ostream& operator<<(std::ostream &stream, const Triangle &tr) {
    stream << "Triangle[ " << tr.point1 << ", " << tr.point2 << ", " << tr.point3 << " ]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Triangle &tr) {
    Point p1, p2, p3;
    stream >> p1 >> p2 >> p3;
    tr = Triangle(p1, p2, p3);
    return stream;
}

Square::Square(const Point& point1, const Point& point2) {
    if ((std::abs(std::abs(point1.x - point2.x) - std::abs(point1.y - point2.y)) >= EPS) || 
        (std::abs(point1.x - point2.x) <= EPS && std::abs(point1.y - point2.y) <= EPS)) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
}

Square::Square(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}

Square::Square(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}

Square& Square::operator=(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}

Square& Square::operator=(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}

Square::operator double () const {
    return std::pow(Point::distance(point1, point2), 2) / 2;
}

Point Square::geometricCenter() const {
    return Point::mid(point1, point2);
}

bool Square::operator==(const Square &other) {
    return point1 == other.point1 && point2 == other.point2;
}

std::ostream& operator<<(std::ostream &stream, const Square &sq) {
    double deltaX = sq.point2.x - sq.point1.x, deltaY = sq.point2.y - sq.point1.y; 
    stream << "Square[ " << sq.point1 << ", " << sq.point1 + Point{deltaX, 0} << ", " <<
              sq.point1 + Point{0, deltaY} << ", " << sq.point2 << " ]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Square &sq) {
    Point p1, p2;
    stream >> p1 >> p2;
    sq = Square(p1, p2);
    return stream;
}

Rectangle::Rectangle(const Point& point1, const Point& point2) {
    if (abs(point1.x - point2.x) <= EPS || abs(point1.y - point2.y) <= EPS ) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
}

Rectangle::Rectangle(const Rectangle &rect) {
    point1 = rect.point1;
    point2 = rect.point2;
}

Rectangle::Rectangle(Rectangle &&rect) {
    point1 = rect.point1;
    point2 = rect.point2;
}

Rectangle& Rectangle::operator=(const Rectangle &rect) {
    point1 = rect.point1;
    point2 = rect.point2;
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle &&rect) {
    point1 = rect.point1;
    point2 = rect.point2;
    return *this;
}

Rectangle::operator double () const {
    return abs(point1.y - point2.y) * abs(point1.x - point2.x);
}

Point Rectangle::geometricCenter() const {
    return Point{(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
}

bool Rectangle::operator==(const Rectangle &other) {
    return point1 == other.point1 && point2 == other.point2;
}

std::ostream& operator<<(std::ostream &stream, const Rectangle &rect) {
    stream << "Rectangle[ " << rect.point1 << ", " << rect.point1 + Point{Point::distance(rect.point1, rect.point2), 0} << ", " <<
              rect.point2 << ", " << rect.point1 + Point{0, Point::distance(rect.point1, rect.point2)} << " ]";
    return stream;
}

std::istream& operator>>(std::istream &stream, Rectangle &rect) {
    Point p1, p2;
    stream >> p1 >> p2;
    rect = Rectangle(p1, p2);
    return stream;
}