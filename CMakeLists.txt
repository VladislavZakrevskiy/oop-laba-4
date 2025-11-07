cmake_minimum_required(VERSION 3.20)
project(figures_templates)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp
)

set(HEADERS
    include/Point.h
    include/Figure.h
    include/Rectangle.h
    include/Trapezoid.h
    include/Rhombus.h
    include/Array.h
)

add_executable(figures_demo ${SOURCES} ${HEADERS})

enable_testing()
find_package(GTest REQUIRED)

add_executable(figures_tests
    tests/test_figures.cpp
    ${HEADERS}
)

target_link_libraries(figures_tests GTest::gtest GTest::gtest_main)

add_test(NAME FiguresTest COMMAND figures_tests)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS figures_tests
)
