cmake_minimum_required(VERSION 3.28)
set(TARGET usd-experiments)
project(${TARGET})   
set(CMAKE_CXX_STANDARD 17)

# Add the path to the custom Find module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
add_subdirectory(apps)