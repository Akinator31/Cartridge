cmake_minimum_required(VERSION 3.20)
project(GameBoy C)

set(GBDK_HOME /opt/gbdk)

include_directories(${GBDK_HOME}/include)
add_library(dummy EXCLUDE_FROM_ALL src/main.c)

add_custom_target(game
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Building Game Boy ROM..."
)

add_custom_target(clean_game
        COMMAND make clean
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)