cmake_minimum_required (VERSION 3.10)

project(type_map_test)

add_executable(${PROJECT_NAME} test.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} type_map)
