#pragma once
#include "Figure.h"
#include <stdexcept>
#include <cmath>

template<Scalar T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() = default;
    
    Trapezoid(const Point<T>& center, T base1, T base2, T height) {
        if (base1 <= 0 || base2 <= 0 || height <= 0) {
            throw std::invalid_argument("All dimensions must be positive");
        }
        
        T half_height = height / 2;
        T half_base1 = base1 / 2;
        T half_base2 = base2 / 2;
        
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() - half_base1, center.y() - half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() + half_base1, center.y() - half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() + half_base2, center.y() + half_height));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() - half_base2, center.y() + half_height));
    }
    
    Trapezoid(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) {
        this->vertices_.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices_.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices_.push_back(std::make_unique<Point<T>>(x3, y3));
        this->vertices_.push_back(std::make_unique<Point<T>>(x4, y4));
        
        if (!is_valid_trapezoid()) {
            throw std::invalid_argument("Points do not form a valid trapezoid");
        }
    }
    
    Trapezoid(const Trapezoid& other) : Figure<T>(other) {}
    
    Trapezoid(Trapezoid&& other) noexcept : Figure<T>(std::move(other)) {}
    
    Trapezoid& operator=(const Trapezoid& other) {
        if (this != &other) {
            Figure<T>::operator=(other);
        }
        return *this;
    }
    
    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this != &other) {
            Figure<T>::operator=(std::move(other));
        }
        return *this;
    }
    
    double area() const override {
        if (this->vertices_.size() != 4) {
            return 0.0;
        }
        
        double base1 = this->vertices_[0]->distance(*this->vertices_[1]);
        double base2 = this->vertices_[2]->distance(*this->vertices_[3]);
        double height = std::abs(this->vertices_[0]->y() - this->vertices_[3]->y());
        
        return (base1 + base2) * height / 2.0;
    }
    
    T base1() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[0]->distance(*this->vertices_[1]));
    }
    
    T base2() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[2]->distance(*this->vertices_[3]));
    }
    
    T height() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(std::abs(this->vertices_[0]->y() - this->vertices_[3]->y()));
    }

private:
    bool is_valid_trapezoid() const {
        if (this->vertices_.size() != 4) {
            return false;
        }
        
        const double eps = 1e-9;
        
        T y1 = this->vertices_[0]->y();
        T y2 = this->vertices_[1]->y();
        T y3 = this->vertices_[2]->y();
        T y4 = this->vertices_[3]->y();
        
        bool parallel_bases = (std::abs(y1 - y2) < eps) && (std::abs(y3 - y4) < eps);
        
        return parallel_bases && (std::abs(y1 - y3) > eps);
    }
};
