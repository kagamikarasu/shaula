cmake_minimum_required(VERSION 3.12)

find_package(Curses REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DISPLAY_SRC)

add_library(display STATIC ${DISPLAY_SRC})

target_link_libraries(display PRIVATE ncurses server client)
target_include_directories(display PUBLIC ${PROJECT_SOURCE_DIR})