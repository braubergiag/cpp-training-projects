project(stack_cv)
cmake_minimum_required(VERSION 3.22)

add_executable(${PROJECT_NAME} src/stack.c src/main.c src/tests.c)
include(CTest)
add_test(stack_test ${PROJECT_NAME})



