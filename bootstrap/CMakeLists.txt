cmake_minimum_required(VERSION 3.16)
project(frostc_cpp)

# use c++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# currdir for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Define executable
add_executable(frostc_cpp
    main.cpp
    Lexer.cpp
    Parser.cpp
    Assembler.cpp
)

set_target_properties(frostc_cpp PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
)

