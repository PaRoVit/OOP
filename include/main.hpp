#include "../include/point.hpp"
#include "../include/figures.hpp"
#include "../include/array.hpp"

#include <iostream>

template<typename T>
class MainRoutine {
public:
    Array<Figure<T>*> data;

    void eraseFigure() {
        size_t n;
        std::cin >> n;
        n--;
        if (n >= data.size()) {
            std::cout << "There's no figure with index " << n + 1 << ".\n";
            return ;
        }
        data.erase(n);
    }

    void pushFigure() {
        std::string type;
        std::cin >> type;
        try {
            if (type == "square") {
                Square<T> *sq = new Square<T>();
                std::cin >> *sq;
                data.pushBack(sq);  // Добавляем квадрат
            } else if (type == "triangle") {
                Triangle<T> *tr = new Triangle<T>();
                std::cin >> *tr;
                data.pushBack(tr);  // Добавляем треугольник
            } else if (type == "rectangle") {
                Rectangle<T> *rect = new Rectangle<T>();
                std::cin >> *rect;
                data.pushBack(rect);  // Добавляем прямоугольник
            } else {
                std::cout << "Unknown figure name.\n";
                return;
            }
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "Success.\n";
    }

    void allArea() {
        T area = 0;
        for (size_t i = 0; i < data.size(); i++) {
            area += static_cast<double>(*data[i]);  // Суммируем площади
        }
        std::cout << area << std::endl;
    }

    void info() {
        std::cout << "Info: \n";
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << (i + 1) << ":\n";
            std::cout << "  area : " << static_cast<T>(*data[i]) << "\n"
                    << "  geometric_center : " << data[i]->geometricCenter() << "\n";
            // Вывод информации о фигуре
            if (auto* triangle = dynamic_cast<Triangle<T>*>(data[i])) {
                std::cout << "  " << *triangle;
            } else if (auto* square = dynamic_cast<Square<T>*>(data[i])) {
                std::cout << "  " << *square;
            } else if (auto* rectangle = dynamic_cast<Rectangle<T>*>(data[i])) {
                std::cout << "  " << *rectangle;
            }
            std::cout << "\n";
        }
    }

    void start() {
        std::string command;
        std::cout << "> ";
        std::cin >> command;
        while (command != "exit") {
            if (command == "push") {
                pushFigure();
            } else if (command == "info") {
                info();
            } else if (command == "area") {
                allArea();
            } else if (command == "erase") {
                eraseFigure();
            }
            std::cout << "> ";
            std::cin >> command;
        }
    }
};