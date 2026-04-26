cmake_minimum_required(VERSION 3.20)
project(GameBoy C)

set(GBDK_HOME /opt/gbdk)
set(LCC ${GBDK_HOME}/bin/lcc)

file(GLOB_RECURSE GB_SOURCES CONFIGURE_DEPENDS src/*.c)

add_library(dummy EXCLUDE_FROM_ALL ${GB_SOURCES})
target_include_directories(dummy PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${GBDK_HOME}/include
)

find_file(GAMBATTE_CORE
        NAMES gambatte_libretro.so
        PATHS
        /usr/lib/x86_64-linux-gnu/libretro
        /usr/lib/libretro
)

add_custom_target(game
        COMMAND ${LCC} -Wall -Wextra -Iinclude -o game.gb ${GB_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        SOURCES ${GB_SOURCES}
        COMMENT "Building Game Boy ROM..."
)

if(GAMBATTE_CORE)
    add_custom_target(run
            COMMAND retroarch -L ${GAMBATTE_CORE} game.gb
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            DEPENDS game
            COMMENT "Running game.gb with RetroArch..."
    )
else()
    add_custom_target(run
            COMMAND ${CMAKE_COMMAND} -E echo "Error: gambatte_libretro.so not found."
            COMMENT "Gambatte core not found"
    )
endif()

add_custom_target(clean_game
        COMMAND ${CMAKE_COMMAND} -E rm -f
        ${CMAKE_SOURCE_DIR}/*.o
        ${CMAKE_SOURCE_DIR}/*.noi
        ${CMAKE_SOURCE_DIR}/*.map
        ${CMAKE_SOURCE_DIR}/*.sym
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Cleaning object files..."
)

add_custom_target(fclean
        COMMAND ${CMAKE_COMMAND} -E rm -f
        ${CMAKE_SOURCE_DIR}/*.o
        ${CMAKE_SOURCE_DIR}/*.noi
        ${CMAKE_SOURCE_DIR}/*.map
        ${CMAKE_SOURCE_DIR}/*.sym
        ${CMAKE_SOURCE_DIR}/*.gb
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Full clean..."
)