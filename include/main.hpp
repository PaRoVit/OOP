#include "../include/point.hpp"
#include "../include/figures.hpp"
#include "../include/array.hpp"

#include <iostream>


class MainRoutine {
public:
    Array data;

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
                Square *sq = new Square;
                std::cin >> *sq;
                data.pushBack((Figure*)sq);
            } else if (type == "triangle") {
                Triangle *tr = new Triangle;
                std::cin >> *tr;
                data.pushBack((Figure*)tr);
            } else if (type == "rectangle") {
                Rectangle *rect = new Rectangle;
                std::cin >> *rect;
                data.pushBack((Figure*)rect);
            } else {
                std::cout << "Unknown figure name.\n";
                return;
            }
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return ;
        }
        std::cout << "Success.\n";
    }

    void allArea() {
        double area = 0;
        for (size_t i = 0; i < data.size(); i++) {
            area += static_cast<double>(*data[i]); 
        }
        std::cout << area << std::endl;
    }

    void info() {
        std::cout << "Info: \n";
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << (i + 1) << ":\n";
            std::cout << "  area : " << static_cast<double>(*data[i]) << "\n" <<
                         "  geometric_center : " << data[i]->geometricCenter() << "\n"; 

        if (auto* triangle = dynamic_cast<Triangle*>(data[i])) {
            std::cout << "  " << *triangle; 
        } else if (auto* square = dynamic_cast<Square*>(data[i])) {
            std::cout << "  " << *square; 
        } else if (auto* rectangle = dynamic_cast<Rectangle*>(data[i])) {
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
            } else if (command == "erase") {
                eraseFigure();
            } else if (command == "area") {
                allArea();   
            } else {
                std::cout << "Unknown command.\n";
            }
            std::cout << "> ";
            std::cin >> command;
        }
    }
};