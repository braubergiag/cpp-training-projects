project(ssa)
cmake_minimum_required(VERSION 3.22)

add_executable(${PROJECT_NAME} src/main.c src/ssa.c src/vector.c)

include (CTest)

add_test(ssa_test ${PROJECT_NAME})