cmake_minimum_required(VERSION 3.10)
project(OpenDLPScanner)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenDLPScanner
    main.cpp
    src/Scanner.cpp
)
target_compile_definitions(OpenDLPScanner PRIVATE SOLUTION_DIR="${CMAKE_SOURCE_DIR}")
target_include_directories(OpenDLPScanner PRIVATE include)
target_link_libraries(OpenDLPScanner PRIVATE nlohmann_json::nlohmann_json)
