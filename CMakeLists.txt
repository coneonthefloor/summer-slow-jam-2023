cmake_minimum_required(VERSION 3.25)
project(SummerSlowJam2023 C)

set(CMAKE_C_STANDARD 17)

add_executable(SummerSlowJam2023 main.c)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(SummerSlowJam2023 PRIVATE raylib)
