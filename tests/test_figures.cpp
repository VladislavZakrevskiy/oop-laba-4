#include <gtest/gtest.h>
#include "Point.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Array.h"
#include <memory>

class PointTest : public ::testing::Test {
protected:
    Point<double> p1{1.0, 2.0};
    Point<double> p2{3.0, 4.0};
    Point<int> pi1{1, 2};
    Point<int> pi2{3, 4};
};

TEST_F(PointTest, Construction) {
    EXPECT_EQ(p1.x(), 1.0);
    EXPECT_EQ(p1.y(), 2.0);
    
    Point<double> default_point;
    EXPECT_EQ(default_point.x(), 0.0);
    EXPECT_EQ(default_point.y(), 0.0);
}

TEST_F(PointTest, CopyAndMove) {
    Point<double> copied = p1;
    EXPECT_EQ(copied, p1);
    
    Point<double> moved = std::move(copied);
    EXPECT_EQ(moved, p1);
}

TEST_F(PointTest, Operations) {
    Point<double> sum = p1 + p2;
    EXPECT_EQ(sum.x(), 4.0);
    EXPECT_EQ(sum.y(), 6.0);
    
    Point<double> diff = p2 - p1;
    EXPECT_EQ(diff.x(), 2.0);
    EXPECT_EQ(diff.y(), 2.0);
    
    double distance = p1.distance(p2);
    EXPECT_NEAR(distance, 2.828427, 1e-5);
}

TEST_F(PointTest, Comparison) {
    Point<double> p1_copy = p1;
    EXPECT_TRUE(p1 == p1_copy);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

class RectangleTest : public ::testing::Test {
protected:
    Rectangle<double> rect{Point<double>(0, 0), 4, 3};
};

TEST_F(RectangleTest, Construction) {
    EXPECT_EQ(rect.vertex_count(), 4);
    EXPECT_NEAR(rect.area(), 12.0, 1e-9);
    EXPECT_NEAR(rect.width(), 4.0, 1e-9);
    EXPECT_NEAR(rect.height(), 3.0, 1e-9);
}

TEST_F(RectangleTest, Center) {
    Point<double> center = rect.center();
    EXPECT_NEAR(center.x(), 0.0, 1e-9);
    EXPECT_NEAR(center.y(), 0.0, 1e-9);
}

TEST_F(RectangleTest, CopyAndMove) {
    Rectangle<double> copied = rect;
    EXPECT_TRUE(copied == rect);
    EXPECT_NEAR(copied.area(), rect.area(), 1e-9);
    
    Rectangle<double> moved = std::move(copied);
    EXPECT_NEAR(moved.area(), rect.area(), 1e-9);
}

TEST_F(RectangleTest, TypeConversion) {
    double area = static_cast<double>(rect);
    EXPECT_NEAR(area, 12.0, 1e-9);
}

class TrapezoidTest : public ::testing::Test {
protected:
    Trapezoid<double> trap{Point<double>(0, 0), 6, 4, 3};
};

TEST_F(TrapezoidTest, Construction) {
    EXPECT_EQ(trap.vertex_count(), 4);
    EXPECT_NEAR(trap.area(), 15.0, 1e-9);
    EXPECT_NEAR(trap.base1(), 6.0, 1e-9);
    EXPECT_NEAR(trap.base2(), 4.0, 1e-9);
    EXPECT_NEAR(trap.height(), 3.0, 1e-9);
}

TEST_F(TrapezoidTest, Center) {
    Point<double> center = trap.center();
    EXPECT_NEAR(center.x(), 0.0, 1e-9);
    EXPECT_NEAR(center.y(), 0.0, 1e-9);
}

TEST_F(TrapezoidTest, CopyAndMove) {
    Trapezoid<double> copied = trap;
    EXPECT_TRUE(copied == trap);
    EXPECT_NEAR(copied.area(), trap.area(), 1e-9);
    
    Trapezoid<double> moved = std::move(copied);
    EXPECT_NEAR(moved.area(), trap.area(), 1e-9);
}

class RhombusTest : public ::testing::Test {
protected:
    Rhombus<double> rhomb{Point<double>(0, 0), 6, 4};
};

TEST_F(RhombusTest, Construction) {
    EXPECT_EQ(rhomb.vertex_count(), 4);
    EXPECT_NEAR(rhomb.area(), 12.0, 1e-9);
    EXPECT_NEAR(rhomb.diagonal1(), 4.0, 1e-9);
    EXPECT_NEAR(rhomb.diagonal2(), 6.0, 1e-9);
}

TEST_F(RhombusTest, Center) {
    Point<double> center = rhomb.center();
    EXPECT_NEAR(center.x(), 0.0, 1e-9);
    EXPECT_NEAR(center.y(), 0.0, 1e-9);
}

TEST_F(RhombusTest, CopyAndMove) {
    Rhombus<double> copied = rhomb;
    EXPECT_TRUE(copied == rhomb);
    EXPECT_NEAR(copied.area(), rhomb.area(), 1e-9);
    
    Rhombus<double> moved = std::move(copied);
    EXPECT_NEAR(moved.area(), rhomb.area(), 1e-9);
}

class ArrayTest : public ::testing::Test {
protected:
    Array<int> arr;
    
    void SetUp() override {
        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);
    }
};

