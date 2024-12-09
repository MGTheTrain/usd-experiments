cmake_minimum_required(VERSION 3.10)

set(TARGET tinyusdz-parser)
project(${TARGET})

set(TINYUSDZ_PATH ${CMAKE_SOURCE_DIR}/third-party/tinyusdz)

if(EXISTS ${TINYUSDZ_PATH})
    # The second argument (binary directory) ensures CMake puts build files in the correct place
    add_subdirectory(${TINYUSDZ_PATH} ${CMAKE_BINARY_DIR}/third-party/tinyusdz)
else()
    message(FATAL_ERROR "TinyUSDZ directory does not exist: ${TINYUSDZ_PATH}")
endif()

set(TINYUSDZ_PARSER_SRC 
    tinyusdz-parser.cpp
)

add_executable(${TARGET} ${TINYUSDZ_PARSER_SRC})

target_include_directories(${TARGET} PRIVATE "${TINYUSDZ_PATH}/src")
target_link_libraries(${TARGET} PRIVATE tinyusdz::tinyusdz_static)