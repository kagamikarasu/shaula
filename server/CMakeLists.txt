cmake_minimum_required(VERSION 3.12)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SERVER_SRC)

add_library(server STATIC ${SERVER_SRC})

target_link_libraries(server PRIVATE node)
target_include_directories(server INTERFACE ${PROJECT_SOURCE_DIR})