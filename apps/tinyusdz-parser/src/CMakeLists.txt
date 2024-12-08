cmake_minimum_required(VERSION 3.28)

set(TARGET tinyusdz-parser)
project(${TARGET})

find_package(pxr CONFIG REQUIRED)

# include_directories(
#     ../include)
set(TINYUSDZ_PARSER_SRC 
    tinyusdz-parser.cpp
)  

add_executable(${TARGET} ${TINYUSDZ_PARSER_SRC})

target_link_libraries(${TARGET} PRIVATE ar gf hd hf)