cmake_minimum_required(VERSION 3.12)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CLIENT_SRC)

add_library(client STATIC ${CLIENT_SRC})

target_link_libraries(client PRIVATE node)
target_include_directories(client INTERFACE ${PROJECT_SOURCE_DIR})