#include <gtest/gtest.h>
#include "../include/Four.hpp"

TEST(FourTest, InvalidNumber) {
    EXPECT_THROW(Four("1234"), std::logic_error); 
}

TEST(FourTest, InvalidNumber2) {
    EXPECT_THROW(Four("-12"), std::logic_error); 
}

TEST(FourTest, Addition) {
    Four a("12");  
    Four b("12");  

    Four result = a + b; 

    EXPECT_EQ(result.getNumber()[1], '3'); 
    EXPECT_EQ(result.getNumber()[0], '0'); 
}

TEST(FourTest, Subtraction) {
    Four a("100");  
    Four b("33");  

    Four result = a - b; 

    EXPECT_EQ(result.getNumber()[0], '1');  
}

TEST(FourTest, SubtractionOutRange) {
    Four a("13");  
    Four b("23");  

    EXPECT_THROW(a - b, std::logic_error);  
}

TEST(FourTest, Multiplication) {
    Four a("12");  
    Four b("12");  

    Four result = a * b; 

    EXPECT_EQ(result.getNumber()[2], '2');  
    EXPECT_EQ(result.getNumber()[1], '1'); 
    EXPECT_EQ(result.getNumber()[0], '0'); 
}

TEST(FourTest, Assignment) {
    Four a("12");  
    Four b("23");  

    a = std::move(b);

    EXPECT_EQ(a.getNumber()[1], '2'); 
    EXPECT_EQ(a.getNumber()[0], '3'); 

}

TEST(FourTest, Comparisons) {
    Four a("23"); 
    Four b("12"); 

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a >= b);
    EXPECT_FALSE(a <= b);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();               
}
