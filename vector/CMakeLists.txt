project(vector)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)


add_executable(${PROJECT_NAME}
        core/src/main.cc
        core/include/vector.h)







include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
    vector_tests
    tests/test_vector.cc

  
)
target_link_libraries(
    vector_tests
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_tests)