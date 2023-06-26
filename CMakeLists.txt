cmake_minimum_required(VERSION 3.24)
project(crypto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /usr/include/)
find_path(SIMPLE2D_INCLUDE_DIR cryptolib.h
        /usr/include
        /usr/include/cryptopp
        DOC "The directory where simple2d.h resides.")
add_executable(crypto main.cpp tables.h tests.h encrypt.h decrypt.h common.h)
target_link_directories(crypto PRIVATE ${CMAKE_SOURCE_DIR}/../../../../usr/include)
target_link_libraries(crypto cryptopp)