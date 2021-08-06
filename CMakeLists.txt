cmake_minimum_required(VERSION 3.12)
project(shaula CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Curses REQUIRED)

add_subdirectory(cardinal)
add_subdirectory(message)
add_subdirectory(node)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(observer)

target_link_libraries(${PROJECT_NAME} PRIVATE observer server client)

# test
enable_testing()
add_executable(test_cardinal test/test_cardinal.cpp)
target_link_libraries(test_cardinal PRIVATE cardinal)
add_test(NAME run_test_cardinal COMMAND test_server)