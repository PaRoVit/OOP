#include "../include/plantGrowth.h"

int plantGrowth(int upSpeed, int downSpeed, int desiredHeight) {

    if (desiredHeight <= 0) {
        throw NegativeValueException();
    }

    if (upSpeed <= downSpeed) {
        throw InvalidRangeException();
    }

    int currentHeight = 0;  
    int days = 0;          

    while (currentHeight < desiredHeight) {
        days++;  
        currentHeight += upSpeed;  

        if (currentHeight >= desiredHeight) {
            return days;  
        }

        currentHeight -= downSpeed;  
    }

    return days;  
}