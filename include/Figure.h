#pragma once
#include "Point.h"
#include <memory>
#include <vector>
#include <iostream>

template<Scalar T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices_;

public:
    Figure() = default;
    
    virtual ~Figure() = default;
    
    Figure(const Figure& other) {
        vertices_.reserve(other.vertices_.size());
        for (const auto& vertex : other.vertices_) {
            vertices_.push_back(std::make_unique<Point<T>>(*vertex));
        }
    }
    
    Figure(Figure&& other) noexcept : vertices_(std::move(other.vertices_)) {}
    
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices_.clear();
            vertices_.reserve(other.vertices_.size());
            for (const auto& vertex : other.vertices_) {
                vertices_.push_back(std::make_unique<Point<T>>(*vertex));
            }
        }
        return *this;
    }
    
    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            vertices_ = std::move(other.vertices_);
        }
        return *this;
    }
    
    virtual double area() const = 0;
    
    virtual Point<T> center() const {
        if (vertices_.empty()) {
            return Point<T>();
        }
        
        T sum_x = T{};
        T sum_y = T{};
        
        for (const auto& vertex : vertices_) {
            sum_x += vertex->x();
            sum_y += vertex->y();
        }
        
        return Point<T>(sum_x / static_cast<T>(vertices_.size()), 
                       sum_y / static_cast<T>(vertices_.size()));
    }
    
    virtual void print_vertices(std::ostream& os) const {
        for (size_t i = 0; i < vertices_.size(); ++i) {
            os << "Vertex " << i + 1 << ": " << *vertices_[i];
            if (i < vertices_.size() - 1) {
                os << ", ";
            }
        }
    }
    
    bool operator==(const Figure& other) const {
        if (vertices_.size() != other.vertices_.size()) {
            return false;
        }
        
        for (size_t i = 0; i < vertices_.size(); ++i) {
            if (*vertices_[i] != *other.vertices_[i]) {
                return false;
            }
        }
        
        return true;
    }
    
    bool operator!=(const Figure& other) const {
        return !(*this == other);
    }
    
    explicit operator double() const {
        return area();
    }
    
    size_t vertex_count() const {
        return vertices_.size();
    }
    
    const Point<T>& get_vertex(size_t index) const {
        return *vertices_.at(index);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        os << "Center: " << figure.center() << ", Area: " << figure.area() << ", Vertices: ";
        figure.print_vertices(os);
        return os;
    }
};
