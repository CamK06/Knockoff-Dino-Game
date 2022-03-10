project(dinogame)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB SOURCES "src/*.cpp")
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

add_executable(dino ${SOURCES})
target_link_libraries(dino sfml-graphics sfml-system sfml-window)