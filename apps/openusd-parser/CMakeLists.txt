cmake_minimum_required(VERSION 3.28)

set(TARGET openusd-parser)
project(${TARGET})

set(OPENUSD_PARSER_SRC 
    openusd-parser.cpp
)

find_package(USD REQUIRED)

include_directories(${USD_INCLUDE_DIR})

add_executable(${TARGET} ${OPENUSD_PARSER_SRC})

target_link_libraries(${TARGET} PRIVATE ${USD_LIBRARIES})