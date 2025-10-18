cmake_minimum_required(VERSION 3.10)
project(MAI_SEM3_LAB2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим установленный googletest
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Основная программа
add_executable(lab2 main.cpp src/FOUR.cpp)
target_include_directories(lab2 PUBLIC include)

# Тесты
add_executable(tests tests/tests01.cpp src/FOUR.cpp)
target_include_directories(tests PUBLIC include)
target_link_libraries(tests GTest::gtest_main Threads::Threads)

# Чтобы исполняемые файлы были в корне build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})