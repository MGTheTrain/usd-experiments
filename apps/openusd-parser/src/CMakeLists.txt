cmake_minimum_required(VERSION 3.28)

set(TARGET openusd-parser)
project(${TARGET})

find_package(pxr CONFIG REQUIRED)

# include_directories(
#     ../include)
set(OPENUSD_PARSER_SRC 
    openusd-parser.cpp
)  

add_executable(${TARGET} ${OPENUSD_PARSER_SRC})

target_link_libraries(${TARGET} PRIVATE ar gf hd hf)