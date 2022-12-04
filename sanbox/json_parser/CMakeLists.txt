project(parser)
cmake_minimum_required(VERSION 3.1)






find_package(nlohmann_json 3.10.5 REQUIRED)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME}  PRIVATE nlohmann_json::nlohmann_json)