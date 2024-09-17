#include "../include/plantGrowth.h"

int plantGrowth(int upSpeed, int downSpeed, int desiredHeight) {

    if (desiredHeight <= 0 || upSpeed <= 0 || downSpeed < 0) {
        throw NegativeValueException();
    }

    if (upSpeed <= downSpeed) {
        throw InvalidRangeException();
    }        

    if (upSpeed >= desiredHeight)
        return 1;

    int days = (desiredHeight - upSpeed + (upSpeed - downSpeed) - 1) / (upSpeed - downSpeed);

    return days + 1;  
}