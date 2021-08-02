cmake_minimum_required(VERSION 3.12)

find_package(Curses REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DISPLAY_SRC)

add_library(observer STATIC ${DISPLAY_SRC})

target_link_libraries(observer PRIVATE ncurses server client)
target_include_directories(observer INTERFACE ${PROJECT_SOURCE_DIR})
