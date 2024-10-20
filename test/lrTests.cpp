#include <gtest/gtest.h>
#include "../include/point.hpp"
#include "../include/figures.hpp"
#include "../include/array.hpp"
#include "../include/main.hpp"


TEST(TriangleTest, ReturnsGeometricCenter)
{
    Point<double> p1{0, 0};
    Point<double> p2{3, 0};
    Point<double> p3{0, 6};
    Triangle<double> triangle(p1, p2, p3);
    Point<double> center = triangle.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0); 
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(TriangleTest, ReturnsArea)
{
    Point<double> p1{0, 0};
    Point<double> p2{3, 0};
    Point<double> p3{0, 6};
    Triangle<double> triangle(p1, p2, p3);
    EXPECT_DOUBLE_EQ(static_cast<double>(triangle), 9.0); 
}

TEST(TriangleTest, ReturnsError1)
{
    Point<double> p1{1, 1};
    Point<double> p2{2, 2};
    Point<double> p3{3, 3};
    EXPECT_THROW(Triangle<double> triangle(p1, p2, p3);, std::invalid_argument); 
}

TEST(SquareTest, ReturnsGeometricCenter)
{
    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double> square(p1, p2);
    Point center = square.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 0.5); 
    EXPECT_DOUBLE_EQ(center.y, 0.5);
}

TEST(SquareTest, ReturnsArea)
{
    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double> square(p1, p2);
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 9.0); 
}

TEST(SquareTest, ReturnsError1)
{
    Point<double> p1{1, 0};
    Point<double> p2{2, 0};
    EXPECT_THROW(Square<double> square(p1, p2), std::invalid_argument); 
}

TEST(SquareTest, ReturnsError2)
{
    Point<double> p1{0, 0};
    Point<double> p2{0, 0};
    EXPECT_THROW(Square<double> square(p1, p2), std::invalid_argument); 
}

TEST(RectangleTest, ReturnsGeometricCenter)
{
    Point<double> p1{3, 5};
    Point<double> p2{-1, -1};
    Rectangle<double> rectangle(p1, p2);
    Point<double> center = rectangle.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0); 
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}


TEST(RectangleTest, ReturnsArea)
{
    Point<double> p1{3, 5};
    Point<double> p2{-1, -1};
    Rectangle<double> rectangle(p1, p2);
    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 24.0); 
}

TEST(RectangleTest, ReturnsError1)
{
    Point<double> p1{1, 0};
    Point<double> p2{2, 0};
    EXPECT_THROW(Rectangle<double> rectangle(p1, p2);, std::invalid_argument); 
}

TEST(RectangleTest, ReturnsError2)
{
    Point<double> p1{0, 0};
    Point<double> p2{0, 0};
    EXPECT_THROW(Rectangle<double> rectangle(p1, p2);, std::invalid_argument); 
}




TEST(ArrayTest, PushBackTest) {
    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double>* square = new Square<double>(p1, p2);

    Array<Figure<double>*> data;

    data.pushBack((Figure<double>*)square);


    EXPECT_EQ(data.size(), 1);
    EXPECT_NO_THROW(dynamic_cast<Square<double>*>(data[0]));
    data.erase(0);
    EXPECT_EQ(data.size(), 0);
}

TEST(ArrayTest, EraseTest) {
    Array<Figure<double>*> data;
    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double>* square = new Square<double>(p1, p2);

    Point<double> p3{3, 0};
    Triangle<double>* triangle = new Triangle<double>(p1, p2, p3);

    data.pushBack((Figure<double>*)square);
    data.pushBack((Figure<double>*)triangle);
    data.erase(0);

    EXPECT_EQ(data.size(), 1);
    EXPECT_NO_THROW(dynamic_cast<Triangle<double>*>(data[0]));
    data.erase(0);
    EXPECT_EQ(data.size(), 0);
}

TEST(ArrayTest, EraseNoErrorTest) {
    Array<Figure<double>*> data;

    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double>* square = new Square<double>(p1, p2);

    Point<double> p3{0, 0};
    Point<double> p4{3, 0};
    Triangle<double>* triangle = new Triangle<double>(p1, p3, p4);

    data.pushBack((Figure<double>*)square);
    data.pushBack((Figure<double>*)triangle);

    EXPECT_THROW(data.erase(5), std::out_of_range);  

    EXPECT_EQ(data.size(), 2);

    EXPECT_NO_THROW(dynamic_cast<Square<double>*>(data[0]));
    EXPECT_NO_THROW(dynamic_cast<Triangle<double>*>(data[1]));
    data.erase(1);
    data.erase(0);
    EXPECT_EQ(data.size(), 0);

}

TEST(MainRoutineTest, AllAreaTest) {
    MainRoutine<double> mainRoutine;

    Point<double> p1{2, 2};
    Point<double> p2{-1, -1};
    Square<double>* square = new Square<double>(p1, p2); // S = 9

    Point<double> p3{0, 0};
    Point<double> p4{3, 0};
    Point<double> p5{0, 6};
    Triangle<double>* triangle = new Triangle<double>(p3, p4, p5); // S = 9

    Rectangle<double>* rectangle = new Rectangle<double>(p1, p4);  // S = 2

    // Добавляем фигуры в массив
    mainRoutine.data.pushBack((Figure<double>*)square);
    mainRoutine.data.pushBack((Figure<double>*)triangle);
    mainRoutine.data.pushBack((Figure<double>*)rectangle);

    double expectedTotalArea = 9.0 + 9.0 + 2.0;

    std::ostringstream out;
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    mainRoutine.allArea();

    std::cout.rdbuf(coutbuf);
    double actualTotalArea = std::stod(out.str());

    EXPECT_DOUBLE_EQ(expectedTotalArea, actualTotalArea);

    mainRoutine.data.erase(2);
    mainRoutine.data.erase(1);
    mainRoutine.data.erase(0);
    EXPECT_EQ(mainRoutine.data.size(), 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
