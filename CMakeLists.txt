cmake_minimum_required(VERSION 3.12)
project(shaula CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Curses REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE boost_coroutine boost_thread Threads::Threads OpenSSL::Crypto base58 ncurses)

aux_source_directory(client CLIENT_SRC)
aux_source_directory(crypt CRYPT_SRC)
aux_source_directory(cardinal CARDINAL_SRC)
aux_source_directory(message MESSAGE_SRC)
aux_source_directory(display DISPLAY_SRC)
aux_source_directory(server SERVER_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_SRC} ${CRYPT_SRC} ${MESSAGE_SRC} ${CARDINAL_SRC} ${DISPLAY_SRC} ${SERVER_SRC} Node.cpp Node.h)