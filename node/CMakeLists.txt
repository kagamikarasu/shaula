cmake_minimum_required(VERSION 3.12)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} NODE_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/config CONFIG_SRC)

add_library(node STATIC ${NODE_SRC} ${CONFIG_SRC})

target_link_libraries(node PRIVATE boost_coroutine boost_thread Threads::Threads message)
target_include_directories(node INTERFACE ${PROJECT_SOURCE_DIR})