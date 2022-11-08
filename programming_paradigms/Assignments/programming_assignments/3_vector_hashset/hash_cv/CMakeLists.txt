project(hash_cv)
cmake_minimum_required(VERSION 3.22)
include(CTest)
add_executable(${PROJECT_NAME}
        src/hashset.c
        src/vector.c
        src/streamtokenizer.c
        src/thesaurus-lookup.c)
add_test(hash_test ${PROJECT_NAME})


