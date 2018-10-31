cmake_minimum_required(VERSION 3.5)
project(my_string C)

set(CMAKE_C_STANDARD 99)
# set(bin_dir bin/)

add_library(_my_string SHARED
            my_string.c
            my_string.h)

file(MAKE_DIRECTORY bin/)

add_custom_command(TARGET _my_string POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy lib_my_string.so ../bin/)