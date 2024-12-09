# FindUSD.cmake - Find USD package based on known file names and directory structure

if(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-osx")
    else()
        set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x86_64-osx")
    endif()
elseif(UNIX)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-linux")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/arm64-linux")
    else()
        message(FATAL_ERROR "Unsupported architecture for UNIX platform: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
elseif(WIN32)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
        set(USD_SEARCH_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows")
    else()
        message(FATAL_ERROR "Unsupported architecture for Windows platform: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
else()
    message(STATUS "Unsupported platform")
endif()

if(EXISTS "${USD_SEARCH_DIR}")
    message(STATUS "Searching for USD in: ${USD_SEARCH_DIR}")

    # Handle dynamic and static libraries separately based on platform
    if(APPLE) 
        file(GLOB USD_STATIC_LIBRARIES ${USD_SEARCH_DIR}/lib/*.a)
        file(GLOB USD_DYNAMIC_LIBRARIES ${USD_SEARCH_DIR}/lib/*.dylib)
    elseif(UNIX) 
        file(GLOB USD_STATIC_LIBRARIES ${USD_SEARCH_DIR}/lib/*.a)
        file(GLOB USD_DYNAMIC_LIBRARIES ${USD_SEARCH_DIR}/bin/*.so)
    elseif(WIN32) 
        file(GLOB_RECURSE USD_STATIC_LIBRARIES ${USD_SEARCH_DIR}/lib/*.lib)
        file(GLOB_RECURSE USD_DYNAMIC_LIBRARIES ${USD_SEARCH_DIR}/bin/*.dll)
    else()  
        message(STATUS "Unsupported platform")
    endif()

    if(USD_STATIC_LIBRARIES)
        message(STATUS "Found static USD libraries: ${USD_STATIC_LIBRARIES}")
        set(USD_STATIC_LIB_DIR "${USD_SEARCH_DIR}/lib")
    else()
        message(FATAL_ERROR "Static USD libraries not found in: ${USD_SEARCH_DIR}/lib")
    endif()

    if(USD_DYNAMIC_LIBRARIES)
        message(STATUS "Found dynamic USD libraries: ${USD_DYNAMIC_LIBRARIES}")
    else()
        message(FATAL_ERROR "Dynamic USD libraries not found")
    endif()

    file(GLOB USD_INCLUDE_DIRS ${USD_SEARCH_DIR}/include)
    if(USD_INCLUDE_DIRS)
        message(STATUS "Found USD include directory: ${USD_INCLUDE_DIRS}")
        set(USD_INCLUDE_DIR "${USD_SEARCH_DIR}/include")
    else()
        message(FATAL_ERROR "USD include folder not found in: ${USD_SEARCH_DIR}/include")
    endif()

else()
    message(FATAL_ERROR "USD base directory not found: ${USD_SEARCH_DIR}")
endif()

set(USD_FOUND TRUE)

mark_as_advanced(USD_STATIC_LIBRARIES USD_DYNAMIC_LIBRARIES USD_INCLUDE_DIR)
