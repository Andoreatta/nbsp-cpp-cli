cmake_minimum_required(VERSION 3.22)
project(nbspcli CXX)

set(CMAKE_CXX_STANDARD 23)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(fmt REQUIRED)
find_package(cxxopts REQUIRED)
add_compile_options(-pedantic-errors -Wall -Weffc++ -Wextra  -Wconversion -Wsign-conversion -Werror)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} cxxopts::cxxopts fmt::fmt NBioBSP)