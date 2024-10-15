#include <gtest/gtest.h>
#include "../include/point.hpp"
#include "../include/figures.hpp"
#include "../include/array.hpp"
#include "../include/main.hpp"


TEST(TriangleTest, ReturnsGeometricCenter)
{
    Point p1{0, 0};
    Point p2{3, 0};
    Point p3{0, 6};
    Triangle triangle(p1, p2, p3);
    Point center = triangle.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0); 
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(TriangleTest, ReturnsArea)
{
    Point p1{0, 0};
    Point p2{3, 0};
    Point p3{0, 6};
    Triangle triangle(p1, p2, p3);
    EXPECT_DOUBLE_EQ(static_cast<double>(triangle), 9.0); 
}

TEST(TriangleTest, ReturnsError1)
{
    Point p1{1, 1};
    Point p2{2, 2};
    Point p3{3, 3};
    EXPECT_THROW(Triangle triangle(p1, p2, p3);, std::invalid_argument); 
}

TEST(SquareTest, ReturnsGeometricCenter)
{
    Point p1{2, 2};
    Point p2{-1, -1};
    Square square(p1, p2);
    Point center = square.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 0.5); 
    EXPECT_DOUBLE_EQ(center.y, 0.5);
}

TEST(SquareTest, ReturnsArea)
{
    Point p1{2, 2};
    Point p2{-1, -1};
    Square square(p1, p2);
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 9.0); 
}

TEST(SquareTest, ReturnsError1)
{
    Point p1{1, 0};
    Point p2{2, 0};
    EXPECT_THROW(Square square(p1, p2), std::invalid_argument); 
}

TEST(SquareTest, ReturnsError2)
{
    Point p1{0, 0};
    Point p2{0, 0};
    EXPECT_THROW(Square square(p1, p2), std::invalid_argument); 
}

TEST(RectangleTest, ReturnsGeometricCenter)
{
    Point p1{3, 5};
    Point p2{-1, -1};
    Rectangle rectangle(p1, p2);
    Point center = rectangle.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0); 
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}


TEST(RectangleTest, ReturnsArea)
{
    Point p1{3, 5};
    Point p2{-1, -1};
    Rectangle rectangle(p1, p2);
    EXPECT_DOUBLE_EQ(static_cast<double>(rectangle), 24.0); 
}

TEST(RectangleTest, ReturnsError1)
{
    Point p1{1, 0};
    Point p2{2, 0};
    EXPECT_THROW(Rectangle rectangle(p1, p2);, std::invalid_argument); 
}

TEST(RectangleTest, ReturnsError2)
{
    Point p1{0, 0};
    Point p2{0, 0};
    EXPECT_THROW(Rectangle rectangle(p1, p2);, std::invalid_argument); 
}




TEST(ArrayTest, PushBackTest) {
    Point p1{2, 2};
    Point p2{-1, -1};
    Square* square = new Square(p1, p2);

    Array data;

    data.pushBack((Figure*)square);


    EXPECT_EQ(data.size(), 1);
    EXPECT_NO_THROW(dynamic_cast<Square*>(data[0]));
    data.erase(0);
    EXPECT_EQ(data.size(), 0);
}

TEST(ArrayTest, EraseTest) {
    Array data;

    Point p1{2, 2};
    Point p2{-1, -1};
    Square* square = new Square(p1, p2);

    Point p3{3, 0};
    Triangle* triangle = new Triangle(p1, p2, p3);

    data.pushBack((Figure*)square);
    data.pushBack((Figure*)triangle);
    data.erase(0);

    EXPECT_EQ(data.size(), 1);
    EXPECT_NO_THROW(dynamic_cast<Triangle*>(data[0]));
    data.erase(0);
    EXPECT_EQ(data.size(), 0);
}

TEST(ArrayTest, EraseNoErrorTest) {
    Array data;

    Point p1{2, 2};
    Point p2{-1, -1};
    Square* square = new Square(p1, p2);

    Point p3{0, 0};
    Point p4{3, 0};
    Triangle* triangle = new Triangle(p1, p3, p4);

    data.pushBack((Figure*)square);
    data.pushBack((Figure*)triangle);

    EXPECT_THROW(data.erase(5), std::out_of_range);  

    EXPECT_EQ(data.size(), 2);

    EXPECT_NO_THROW(dynamic_cast<Square*>(data[0]));
    EXPECT_NO_THROW(dynamic_cast<Triangle*>(data[1]));
    data.erase(1);
    data.erase(0);
    EXPECT_EQ(data.size(), 0);

}

TEST(MainRoutineTest, AllAreaTest) {
    MainRoutine mainRoutine;

    Point p1{2, 2};
    Point p2{-1, -1};
    Square* square = new Square(p1, p2); // S = 9

    Point p3{0, 0};
    Point p4{3, 0};
    Point p5{0, 6};
    Triangle* triangle = new Triangle(p3, p4, p5); // S = 9

    Rectangle* rectangle = new Rectangle(p1, p4);  // S = 2

    // Добавляем фигуры в массив
    mainRoutine.data.pushBack((Figure*)square);
    mainRoutine.data.pushBack((Figure*)triangle);
    mainRoutine.data.pushBack((Figure*)rectangle);

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
