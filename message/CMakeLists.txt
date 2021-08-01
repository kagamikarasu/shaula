cmake_minimum_required(VERSION 3.12)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MESSAGE_SRC)

add_library(message STATIC ${MESSAGE_SRC})

target_link_libraries(message PRIVATE crypt cardinal)
target_include_directories(message PRIVATE ${PROJECT_SOURCE_DIR})