TEST_F(ArrayTest, BasicOperations) {
    EXPECT_EQ(arr.size(), 3);
    EXPECT_FALSE(arr.empty());
    
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST_F(ArrayTest, PushBack) {
    arr.push_back(4);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[3], 4);
}

TEST_F(ArrayTest, Remove) {
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST_F(ArrayTest, CopyAndMove) {
    Array<int> copied = arr;
    EXPECT_EQ(copied.size(), arr.size());
    EXPECT_EQ(copied[0], arr[0]);
    
    Array<int> moved = std::move(copied);
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(copied.size(), 0);
}

TEST_F(ArrayTest, OutOfRange) {
    EXPECT_THROW(arr[10], std::out_of_range);
    EXPECT_THROW(arr.remove(10), std::out_of_range);
}

class FigureArrayTest : public ::testing::Test {
protected:
    Array<std::shared_ptr<Figure<double>>> figures;
    
    void SetUp() override {
        figures.push_back(std::make_shared<Rectangle<double>>(Point<double>(0, 0), 4, 3));
        figures.push_back(std::make_shared<Trapezoid<double>>(Point<double>(0, 0), 6, 4, 3));
        figures.push_back(std::make_shared<Rhombus<double>>(Point<double>(0, 0), 6, 4));
    }
};

TEST_F(FigureArrayTest, PolymorphicBehavior) {
    EXPECT_EQ(figures.size(), 3);
    
    EXPECT_NEAR(figures[0]->area(), 12.0, 1e-9);
    EXPECT_NEAR(figures[1]->area(), 15.0, 1e-9);
    EXPECT_NEAR(figures[2]->area(), 12.0, 1e-9);
}

TEST_F(FigureArrayTest, TotalArea) {
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += static_cast<double>(*figures[i]);
    }
    EXPECT_NEAR(total, 39.0, 1e-9);
}

TEST_F(FigureArrayTest, Centers) {
    for (size_t i = 0; i < figures.size(); ++i) {
        Point<double> center = figures[i]->center();
        EXPECT_NEAR(center.x(), 0.0, 1e-9);
        EXPECT_NEAR(center.y(), 0.0, 1e-9);
    }
}

TEST(ConceptTest, ScalarTypes) {
    EXPECT_TRUE(Scalar<int>);
    EXPECT_TRUE(Scalar<float>);
    EXPECT_TRUE(Scalar<double>);
    EXPECT_TRUE(Scalar<long>);
    
    Point<int> int_point(1, 2);
    Point<float> float_point(1.5f, 2.5f);
    Point<double> double_point(1.5, 2.5);
    
    EXPECT_EQ(int_point.x(), 1);
    EXPECT_NEAR(float_point.x(), 1.5f, 1e-6);
    EXPECT_NEAR(double_point.x(), 1.5, 1e-9);
}

TEST(TemplateTest, DifferentTypes) {
    Rectangle<int> int_rect(Point<int>(0, 0), 4, 3);
    Rectangle<float> float_rect(Point<float>(0.0f, 0.0f), 4.0f, 3.0f);
    Rectangle<double> double_rect(Point<double>(0.0, 0.0), 4.0, 3.0);
    
    EXPECT_NEAR(int_rect.area(), 8.0, 1e-9);
    EXPECT_NEAR(float_rect.area(), 12.0f, 1e-6);
    EXPECT_NEAR(double_rect.area(), 12.0, 1e-9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
