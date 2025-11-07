#include "Point.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Array.h"
#include <iostream>
#include <memory>

template<Scalar T>
void demonstrate_figure_operations(Array<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "\n=== Демонстрация операций с фигурами ===" << std::endl;
    
    double total_area = 0.0;
    
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "\nФигура " << (i + 1) << ":" << std::endl;
        std::cout << *figures[i] << std::endl;
        
        double area = static_cast<double>(*figures[i]);
        total_area += area;
    }
    
    std::cout << "\nОбщая площадь всех фигур: " << total_area << std::endl;
}

template<Scalar T>
void demonstrate_specific_types() {
    std::cout << "\n=== Демонстрация работы с конкретными типами ===" << std::endl;
    
    Array<Rectangle<T>> rectangles;
    rectangles.push_back(Rectangle<T>(Point<T>(0, 0), 4, 3));
    rectangles.push_back(Rectangle<T>(Point<T>(2, 2), 6, 2));
    
    std::cout << "\nМассив прямоугольников:" << std::endl;
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << "Прямоугольник " << (i + 1) << ": " << rectangles[i] << std::endl;
    }
    
    Array<Rhombus<T>> rhombuses;
    rhombuses.push_back(Rhombus<T>(Point<T>(0, 0), 6, 4));
    rhombuses.push_back(Rhombus<T>(Point<T>(1, 1), 8, 6));
    
    std::cout << "\nМассив ромбов:" << std::endl;
    for (size_t i = 0; i < rhombuses.size(); ++i) {
        std::cout << "Ромб " << (i + 1) << ": " << rhombuses[i] << std::endl;
    }
}

int main() {
    try {
        std::cout << "=== Лабораторная работа №4: Метапрограммирование ===" << std::endl;
        
        Array<std::shared_ptr<Figure<double>>> figures;
        
        auto rect1 = std::make_shared<Rectangle<double>>(Point<double>(0, 0), 4, 3);
        auto rect2 = std::make_shared<Rectangle<double>>(Point<double>(2, 2), 6, 2);
        
        auto trap1 = std::make_shared<Trapezoid<double>>(Point<double>(0, 0), 6, 4, 3);
        auto trap2 = std::make_shared<Trapezoid<double>>(Point<double>(1, 1), 8, 2, 4);
        
        auto rhomb1 = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 6, 4);
        auto rhomb2 = std::make_shared<Rhombus<double>>(Point<double>(1, 1), 8, 6);
        
        figures.push_back(rect1);
        figures.push_back(trap1);
        figures.push_back(rhomb1);
        figures.push_back(rect2);
        figures.push_back(trap2);
        figures.push_back(rhomb2);
        
        demonstrate_figure_operations(figures);
        
        std::cout << "\n=== Тестирование операций копирования и сравнения ===" << std::endl;
        
        Rectangle<double> original_rect(Point<double>(0, 0), 4, 3);
        Rectangle<double> copied_rect = original_rect;
        Rectangle<double> different_rect(Point<double>(1, 1), 5, 2);
        
        std::cout << "Оригинальный прямоугольник: " << original_rect << std::endl;
        std::cout << "Скопированный прямоугольник: " << copied_rect << std::endl;
        std::cout << "Другой прямоугольник: " << different_rect << std::endl;
        
        std::cout << "Оригинальный == Скопированный: " << (original_rect == copied_rect ? "да" : "нет") << std::endl;
        std::cout << "Оригинальный == Другой: " << (original_rect == different_rect ? "да" : "нет") << std::endl;
        
        std::cout << "\n=== Тестирование удаления элементов ===" << std::endl;
        std::cout << "Размер массива до удаления: " << figures.size() << std::endl;
        
        figures.remove(2);
        std::cout << "Размер массива после удаления элемента с индексом 2: " << figures.size() << std::endl;
        
        demonstrate_specific_types<double>();
        
        std::cout << "\n=== Тестирование с разными типами данных ===" << std::endl;
        
        Array<std::shared_ptr<Figure<int>>> int_figures;
        auto int_rect = std::make_shared<Rectangle<int>>(Point<int>(0, 0), 4, 3);
        auto int_rhomb = std::make_shared<Rhombus<int>>(Point<int>(1, 1), 6, 4);
        
        int_figures.push_back(int_rect);
        int_figures.push_back(int_rhomb);
        
        std::cout << "\nФигуры с целочисленными координатами:" << std::endl;
        for (size_t i = 0; i < int_figures.size(); ++i) {
            std::cout << "Фигура " << (i + 1) << ": " << *int_figures[i] << std::endl;
        }
        
        std::cout << "\n=== Тестирование операций перемещения ===" << std::endl;
        
        Array<Rectangle<double>> temp_array;
        temp_array.push_back(Rectangle<double>(Point<double>(0, 0), 2, 2));
        temp_array.push_back(Rectangle<double>(Point<double>(1, 1), 3, 3));
        
        Array<Rectangle<double>> moved_array = std::move(temp_array);
        std::cout << "Размер перемещенного массива: " << moved_array.size() << std::endl;
        std::cout << "Размер исходного массива после перемещения: " << temp_array.size() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
