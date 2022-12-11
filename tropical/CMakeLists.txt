cmake_minimum_required (VERSION 3.0)
project (Tropical)
set(CMAKE_CXX_STANDARD 17)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable (${PROJECT_NAME} main.cpp max_algebra.h )
target_link_libraries (${PROJECT_NAME} Eigen3::Eigen)


