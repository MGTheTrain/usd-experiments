cmake_minimum_required(VERSION 3.28)

set(TARGET tinyusdz-parser)
project(${TARGET})

# include_directories(
#     ../include)
set(TINYUSDZ_PARSER_SRC 
    tinyusdz-parser.cpp
)  

add_executable(${TARGET} ${TINYUSDZ_PARSER_SRC})