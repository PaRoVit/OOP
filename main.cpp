#include <iostream>
#include "include/plantGrowth.h"

int main() {
    int upSpeed, downSpeed, desiredHeight;
    std::cout << "enter the growth rate: ";
    std::cin  >> upSpeed;
    std::cout << "enter the reduction rate: ";
    std::cin  >> downSpeed;
    std::cout << "enter the final height: ";
    std::cin  >> desiredHeight;

    int totalDays = 0;
    
    try {
        totalDays = plantGrowth(upSpeed, downSpeed, desiredHeight);
        std::cout << "result: " << totalDays << std::endl;
    } catch (const NegativeValueException& e) {
        std::cerr << e.what() << std::endl;
    } catch (const InvalidRangeException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}