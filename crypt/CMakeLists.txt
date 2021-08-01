cmake_minimum_required(VERSION 3.12)

find_package(OpenSSL REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CRYPT_SRC)

add_library(crypt STATIC ${CRYPT_SRC})

target_link_libraries(crypt PRIVATE OpenSSL::Crypto base58)