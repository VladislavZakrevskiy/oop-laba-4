#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

template<class T>
class Array {
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;

    void resize_if_needed() {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            auto new_data = std::shared_ptr<T[]>(new T[new_capacity]);
            
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

public:
    Array() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit Array(size_t initial_capacity) 
        : data_(std::shared_ptr<T[]>(new T[initial_capacity])), 
          size_(0), 
          capacity_(initial_capacity) {}
    
    Array(const Array& other) 
        : data_(std::shared_ptr<T[]>(new T[other.capacity_])), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            data_ = std::shared_ptr<T[]>(new T[other.capacity_]);
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void push_back(const T& item) {
        resize_if_needed();
        data_[size_++] = item;
    }
    
    void push_back(T&& item) {
        resize_if_needed();
        data_[size_++] = std::move(item);
    }
    
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        
        --size_;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const {
        return size_;
    }
    
    size_t capacity() const {
        return capacity_;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    void clear() {
        size_ = 0;
    }
    
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    class iterator {
    private:
        T* ptr_;
        
    public:
        explicit iterator(T* ptr) : ptr_(ptr) {}
        
        T& operator*() { return *ptr_; }
        const T& operator*() const { return *ptr_; }
        
        T* operator->() { return ptr_; }
        const T* operator->() const { return ptr_; }
        
        iterator& operator++() {
            ++ptr_;
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }
        
        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }
    };
    
    iterator begin() {
        return iterator(data_.get());
    }
    
    iterator end() {
        return iterator(data_.get() + size_);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size_; ++i) {
            os << arr.data_[i];
            if (i < arr.size_ - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};
