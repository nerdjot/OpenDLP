cmake_minimum_required(VERSION 2.4)
project(scanner)

# Add nlohmann_json (header-only library)
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Add the scanner subdirectory, which contains its own CMakeLists.txt
add_subdirectory(src/scanner)