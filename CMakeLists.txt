cmake_minimum_required (VERSION 3.10)

project(type_map)

add_library (${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE include)

add_subdirectory(test)
