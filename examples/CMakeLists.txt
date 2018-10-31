cmake_minimum_required(VERSION 3.5)
project(examples C)

set(CMAKE_C_STANDARD 99)

link_directories(../library/bin)
add_library(my_string SHARED IMPORTED)

add_executable(examples examples.c)
target_include_directories(examples PUBLIC ../library)
target_link_libraries(examples _my_string)

file(MAKE_DIRECTORY bin/)

add_custom_command(TARGET examples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy examples ../bin/)