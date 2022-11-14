project(student_exam)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/student_info.cpp
        src/grader_util.cpp)


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
        student_tests
        tests/tests.cpp


)
target_link_libraries(
        student_tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(student_tests)