#pragma once
#include "Figure.h"
#include <stdexcept>
#include <cmath>

template<Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle() = default;
    
    Rectangle(const Point<T>& center, T width, T height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        
        T half_width = width / 2;
        T half_height = height / 2;
        
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() - half_width, center.y() - half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() + half_width, center.y() - half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() + half_width, center.y() + half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() - half_width, center.y() + half_height));
    }
    
    Rectangle(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) {
        this->vertices_.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices_.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices_.push_back(std::make_unique<Point<T>>(x3, y3));
        this->vertices_.push_back(std::make_unique<Point<T>>(x4, y4));
        
        if (!is_valid_rectangle()) {
            throw std::invalid_argument("Points do not form a valid rectangle");
        }
    }
    
    Rectangle(const Rectangle& other) : Figure<T>(other) {}
    
    Rectangle(Rectangle&& other) noexcept : Figure<T>(std::move(other)) {}
    
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            Figure<T>::operator=(other);
        }
        return *this;
    }
    
    Rectangle& operator=(Rectangle&& other) noexcept {
        if (this != &other) {
            Figure<T>::operator=(std::move(other));
        }
        return *this;
    }
    
    double area() const override {
        if (this->vertices_.size() != 4) {
            return 0.0;
        }
        
        double side1 = this->vertices_[0]->distance(*this->vertices_[1]);
        double side2 = this->vertices_[1]->distance(*this->vertices_[2]);
        
        return side1 * side2;
    }
    
    T width() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[0]->distance(*this->vertices_[1]));
    }
    
    T height() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[1]->distance(*this->vertices_[2]));
    }

private:
    bool is_valid_rectangle() const {
        if (this->vertices_.size() != 4) {
            return false;
        }
        
        double side1 = this->vertices_[0]->distance(*this->vertices_[1]);
        double side2 = this->vertices_[1]->distance(*this->vertices_[2]);
        double side3 = this->vertices_[2]->distance(*this->vertices_[3]);
        double side4 = this->vertices_[3]->distance(*this->vertices_[0]);
        
        double diag1 = this->vertices_[0]->distance(*this->vertices_[2]);
        double diag2 = this->vertices_[1]->distance(*this->vertices_[3]);
        
        const double eps = 1e-9;
        
        return (std::abs(side1 - side3) < eps) && 
               (std::abs(side2 - side4) < eps) && 
               (std::abs(diag1 - diag2) < eps);
    }
};
