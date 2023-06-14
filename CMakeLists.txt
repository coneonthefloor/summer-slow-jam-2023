cmake_minimum_required(VERSION 3.25)
project(SummerSlowJam2023 C)

set(CMAKE_C_STANDARD 17)

add_executable(SummerSlowJam2023 src/main.c src/ball.c src/ball.h src/main.h src/paddle.c src/paddle.h)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(SummerSlowJam2023 PRIVATE raylib)
