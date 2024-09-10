cmake_minimum_required(VERSION 3.26)
project(tictactoe)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall -Wextra -pedantic -std=c++20")

set(PRJ_SOURCE_FILES
        main.cpp
        game.cpp
        game.h
        display.cpp
        display.h
)

add_executable(${PROJECT_NAME}
        ${PRJ_SOURCE_FILES}
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(SDL2_INCLUDE_DIR c:/libs/SDL2-2.28.5/include)
    set(SDL2_LIB_DIR path c:/libs/SDL2-2.28.5/lib/x64)
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})
    target_link_libraries(${PROJECT_NAME}
            c:/libs/SDL2-2.28.5/lib/x64/SDL2main.lib
            c:/libs/SDL2-2.28.5/lib/x64/SDL2.lib
    )
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(
            ${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
    )
    target_include_directories(
            ${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
    )
endif()