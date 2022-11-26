project(date)


add_executable(${PROJECT_NAME} src/main.cpp src/date.cpp)


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
        test_date
        src/date.cpp
        tests/test_date.cpp


)
target_link_libraries(
        test_date
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_date)