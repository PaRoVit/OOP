#include <gtest/gtest.h>
#include "../include/plantGrowth.h"

TEST(CountOnesInRangeTest1, ReturnsCorrectResultFor100To10)
{
    int upSpeed = 100;
    int downSpeed = 10;
    int desiredHeight = 910;
    int result = plantGrowth(upSpeed, downSpeed, desiredHeight);
    ASSERT_TRUE(result == 10);
}

TEST(CountOnesInRangeTest2, ReturnsCorrectResultFor100To10)
{
    int upSpeed = 100;
    int downSpeed = 10;
    int desiredHeight = 100;
    int result = plantGrowth(upSpeed, downSpeed, desiredHeight);
    ASSERT_TRUE(result == 1);
}

TEST(CountOnesInRangeTest, ReturnsCorrectResultForRange60To50)
{
    int upSpeed = 60;
    int downSpeed = 50;
    int desiredHeight = 70;
    int result = plantGrowth(upSpeed, downSpeed, desiredHeight);
    ASSERT_TRUE(result == 2);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForDesiredHeightEqualTo0)
{
    int upSpeed = 100;
    int downSpeed = 50;
    int desiredHeight = 0;
    ASSERT_THROW(plantGrowth(upSpeed, downSpeed, desiredHeight), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForNegativeDesiredHeight)
{
    int upSpeed = 100;
    int downSpeed = 50;
    int desiredHeight = -20;
    ASSERT_THROW(plantGrowth(upSpeed, downSpeed, desiredHeight), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForNegativeUpSpeed)
{
    int upSpeed = 0;
    int downSpeed = 50;
    int desiredHeight = 900;
    ASSERT_THROW(plantGrowth(upSpeed, downSpeed, desiredHeight), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsNegativeValueExceptionForNegativeDownSpeed)
{
    int upSpeed = 100;
    int downSpeed = -50;
    int desiredHeight = 900;
    ASSERT_THROW(plantGrowth(upSpeed, downSpeed, desiredHeight), NegativeValueException);
}

TEST(CountOnesInRangeTest, ThrowsInvalidRangeExceptionForDownwardGrowthExceedingUpwardGrowth)
{
    int upSpeed = 100;
    int downSpeed = 110;
    int desiredHeight = 50;
    ASSERT_THROW(plantGrowth(upSpeed, downSpeed, desiredHeight), InvalidRangeException);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
