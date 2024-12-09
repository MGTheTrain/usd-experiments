cmake_minimum_required(VERSION 3.28)

set(TARGET openusd-parser)
project(${TARGET})

set(OPENUSD_PARSER_SRC 
    openusd-parser.cpp
)

find_package(USD REQUIRED)

include_directories(${USD_INCLUDE_DIR})

add_executable(${TARGET} ${OPENUSD_PARSER_SRC})

if(APPLE)
    target_link_libraries(${TARGET} PRIVATE ${USD_STATIC_LIBRARIES} ${USD_DYNAMIC_LIBRARIES})
else()
    target_link_libraries(${TARGET} PRIVATE ${USD_STATIC_LIBRARIES})

    if(WIN32)
        foreach(lib IN LISTS USD_DYNAMIC_LIBRARIES)
            get_filename_component(lib_name ${lib} NAME)
            file(COPY ${lib} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
        endforeach()

        add_custom_command(TARGET ${TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${USD_SEARCH_DIR}/bin/usd" "${CMAKE_CURRENT_BINARY_DIR}/Release/usd"
        )

        add_custom_command(TARGET ${TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${USD_SEARCH_DIR}/lib/usd" "${CMAKE_CURRENT_BINARY_DIR}/Release/usd"
        )

    elseif(UNIX)
        foreach(lib IN LISTS USD_DYNAMIC_LIBRARIES)
            get_filename_component(lib_name ${lib} NAME)
            file(COPY ${lib} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        endforeach()

        add_custom_command(TARGET ${TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${USD_SEARCH_DIR}/bin/usd" "${CMAKE_CURRENT_BINARY_DIR}/usd"
        )

        add_custom_command(TARGET ${TARGET}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${USD_SEARCH_DIR}/lib/usd" "${CMAKE_CURRENT_BINARY_DIR}/usd"
        )

    else()
        message(STATUS "Unsupported platform")
    endif()
endif()