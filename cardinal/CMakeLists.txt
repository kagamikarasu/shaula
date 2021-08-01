cmake_minimum_required(VERSION 3.12)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CARDINAL_SRC)

add_library(cardinal STATIC ${CARDINAL_SRC})

target_link_libraries(cardinal PRIVATE OpenSSL::Crypto base58)

target_include_directories(cardinal INTERFACE ${PROJECT_SOURCE_DIR})