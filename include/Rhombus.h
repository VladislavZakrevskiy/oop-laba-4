#pragma once
#include "Figure.h"
#include <stdexcept>
#include <cmath>

template<Scalar T>
class Rhombus : public Figure<T> {
public:
    Rhombus() = default;
    
    Rhombus(const Point<T>& center, T diagonal1, T diagonal2) {
        if (diagonal1 <= 0 || diagonal2 <= 0) {
            throw std::invalid_argument("Diagonals must be positive");
        }
        
        T half_d1 = diagonal1 / 2;
        T half_d2 = diagonal2 / 2;
        
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x(), center.y() + half_d2));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() + half_d1, center.y()));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x(), center.y() - half_d2));
        this->vertices_.push_back(std::make_unique<Point<T>>(center.x() - half_d1, center.y()));
    }
    
    Rhombus(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) {
        this->vertices_.push_back(std::make_unique<Point<T>>(x1, y1));
        this->vertices_.push_back(std::make_unique<Point<T>>(x2, y2));
        this->vertices_.push_back(std::make_unique<Point<T>>(x3, y3));
        this->vertices_.push_back(std::make_unique<Point<T>>(x4, y4));
        
        if (!is_valid_rhombus()) {
            throw std::invalid_argument("Points do not form a valid rhombus");
        }
    }
    
    Rhombus(const Rhombus& other) : Figure<T>(other) {}
    
    Rhombus(Rhombus&& other) noexcept : Figure<T>(std::move(other)) {}
    
    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            Figure<T>::operator=(other);
        }
        return *this;
    }
    
    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this != &other) {
            Figure<T>::operator=(std::move(other));
        }
        return *this;
    }
    
    double area() const override {
        if (this->vertices_.size() != 4) {
            return 0.0;
        }
        
        double diagonal1 = this->vertices_[0]->distance(*this->vertices_[2]);
        double diagonal2 = this->vertices_[1]->distance(*this->vertices_[3]);
        
        return (diagonal1 * diagonal2) / 2.0;
    }
    
    T diagonal1() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[0]->distance(*this->vertices_[2]));
    }
    
    T diagonal2() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[1]->distance(*this->vertices_[3]));
    }
    
    T side() const {
        if (this->vertices_.size() != 4) {
            return T{};
        }
        return static_cast<T>(this->vertices_[0]->distance(*this->vertices_[1]));
    }

private:
    bool is_valid_rhombus() const {
        if (this->vertices_.size() != 4) {
            return false;
        }
        
        double side1 = this->vertices_[0]->distance(*this->vertices_[1]);
        double side2 = this->vertices_[1]->distance(*this->vertices_[2]);
        double side3 = this->vertices_[2]->distance(*this->vertices_[3]);
        double side4 = this->vertices_[3]->distance(*this->vertices_[0]);
        
        const double eps = 1e-9;
        
        bool all_sides_equal = (std::abs(side1 - side2) < eps) && 
                              (std::abs(side2 - side3) < eps) && 
                              (std::abs(side3 - side4) < eps);
        
        Point<T> center = this->center();
        Point<T> diag1_mid((this->vertices_[0]->x() + this->vertices_[2]->x()) / 2,
                          (this->vertices_[0]->y() + this->vertices_[2]->y()) / 2);
        Point<T> diag2_mid((this->vertices_[1]->x() + this->vertices_[3]->x()) / 2,
                          (this->vertices_[1]->y() + this->vertices_[3]->y()) / 2);
        
        bool diagonals_bisect = (center == diag1_mid) && (center == diag2_mid);
        
        return all_sides_equal && diagonals_bisect;
    }
};
