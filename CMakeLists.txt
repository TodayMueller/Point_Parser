cmake_minimum_required(VERSION 3.16)
project(PointParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(cpp_program
    src/main.cpp
    src/parser_factory.cpp
    src/parser_factory.h
    src/parser_base.h
    src/text_parser.cpp
    src/text_parser.h
    src/binary_parser.cpp
    src/binary_parser.h
    src/json_parser.cpp
    src/json_parser.h
)

target_link_libraries(cpp_program PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS cpp_program DESTINATION bin)
install(FILES scripts/run.sh DESTINATION bin)
install(FILES scripts/plot.py DESTINATION lib)

execute_process(COMMAND chmod +x scripts/run.sh)
