#include "../include/figures.hpp"

namespace lab3 {

// треугольник
// конструктор через три точки
Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) {
    this->point1 = point1;
    this->point2 = point2;
    this->point3 = point3;
}
// копирующий конструктор
Triangle::Triangle(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
}
// перемещающий конструктор
Triangle::Triangle(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
}
// присваивание копированием
Triangle& Triangle::operator=(const Triangle &tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
    return *this;
}
// присваивание перемещением
Triangle& Triangle::operator=(Triangle &&tr) {
    point1 = tr.point1;
    point2 = tr.point2;
    point3 = tr.point3;
    return *this;
}
// вычисление площади формулой герона
Triangle::operator double () const {
    double a = Point::distance(point1, point2);
    double b = Point::distance(point2, point3);
    double c = Point::distance(point3, point1);
    double p = (a + b + c) / 2;  // полупериметр
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}
// геом центр
Point Triangle::geometricCenter() const {
    return Point{(point1.x + point2.x + point3.x) / 3, 
                 (point1.y + point2.y + point3.y) / 3};
}
// сравнение треугольников
bool Triangle::operator==(const Triangle &other) {
    return point1 == other.point1 && point2 == other.point2 && point3 == other.point3;
}
// оператор вывода
std::ostream& operator<<(std::ostream &stream, const Triangle &tr) {
    stream << "Triangle[ " << tr.point1 << " " << tr.point2 << " " << tr.point3 << " ]";
    return stream;
}
// оператор ввода
std::istream& operator>>(std::istream &stream, Triangle &tr) {
    Point p1, p2, p3;
    stream >> p1 >> p2 >> p3;
    tr = Triangle(p1, p2, p3);
    return stream;
}

// квадрат через 2 точки
// контруктор через 2 точки
Square::Square(const Point& point1, const Point& point2) {
    // проверка что это действительно квадрат
    if ((abs(abs(point1.x - point2.x) - abs(point1.y - point2.y)) >= EPS) || (abs(point1.x - point2.x) <= EPS && abs(point1.y - point2.y) <= EPS)) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
}
// копирующий контруктор
Square::Square(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}
// перемещающий конструктор
Square::Square(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
}
// присваивание копированием 
Square& Square::operator=(const Square &sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}
// присваивание перемещением
Square& Square::operator=(Square &&sq) {
    point1 = sq.point1;
    point2 = sq.point2;
    return *this;
}
// площадь через длину диагонали
Square::operator double () const {
    return std::pow(Point::distance(point1, point2), 2) / 2;
}
// геом центр 
Point Square::geometricCenter() const {
    return Point::mid(point1, point2);
}
// сравнение квадратов
bool Square::operator==(const Square &other) {
    return point1 == other.point1 && point2 == other.point2;
}
// оператор вывода
std::ostream& operator<<(std::ostream &stream, const Square &sq) {
    double deltaX = sq.point2.x - sq.point1.x, deltaY = sq.point2.y - sq.point1.y; // вспомогательные значения для нахождения других вершин 
    stream << "Square[ " << sq.point1 << " " << sq.point1 + Point{deltaX, 0} << " " <<
              sq.point1 + Point{0, deltaY} << " " << sq.point2 << " ]";
    return stream;
}
// оператор ввода
std::istream& operator>>(std::istream &stream, Square &sq) {
    Point p1, p2;
    stream >> p1 >> p2;
    sq = Square(p1, p2);
    return stream;
}


// прямоугольник
Rectangle::Rectangle(const Point& point1, const Point& point2) {
    // проверка на несовпадение точек
    if (abs(point1.x - point2.x) <= EPS || abs(point1.y - point2.y) <= EPS ) {
        throw std::invalid_argument("Bad points.");
    }
    this->point1 = point1;
    this->point2 = point2;
}
// копирующий контруктор
Rectangle::Rectangle(const Rectangle &rect) {
    point1 = rect.point1;
    point2 = rect.point2;
}
// перемещающий контруктор
Rectangle::Rectangle(Rectangle &&rect) {
    point1 = rect.point1;
    point2 = rect.point2;
}
// приваивание копированием
Rectangle& Rectangle::operator=(const Rectangle &rect) {
    point1 = rect.point1;
    point2 = rect.point2;
    return *this;
}
// присваивание перемещением
Rectangle& Rectangle::operator=(Rectangle &&rect) {
    point1 = rect.point1;
    point2 = rect.point2;
    return *this;
}
// площадь
Rectangle::operator double () const {
    return abs(point1.y - point2.y) * abs(point1.x - point2.x);
}
// геом центр
Point Rectangle::geometricCenter() const {
    return Point::mid(point1, point2);
}
// сравнение двух прямоугольников
bool Rectangle::operator==(const Rectangle &other) {
    return point1 == other.point1 && point2 == other.point2;
}
// оператор вывода
std::ostream& operator<<(std::ostream &stream, const Rectangle &rect) {
    double deltaX = rect.point2.x - rect.point1.x, deltaY = rect.point2.y - rect.point1.y;
    stream << "Rectangle[ " << rect.point1 << " " << rect.point1 + Point{deltaX, 0} << " " <<
              rect.point1 + Point{0, deltaY} << " " << rect.point2 << " ]";
    return stream;
}
// оператор ввода
std::istream& operator>>(std::istream &stream, Rectangle &rect) {
    Point p1, p2;
    stream >> p1 >> p2;
    rect = Rectangle(p1, p2);
    return stream;
}
} 