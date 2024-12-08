# FindUSD.cmake - Find USD package based on known file names and directory structure

if(APPLE) 
    set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-osx")
elseif(UNIX) 
    set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/third-party/OpenUSD")
elseif(WIN32) 
    set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/third-party/OpenUSD")
else()  
    message(STATUS "Unsupported platform")
endif()

# Check if the USD directory exists
if(EXISTS "${USD_SEARCH_DIR}")
    message(STATUS "Searching for USD in: ${USD_SEARCH_DIR}")

    if(APPLE) 
        file(GLOB USD_LIBRARIES 
            ${USD_SEARCH_DIR}/lib/*.a
            ${USD_SEARCH_DIR}/lib/*.dylib)
    elseif(UNIX) 
        file(GLOB USD_LIBRARIES 
            ${USD_SEARCH_DIR}/lib/*.a
            ${USD_SEARCH_DIR}/lib/*.so)
    elseif(WIN32) 
        file(GLOB USD_LIBRARIES 
            ${USD_SEARCH_DIR}/lib/*.lib
            ${USD_SEARCH_DIR}/lib/*.dll)
    else()  
        message(STATUS "Unsupported platform")
    endif()
    
    if(USD_LIBRARIES)
        message(STATUS "Found USD library: ${USD_LIBRARIES}")
        set(USD_LIB_DIR "${USD_SEARCH_DIR}/lib")
    else()
        message(FATAL_ERROR "USD library 'libusd_usd.dylib' not found in: ${USD_SEARCH_DIR}/lib")
    endif()

    file(GLOB USD_INCLUDE_DIRS ${USD_SEARCH_DIR}/include)
    if(USD_INCLUDE_DIRS)
        message(STATUS "Found pxr include directory: ${USD_INCLUDE_DIRS}")
        set(USD_INCLUDE_DIR "${USD_SEARCH_DIR}/include")
    else()
        message(FATAL_ERROR "pxr include folder not found in: ${USD_SEARCH_DIR}/include")
    endif()

else()
    message(FATAL_ERROR "USD base directory not found: ${USD_SEARCH_DIR}")
endif()

# Set USD_FOUND to true to indicate successful discovery
set(USD_FOUND TRUE)

# Export the variables for use in the project
mark_as_advanced(USD_LIBRARIES USD_INCLUDE_DIR)
