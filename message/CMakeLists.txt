cmake_minimum_required(VERSION 3.12)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MESSAGE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/struct MESSAGE_STRUCT_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/last LAST_STRUCT_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/config CONFIG_SRC)

add_library(message STATIC ${MESSAGE_SRC} ${MESSAGE_STRUCT_SRC} ${LAST_STRUCT_SRC} ${CONFIG_SRC})

target_link_libraries(message PRIVATE crypt cardinal)
target_include_directories(message INTERFACE ${PROJECT_SOURCE_DIR})