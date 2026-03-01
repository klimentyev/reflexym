cmake_minimum_required(VERSION 4.1)
project(reflexym VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 26)

add_executable(${PROJECT_NAME} example.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
)
target_compile_options(${PROJECT_NAME} PRIVATE -freflection)
