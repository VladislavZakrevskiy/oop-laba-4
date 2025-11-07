#pragma once
#include <iostream>
#include <concepts>
#include <cmath>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;

public:
    Point() : x_(T{}), y_(T{}) {}
    
    Point(T x, T y) : x_(x), y_(y) {}
    
    Point(const Point& other) : x_(other.x_), y_(other.y_) {}
    
    Point(Point&& other) noexcept : x_(std::move(other.x_)), y_(std::move(other.y_)) {}
    
    Point& operator=(const Point& other) {
        if (this != &other) {
            x_ = other.x_;
            y_ = other.y_;
        }
        return *this;
    }
    
    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x_ = std::move(other.x_);
            y_ = std::move(other.y_);
        }
        return *this;
    }
    
    T x() const { return x_; }
    T y() const { return y_; }
    
    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }
    
    bool operator==(const Point& other) const {
        return std::abs(x_ - other.x_) < 1e-9 && std::abs(y_ - other.y_) < 1e-9;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    Point operator+(const Point& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }
    
    Point operator-(const Point& other) const {
        return Point(x_ - other.x_, y_ - other.y_);
    }
    
    double distance(const Point& other) const {
        T dx = x_ - other.x_;
        T dy = y_ - other.y_;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x_ >> p.y_;
        return is;
    }
};
